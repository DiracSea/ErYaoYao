/*
 * @Author: Longze Su
 * @Date: 2019-10-13 02:56:49
 * @Description: CS211_Project1
 * @LastEditTime: 2019-10-13 14:41:25
 * @LastEditors: Longze Su
 */

#include "functions.hpp"
#include "dg.hpp"


void dgemm_ijk(double* a, double* b, double* c, int n)
{
    double t0, t1; 
    Time t; 
    t0 = t.get_time(); 

    int i, j, k;
    for (i = 0; i < n; i++)
	    for (j = 0; j < n; j++)
        {
            register double r = c[i*n+j]; 
            for (k = 0; k < n; k++)
	            r += a[i*n + k]*b[k*n + j];
            c[i*n+j] = r; 
        }

    
    t1 = t.get_time(); 
    IO io; 
    io.output_b("ijk", 0, n, t1-t0); 
}
void dgemm_jik(double* a, double* b, double* c, int n)
{
    double t0, t1; 
    Time t; 
    t0 = t.get_time(); 

    int i, j, k;
    for (j = 0; j < n; j++)
	    for (i = 0; i < n; i++)
        {
            register double r = c[i*n+j];
            for (k = 0; k < n; k++)
	            r += a[i*n + k]*b[k*n + j];
            c[i*n+j] = r;
        }

    
    t1 = t.get_time(); 
    IO io; 
    io.output("jik", 0, n, t1-t0); 
}
void dgemm_ikj(double* a, double* b, double* c, int n)
{
    double t0, t1; 
    Time t; 
    t0 = t.get_time(); 

    int i, j, k;
    for (i = 0; i < n; i++)
	    for (k = 0; k < n; k++)
        {
            register double r = a[i*n + k];
            for (j = 0; j < n; j++)
	            c[i*n+j] += r*b[k*n + j];
            a[i*n + k] = r;
        }
    t1 = t.get_time(); 
    IO io; 
    io.output("ikj", 0, n, t1-t0); 
}
void dgemm_kij(double* a, double* b, double* c, int n)
{
    double t0, t1; 
    Time t; 
    t0 = t.get_time(); 

    int i, j, k;
    for (k = 0; k < n; k++)
	    for (i = 0; i < n; i++)
        {
            register double r = a[i*n + k];
            for (j = 0; j < n; j++)
	            c[i*n+j] += r*b[k*n + j];
            a[i*n + k] = r;
        }

    t1 = t.get_time(); 
    IO io; 
    io.output("kij", 0, n, t1-t0); 
}
void dgemm_jki(double* a, double* b, double* c, int n)
{
    double t0, t1; 
    Time t; 
    t0 = t.get_time(); 

    int i, j, k;
    for (j = 0; j < n; j++)
	    for (k = 0; k < n; k++)
        {
            register double r = b[k*n + j]; 
            for (i = 0; i < n; i++)
	            c[i*n+j] += a[i*n + k]*r;
            b[k*n + j] = r;
        }
    t1 = t.get_time(); 
    IO io; 
    io.output("jki", 0, n, t1-t0); 
}
void dgemm_kji(double* a, double* b, double* c, int n)
{
    double t0, t1; 
    Time t; 
    t0 = t.get_time(); 

    int i, j, k;
    for (k = 0; k < n; k++)
	    for (j = 0; j < n; j++)
        {
            register double r = b[k*n + j]; 
            for (i = 0; i < n; i++)
	            c[i*n+j] += a[i*n + k]*r;
            b[k*n + j] = r;
        }

    t1 = t.get_time(); 
    IO io; 
    io.output("kji", 0, n, t1-t0); 
}


void dgemm_ijk_blockn(double* a, double* b, double* c, int n, int B)
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
void dgemm_jik_blockn(double* a, double* b, double* c, int n, int B)
{
    double t0, t1; 
    Time t; 
    t0 = t.get_time(); 

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


    t1 = t.get_time(); 
    IO io; 
    io.output_b("jik", B, n, t1-t0); 
}
void dgemm_ikj_blockn(double* a, double* b, double* c, int n, int B)
{
    double t0, t1; 
    Time t; 
    t0 = t.get_time(); 

    int i, j, k, i1, j1, k1; 
    for (i = 0; i < n; i+=B)
	    for (k = 0; k < n; k+=B)
            for (j = 0; j < n; j+=B)
		    /* B x B mini matrix multiplications */
                for (i1 = i; i1 < i+B; i1++)
                    for (k1 = k; k1 < k+B; k1++)
                    {
                        register double r = a[i1*n + k1];
                        for (j1 = j; j1 < j+B; j1++)
	                        c[i1*n+j1] += r*b[k1*n + j1];
                        a[i1*n + k1] = r;
                    }
    t1 = t.get_time(); 
    IO io; 
    io.output_b("ikj", B, n, t1-t0); 
}
void dgemm_kij_blockn(double* a, double* b, double* c, int n, int B)
{
    double t0, t1; 
    Time t; 
    t0 = t.get_time(); 

    int i, j, k, i1, j1, k1; 
    for (k = 0; k < n; k+=B)
	    for (i = 0; i < n; i+=B)
            for (j = 0; j < n; j+=B)
		    /* B x B mini matrix multiplications */
                for (k1 = k; k1 < k+B; k1++)
                    for (i1 = i; i1 < i+B; i1++)
                    {
                        register double r = a[i1*n + k1];
                        for (j1 = j; j1 < j+B; j1++)
	                        c[i1*n+j1] += r*b[k1*n + j1];
                        a[i1*n + k1] = r;
                    }

    t1 = t.get_time(); 
    IO io; 
    io.output_b("kij", B, n, t1-t0); 
}
void dgemm_jki_blockn(double* a, double* b, double* c, int n, int B)
{
    double t0, t1; 
    Time t; 
    t0 = t.get_time(); 

    int i, j, k, i1, j1, k1; 
    for (j = 0; j < n; j+=B)
	    for (k = 0; k < n; k+=B)
            for (i = 0; i < n; i+=B)
		    /* B x B mini matrix multiplications */
                for (j1 = j; j1 < j+B; j1++)
                    for (k1 = k; k1 < k+B; k1++)
                    {
                        register double r = b[k1*n + j1]; 
                        for (i1 = i; i1 < i+B; i1++)
	                        c[i1*n+j1] += a[i1*n + k1]*r;
                        b[k1*n + j1] = r; 
                    }
    t1 = t.get_time(); 
    IO io; 
    io.output_b("jki", B, n, t1-t0); 
}
void dgemm_kji_blockn(double* a, double* b, double* c, int n, int B)
{
    double t0, t1; 
    Time t; 
    t0 = t.get_time(); 

    int i, j, k, i1, j1, k1; 
    for (k = 0; k < n; k+=B)
	    for (j = 0; j < n; j+=B)
            for (i = 0; i < n; i+=B)
		    /* B x B mini matrix multiplications */
                for (k1 = k; k1 < k+B; k1++)
                    for (j1 = j; j1 < j+B; j1++)
                    {
                        register double r = b[k1*n + j1]; 
                        for (i1 = i; i1 < i+B; i1++)
	                        c[i1*n+j1] += a[i1*n + k1]*r;
                        b[k1*n + j1] = r; 
                    }

    t1 = t.get_time(); 
    IO io; 
    io.output_b("kji", B, n, t1-t0); 
}

