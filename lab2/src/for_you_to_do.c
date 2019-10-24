#include "../include/for_you_to_do.h"
/**
 * 
 * this function computes LU factorization
 * for a square matrix
 * 
 * syntax 
 *  
 *  input : 
 *      A     n by n , square matrix
 *      ipiv  1 by n , vector
 *      n            , length of vector / size of matrix
 *  
 *  output :
 *      return -1 : if the matrix A is singular (max pivot == 0)
 *      return  0 : return normally 
 * 
 **/

// array operate

int mydgetrf(double *A, int *ipiv, int n) 
{
    /* add your code here */
    int maxIdx, tmpP; 
    double maxV; // tmpR; 
    double *tmpR = (double*) malloc(sizeof(double) * n); 

    // ipiv = idx of pivot\
    // pivoting
    for (int i = 0; i < n; i++) 
    {
        maxIdx = i; maxV = fabs(A[i*n + i]); 

        for (int t = i+1; t < n; t++) 
        {
            if (fabs(A[t*n + i]) > maxV) 
            {
                maxIdx = t; maxV = fabs(A[t*n + i]); 
            } 
        }
        if (maxV == 0) 
        {
            printf("Zero Row, Terminated.\n");
            return 0; 
        }
        else 
        {
            if (maxIdx != i) // pivoting
            {
                // save pivot
                tmpP = ipiv[i]; 
                ipiv[i] = ipiv[maxIdx]; 
                ipiv[maxIdx] = tmpP; 

                // swap

                // for (int j = 0; j < n; i++) 
                // {
                //     tmpR = A[i*n + j]; 
                //     A[i*n + j] = A[maxIdx*n + j]; 
                //     A[maxIdx*n + j] = tmpR; 
                // }
                // memcpy quicker
                memcpy(tmpR, A + i*n, n * sizeof(double));
                memcpy(A + i*n, A + maxIdx*n, n * sizeof(double));
                memcpy(A + maxIdx*n, tmpR, n * sizeof(double));
                
            }
        }

        // factorization
        int j; 
        for (j = i+1; j < n; j++) 
        {
            A[j*n + i] = A[j*n + i]/A[i*n + i]; 
            int k; 
            for (k = i+1; k < n; k++)
            {
                A[j*n + k] -= A[j*n + i] * A[i*n + k]; 
            }
        }
    }
    free(tmpR); 
    return 0;
}

/**
 * 
 * this function computes triangular matrix - vector solver
 * for a square matrix . according to lecture slides, this
 * function computes forward AND backward subtitution in the
 * same function.
 * 
 * syntax 
 *  
 *  input :
 *      UPLO  'L' or 'U' , denotes whether input matrix is upper
 *                         lower triangular . ( forward / backward
 *                         substitution )
 * 
 *      A     n by n     , square matrix
 * 
 *      B     1 by n     , vector
 * 
 *      ipiv  1 by n     , vector , denotes interchanged index due
 *                                  to pivoting by mydgetrf()
 * 
 *      n                , length of vector / size of matrix
 *  
 *  output :
 *      none
 * 
 **/
void mydtrsv(char UPLO, double *A, double *B, int n, int *ipiv)
{
    /* add your code here */
    // UPLO = 'L' or 'U' 
    double *y = (double*) malloc(n * sizeof(double)); 
    memset(y, 0.0, sizeof(double)); // set 0

    double sum; 
    int i, j; 

    if (UPLO == 'L') 
    {
        y[0] = B[ipiv[0]]; 
        for (i = 1; i < n; i++) 
        {
            sum = 0.0; 
            for (j = 0; j < i; j++) 
            {
                sum += y[j] * A[i*n + j];
            }
            y[i] = B[ipiv[i]] - sum;
        }
    }

    else if (UPLO == 'U') 
    {
        y[n - 1] = B[n - 1] / A[(n-1)*n + n-1];
        for (i = n-2; i >= 0; i--)
        {
            sum = 0.0;
            for (j = i+1; j < n; j++)
            {
                sum += y[j] * A[i*n + j];
            }
            y[i] = (B[i] - sum) / A[i*n + i];
        }
    }

    free(y); 
    memcpy(B, y, sizeof(double)*n); 
    return;
}

/**
 * 
 * Same function as what you used in lab1, cache_part4.c : optimal( ... ).
 * 
 **/
void mydgemm(double *a, double *b, double *c, int n, int i, int j, int k, int B)
{
    /* add your code here */
    /* please just copy from your lab1 function optimal( ... ) */
    int i1, j1, k1, l; 
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
    return;
}

/**
 * 
 * this function computes triangular matrix - vector solver
 * for a square matrix using block gepp introduced in course
 * lecture .
 * 
 * just implement the block algorithm you learned in class.
 * 
 * syntax 
 *  
 *  input :
 *      UPLO  'L' or 'U' , denotes whether input matrix is upper
 *                         lower triangular . ( forward / backward
 *                         substitution )
 * 
 *      A     n by n     , square matrix
 * 
 *      B     1 by n     , vector
 * 
 *      ipiv  1 by n     , vector , denotes interchanged index due
 *                                  to pivoting by mydgetrf()
 * 
 *      n                , length of vector / size of matrix
 *  
 *  output :
 *      return -1 : if the matrix A is singular (max pivot == 0)
 *      return  0 : return normally 
 * 
 **/
int mydgetrf_block(double *A, int *ipiv, int n, int b) 
{
    int ib, i, j, k, maxIndex;
    double max, sum;
    double *temprow = (double*) malloc(sizeof(double) * n);

    for (ib = 0; ib < n; ib += b)
    {
        for (i = ib; i < ib+b && i < n; i++)
        {
            // pivoting
            maxIndex = i;
            max = fabs(A[i*n + i]);
            
            int j;
            for (j = i+1; j < n; j++)
            {
                if (fabs(A[j*n + i]) > max)
                {
                    maxIndex = j;
                    max = fabs(A[j*n + i]);
                }
            }
            if (max == 0)
            {
                printf("LU factorization failed: coefficient matrix is singular.\n");
                return -1;
            }
            else
            {
                if (maxIndex != i)
                {
                    // save pivoting information
                    int temp = ipiv[i];
                    ipiv[i] = ipiv[maxIndex];
                    ipiv[maxIndex] = temp;
                    // swap rows
                    memcpy(temprow, A + i*n, n * sizeof(double));
                    memcpy(A + i*n, A + maxIndex*n, n * sizeof(double));
                    memcpy(A + maxIndex*n, temprow, n * sizeof(double));
                }
            }

            // factorization
            for (j = i+1; j < n; j++)
            {
                A[j*n + i] = A[j*n + i] / A[i*n + i];
                int k;
                for (k = i+1; k < ib+b && k < n; k++)
                {
                    A[j*n + k] -= A[j*n +i] * A[i*n + k];
                }
            }
        }

        // update A(ib:end, end+1:n)
        for (i = ib; i < ib+b && i < n; i++)
        {
            for (j = ib+b; j < n; j++)
            {
                sum = 0;
                for (k = ib; k < i; k++)
                {
                    sum += A[i*n + k] * A[k*n + j];
                }
                A[i*n + j] -= sum;
            }
        }

        // update A(end+1:n, end+1:n)
        for (i = ib+b; i < n; i += b)
        {
            for (j = ib+b; j < n; j += b)
            {
                dgemm3_cache_mod(A, A, A, n, i, j, ib, b);
            }
        }
    }
    return 0;
}

