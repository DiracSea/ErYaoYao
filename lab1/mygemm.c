/*
 * @author: Longze Su
 * @Date: 2019-10-14 11:41:26
 * @Description: cS211_Project1
 * @LastEditTime: 2019-10-14 11:54:51
 * @LastEditors: Longze Su
 */
#include "mygemm.h"

/**
 * 
 * Implement all functions here in this file.
 * Do NOT change input parameters and return type.
 * 
 **/

void dgemm0(const double* a, const double* b, double* c, const int n)
{
    int i, j, k;
    for (i = 0; i < n; i++) 
        for (j = 0; j < n; j++) 
            for (k = 0; k < n; k++) 
                c[i*n + j] += a[i*n + k]*b[k*n + j];
}

void dgemm1(const double *a, const double *b, double *c, const int n) 
{
    int i, j, k;
    for (i = 0; i < n; i++) 
        for (j = 0; j < n; j++)
        {
            register double r = c[i*n + j]; 
            for (k = 0; k < n; k++) 
                r += a[i*n + k]*b[k*n + j]; 
            c[i*n + j] = r; 
        }
}

void dgemm2(const double *a, const double *b, double *c, const int n) 
{
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
}

void dgemm3(const double *a, const double *b, double *c, const int n) 
{
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
}

void ijk(const double *a, const double *b, double *c, const int n) 
{
    int i, j, k;
    for (i = 0; i < n; i++)
	    for (j = 0; j < n; j++)
        {
            register double r = c[i*n+j]; 
            for (k = 0; k < n; k++)
	            r += a[i*n + k]*b[k*n + j];
            c[i*n+j] = r; 
        }
}

void bijk(const double *a, const double *b, double *c, const int n, const int B) 
{
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
}

void jik(const double *a, const double *b, double *c, const int n) 
{
    int i, j, k;
    for (j = 0; j < n; j++)
	    for (i = 0; i < n; i++)
        {
            register double r = c[i*n+j];
            for (k = 0; k < n; k++)
	            r += a[i*n + k]*b[k*n + j];
            c[i*n+j] = r;
        }
}

void bjik(const double *a, const double *b, double *c, const int n, const int B) 
{
    int i, j, k, i1, j1, k1; 
    for (j = 0; j < n; j+=B)
	    for (i = 0; i < n; i+=B)
            for (k = 0; k < n; k+=B)
		    /* B x B mini matrix multiplications */
                for (j1 = j; j1 < j+B; j1++)
                    for (i1 = i; i1 < i+B; i1++)
                    {
                        register double r = c[i1*n+j1];
                        for (k1 = k; k1 < k+B; k1++)
	                        r += a[i1*n + k1]*b[k1*n + j1];
                        c[i1*n+j1] = r;
                    }
}

void kij(const double *a, const double *b, double *c, const int n) 
{
    int i, j, k;
    for (k = 0; k < n; k++)
	    for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
	            c[i*n+j] += a[i*n + k]*b[k*n + j];
        }
}

void bkij(const double *a, const double *b, double *c, const int n, const int B) 
{
    int i, j, k, i1, j1, k1; 
    for (k = 0; k < n; k+=B)
	    for (i = 0; i < n; i+=B)
            for (j = 0; j < n; j+=B)
		    /* B x B mini matrix multiplications */
                for (k1 = k; k1 < k+B; k1++)
                    for (i1 = i; i1 < i+B; i1++)
                    {
                        for (j1 = j; j1 < j+B; j1++)
	                        c[i1*n+j1] += a[i1*n + k1]*b[k1*n + j1];
                    }
}


void ikj(const double *a, const double *b, double *c, const int n) 
{
    int i, j, k;
    for (i = 0; i < n; i++)
	    for (k = 0; k < n; k++)
        {
            for (j = 0; j < n; j++)
	            c[i*n+j] += a[i*n + k]*b[k*n + j];

        }
}

void bikj(const double *a, const double *b, double *c, const int n, const int B) 
{
    int i, j, k, i1, j1, k1; 
    for (i = 0; i < n; i+=B)
	    for (k = 0; k < n; k+=B)
            for (j = 0; j < n; j+=B)
		    /* B x B mini matrix multiplications */
                for (i1 = i; i1 < i+B; i1++)
                    for (k1 = k; k1 < k+B; k1++)
                    {
                        for (j1 = j; j1 < j+B; j1++)
	                        c[i1*n+j1] += a[i1*n + k1]*b[k1*n + j1];
                    }
}

void jki(const double *a, const double *b, double *c, const int n) 
{
    int i, j, k;
    for (j = 0; j < n; j++)
	    for (k = 0; k < n; k++)
        {
            for (i = 0; i < n; i++)
	            c[i*n+j] += a[i*n + k]*b[k*n + j];
        }
}

void bjki(const double *a, const double *b, double *c, const int n, const int B) 
{
    int i, j, k, i1, j1, k1; 
    for (j = 0; j < n; j+=B)
	    for (k = 0; k < n; k+=B)
            for (i = 0; i < n; i+=B)
		    /* B x B mini matrix multiplications */
                for (j1 = j; j1 < j+B; j1++)
                    for (k1 = k; k1 < k+B; k1++)
                    {
                        for (i1 = i; i1 < i+B; i1++)
	                        c[i1*n+j1] += a[i1*n + k1]*b[k1*n + j1];
                    }
}

void kji(const double *a, const double *b, double *c, const int n) 
{
    int i, j, k;
    for (k = 0; k < n; k++)
	    for (j = 0; j < n; j++)
        {
            for (i = 0; i < n; i++)
	            c[i*n+j] += a[i*n + k]*b[k*n + j];
        }
}

void bkji(const double *a, const double *b, double *c, const int n, const int B) 
{
    int i, j, k, i1, j1, k1; 
    for (k = 0; k < n; k+=B)
	    for (j = 0; j < n; j+=B)
            for (i = 0; i < n; i+=B)
		    /* B x B mini matrix multiplications */
                for (k1 = k; k1 < k+B; k1++)
                    for (j1 = j; j1 < j+B; j1++)
                    {
                        for (i1 = i; i1 < i+B; i1++)
	                        c[i1*n+j1] += a[i1*n + k1]*b[k1*n + j1];
                    }
}

void optimal(const double* a, const double* b, double *c, const int n, const int B)
{
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
    
}