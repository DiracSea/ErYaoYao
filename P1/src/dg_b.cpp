/*
 * @Author: Longze Su
 * @Date: 2019-10-13 22:44:02
 * @Description: CS211_Project1
 * @LastEditTime: 2019-10-14 01:30:43
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
void Dgemm::dgemm5(double* a, double* b, double* c, int n)
{
    
}