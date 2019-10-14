/*
 * @Author: Longze Su
 * @Date: 2019-10-12 16:59:07
 * @Description: CS211_Project1
 * @LastEditTime: 2019-10-13 18:08:39
 * @LastEditors: Longze Su
 */

#include "functions.hpp"

Dgemm::Dgemm(){}
Dgemm::~Dgemm(){}

void Dgemm::dgemm0(double* a, double* b, double* c, int n)
{
    double t0, t1; 
    Time t; 
    t0 = t.get_time(); 

    int i, j, k;
    for (i = 0; i < n; i++) 
        for (j = 0; j < n; j++) 
            for (k = 0; k < n; k++) 
                c[i*n + j] += a[i*n + k]*b[k*n + j];
    t1 = t.get_time();  
    IO io; 
    io.output("ijk", 0, n, t1-t0); 
}

void Dgemm::dgemm1(double* a, double* b, double* c, int n)
{
    double t0, t1; 
    Time t; 
    t0 = t.get_time(); 

    int i, j, k;
    for (i = 0; i < n; i++) 
        for (j = 0; j < n; j++)
        {
            register double r = c[i*n + j]; 
            for (k = 0; k < n; k++) 
                r += a[i*n + k]*b[k*n + j]; 
            c[i*n + j] = r; 
        }
    t1 = t.get_time(); 
    IO io; 
    io.output("ijk", 1, n, t1-t0); 
}

void Dgemm::dgemm2(double *a, double *b, double *c, int n) 
{
    double t0, t1; 
    Time t; 
    t0 = t.get_time(); 

    int i, j, k;
    for (i = 0; i < n; i += 2)
        for (j = 0; j < n; j += 2) { 

            // define 4 registers for c 
            register double c00 = c[i*n + j]; 
            register double c01 = c[i*n + j+1]; 
            register double c10 = c[(i+1)*n + j]; 
            register double c11 = c[(i+1)*n + j+1]; 

            for (k = 0; k < n; k += 2) {
                // define 4 registers for a
                register double a00 = a[i*n + k]; 
                register double a01 = a[i*n + k+1]; 
                register double a10 = a[(i+1)*n + k]; 
                register double a11 = a[(i+1)*n + k+1]; 

                // define 4 registers for b
                register double b00 = b[k*n + j]; 
                register double b01 = b[k*n + j+1]; 
                register double b10 = b[(k+1)*n + j]; 
                register double b11 = b[(k+1)*n + j+1];

                // computations
                c00 += a00*b00 + a01*b10; 
                c01 += a00*b01 + a01*b11; 
                c10 += a10*b00 + a11*b10; 
                c11 += a10*b01 + a11*b11; 
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

void Dgemm::dgemm3(double *a, double *b, double *c, int n) 
{
    double t0, t1; 
    Time t; 
    t0 = t.get_time(); 

    int i, j, k, l;
    for (i = 0; i < n; i += 3)
        for (j = 0; j < n; j += 3) { 

            // define 9 registers for c 
            register double c00 = c[i*n + j]; 
            register double c01 = c[i*n + j+1]; 
            register double c02 = c[i*n + j+2];
            register double c10 = c[(i+1)*n + j]; 
            register double c11 = c[(i+1)*n + j+1];
            register double c12 = c[(i+1)*n + j+2];
            register double c20 = c[(i+2)*n + j]; 
            register double c21 = c[(i+2)*n + j+1]; 
            register double c22 = c[(i+2)*n + j+2];

            for (k = 0; k < n; k += 3) {

                // reuse register of A and B
                for (l = 0; l < 3; l += 1) {

                    // define 3 registers for a
                    register double a0 = a[i*n + k+l]; 
                    register double a1 = a[(i+1)*n + k+l]; 
                    register double a2 = a[(i+2)*n + k+l]; 

                    // define 3 registers for b
                    register double b0 = b[(k+l)*n + j]; 
                    register double b1 = b[(k+l)*n + j+1]; 
                    register double b2 = b[(k+l)*n + j+2]; 

                    // computations
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
            // save register to mem
            c[i*n + j]       = c00; 
            c[i*n + j+1]     = c01;
            c[i*n + j+2]     = c02; 
            c[(i+1)*n + j]   = c10; 
            c[(i+1)*n + j+1] = c11; 
            c[(i+1)*n + j+2] = c12; 
            c[(i+2)*n + j]   = c20; 
            c[(i+2)*n + j+1] = c21; 
            c[(i+2)*n + j+2] = c22;
        }



    t1 = t.get_time(); 
    IO io; 
    io.output("ijk_block_3x3", 3, n, t1-t0); 
}