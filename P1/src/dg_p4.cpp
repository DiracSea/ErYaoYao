/*
 * @Author: Longze Su
 * @Date: 2019-10-13 12:24:34
 * @Description: CS211_Project1
 * @LastEditTime: 2019-10-13 16:29:07
 * @LastEditors: Longze Su
 */

#include "functions.hpp"
#include "dg.hpp"
void Dgemm::dgemm_ijk_blockn(double* a, double* b, double* c, int n, int B)
{
    double t0, t1; 
    Time t; 
    t0 = t.get_time(); 

    int i, j, k, i1, j1, k1; 
    for (i = 0; i < n; i+=B)
	    for (j = 0; j < n; j+=B)
            for (k = 0; k < n; k+=B)
		    /* B x B mini matrix multiplications */
                for (i1 = i; i1 < i+B; i1++)
                    for (j1 = j; j1 < j+B; j1++)
                    {
                        register double r = c[i1*n+j1];
                        for (k1 = k; k1 < k+B; k1++)
	                        r += a[i1*n + k1]*b[k1*n + j1];
                        c[i1*n+j1] = r;
                    }

    t1 = t.get_time(); 
    IO io; 
    io.output_b("ijk", B, n, t1-t0); 
}
// dgemm 3x3 register and cache
// block of block
void Dgemm::dgemm_3x3_blockn(double* a, double* b, double* c, int n, int B)
{
    double t0, t1; 
    Time t; 
    t0 = t.get_time(); 

    int i, j, k, i1, j1, k1, l; 

    for (i = 0; i < n; i+=B)
	    for (j = 0; j < n; j+=B)
            for (k = 0; k < n; k+=B)
            // cache block
		    /* B x B mini matrix multiplications */
            {
                
                // prevent over boundary 
                int n_i3 = i+B > n ? n:i+B; 
                int n_j3 = j+B > n ? n:j+B; 
                int n_k3 = k+B > n ? n:k+B;

                // register block
                for (i1 = i; i1 < n_i3; i1 += 3)
                {
                    for (j1 = j; j1 < n_j3; j1 += 3)
                    {
                        int n0 = i1*n + j1; 
                        int n1 = n0 + n; 
                        int n2 = n1 + n; 
                        register double c00 = c[n0]; 
                        register double c01 = c[n0 + 1];
                        register double c02 = c[n0 + 2];
                        register double c10 = c[n1]; 
                        register double c11 = c[n1 + 1];
                        register double c12 = c[n1 + 2];
                        register double c20 = c[n2];
                        register double c21 = c[n2 + 1];
                        register double c22 = c[n2 + 2];

                        for (k1 = k; k1 < n_k3; k1 += 3)
                        {
                            for (l = 0; l < 3; l++) 
                            {
                                int n0a = i1*n + k1 + l; 
                                int n1a = n0a + n; 
                                int n2a = n1a + n; 
                                int n0b = k1*n + j1 + l*n; 

                                register double a0 = a[n0a];
                                register double a1 = a[n1a]; 
                                register double a2 = a[n2a]; 
                                register double b0 = b[n0b]; 
                                register double b1 = b[n0b + 1]; 
                                register double b2 = b[n0b + 2]; 

                                c00 += a0*b0; 
                                c01 += a0*b1; 
                                c02 += a0*b2; 
                                c10 += a1*b0; 
                                c11 += a1*b1; 
                                c12 += a1*b2; 
                                c20 += a2*b0; 
                                c21 += a2*b1; 
                                c22 += a2*b2; 
                            }
                        }
                        c[n0] = c00;
                        c[n0 + 1] = c01;
                        c[n0 + 2] = c02;
                        c[n1] = c10;
                        c[n1 + 1] = c11;
                        c[n1 + 2] = c12;
                        c[n2] = c20;
                        c[n2 + 1] = c21;
                        c[n2 + 2] = c22;
                    }
                }
            }
    

    t1 = t.get_time(); 
    IO io; 
    io.output_b("_3x3_blockn", B, n, t1-t0); 
}