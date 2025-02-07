/*
 * @Author: Longze Su
 * @Date: 2019-10-13 22:44:02
 * @Description: CS211_Project1
 * @LastEditTime: 2019-10-18 17:30:51
 * @LastEditors: Longze Su
 */


#include "functions.hpp" 

// strassen
void Dgemm::dgemm4(double* a, double* b, double* c, int n)
{
    double t0, t1; 
    Time t; 
    t0 = t.get_time(); 

    int i, j, k; 
    for (i = 0; i < n; i += 2) 
        for (j = 0; j < n; j += 2) 
        {
            // 19 registers
            register double c00 = c[i*n + j]; 
            register double c01 = c[i*n + j+1]; 
            register double c10 = c[(i+1)*n + j]; 
            register double c11 = c[(i+1)*n + j+1]; 
            
            for (k = 0; k < n; k += 2) 
            {
                register double a00 = a[i*n + k]; 
                register double a01 = a[i*n + k+1]; 
                register double a10 = a[(i+1)*n + k]; 
                register double a11 = a[(i+1)*n + k+1]; 

                // define 4 registers for b
                register double b00 = b[k*n + j]; 
                register double b01 = b[k*n + j+1]; 
                register double b10 = b[(k+1)*n + j]; 
                register double b11 = b[(k+1)*n + j+1];
                // 7m + 18a
                register double m1 = (a00 + a11) * (b00 + b11); 
                register double m2 = (a10 + a11) * b00;
                register double m3 = a00 * (b01 - b11);
                register double m4 =  a11 * (b10 - b00);
                register double m5 = (a00 + a01) * b11;
                register double m6 = (a10 - a00) * (b00 + b01);
                register double m7 = (a01 - a11) * (b10 + b11); 

                c00 += m1+m4-m5+m7; 
                c01 += m3+m5; 
                c10 += m2+m4; 
                c11 += m1+m3-m2+m6; 
            }
            // save register to mem
            c[i*n + j]       = c00; 
            c[i*n + j+1]     = c01; 
            c[(i+1)*n + j]   = c10; 
            c[(i+1)*n + j+1] = c11; 
        }
    t1 = t.get_time(); 
    IO io; 
    io.output("ijk_block_2x2", 2, n, t1-t0); 
}

// block strassen
void Dgemm::dgemm5(double* a, double* b, double* c, int n, int B)
{
    double t0, t1; 
    Time t; 
    t0 = t.get_time(); 

    int i, j, k, i1, j1, k1; 

    for (i = 0; i < n; i+=B)
	    for (j = 0; j < n; j+=B)
            for (k = 0; k < n; k+=B)
            // cache block
		    /* B x B mini matrix multiplications */
            {
                
                // prevent over boundary 
                int n_i2 = i+B > n ? n:i+B; 
                int n_j2 = j+B > n ? n:j+B; 
                int n_k2 = k+B > n ? n:k+B;

                // register block
                for (i1 = i; i1 < n_i2; i1 += 2)
                {
                    for (j1 = j; j1 < n_j2; j1 += 2)
                    {
                        int n0 = i1*n + j1; 
                        int n1 = n0 + n; 
                        register double c00 = c[n0]; 
                        register double c01 = c[n0 + 1];
                        register double c10 = c[n1]; 
                        register double c11 = c[n1 + 1];


                        for (k1 = k; k1 < n_k2; k1 += 2)
                        {
                            register double a00 = a[i1*n + k1]; 
                            register double a01 = a[i1*n + k1+1]; 
                            register double a10 = a[(i1+1)*n + k1]; 
                            register double a11 = a[(i1+1)*n + k1+1]; 

                            // define 4 registers for b
                            register double b00 = b[k1*n + j1]; 
                            register double b01 = b[k1*n + j1+1]; 
                            register double b10 = b[(k1+1)*n + j1]; 
                            register double b11 = b[(k1+1)*n + j1+1];
                            register double m1 = (a00 + a11) * (b00 + b11); 
                            register double m2 = (a10 + a11) * b00;
                            register double m3 = a00 * (b01 - b11);
                            register double m4 =  a11 * (b10 - b00);
                            register double m5 = (a00 + a01) * b11;
                            register double m6 = (a10 - a00) * (b00 + b01);
                            register double m7 = (a01 - a11) * (b10 + b11); 

                            c00 += m1+m4-m5+m7; 
                            c01 += m3+m5; 
                            c10 += m2+m4; 
                            c11 += m1+m3-m2+m6; 
                        }
                        // save register to mem
                        c[n0] = c00; 
                        c[n0 + 1] = c01; 
                        c[n1] = c10; 
                        c[n1 + 1] = c11; 
                    }
                }
            }
    

    t1 = t.get_time(); 
    IO io; 
    io.output_b("ss_2x2_blockn", B, n, t1-t0); 
}