- [**CS211 Project2**](#cs211-project2)
  - [**High Performance Sequential Codes for Solving Large Linear Systems**](#high-performance-sequential-codes-for-solving-large-linear-systems)
    - [***Part #1***](#part-1)
      - [**1. Symbols**](#1-symbols)
      - [**2. Code**](#2-code)
      - [**3. Calculation**](#3-calculation)
      - [**4. Performance**](#4-performance)
    - [***Part #2***](#part-2)
      - [**1. Code Design**](#1-code-design)
      - [**2. Code**](#2-code-1)
      - [**3. Performance**](#3-performance)

<center> 

# **CS211 Project2**

Name: Longze Su 

SID: 862188702

## **High Performance Sequential Codes for Solving Large Linear Systems**

### ***Part #1***

</center> 

#### **1. Symbols**

Variable | Unit | Description
-|-|-
Op|Flops|double float-point operations
P|GFlops|performance
T|s|time

#### **2. Code**

- *This is mydgetrf*
```C++
int mydgetrf(double *A, int *ipiv, int n) 
{
    int i, t, maxIdx; 
    double maxV; // tmpR; 
    double *tmpR = (double*) malloc(sizeof(double) * n); 

    // ipiv = idx of pivot\
    // pivoting
    for (i = 0; i < n; i++) 
    {
        maxIdx = i; maxV = fabs(A[i*n + i]); 

        for (t = i+1; t < n; t++) 
        {
            if (fabs(A[t*n + i]) > maxV) 
            {
                maxIdx = t; maxV = fabs(A[t*n + i]); 
            } 
        }
        if (maxV == 0) 
        {
            printf("A is singular, Terminated.\n");
            return -1; 
        }
        else 
        {
            if (maxIdx != i) // pivoting
            {
                // save pivot
                int tmp = ipiv[i]; 
                ipiv[i] = ipiv[maxIdx]; 
                ipiv[maxIdx] = tmp; 

                // swap
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
```

- *This is mydtrsv*
```C++
void mydtrsv(char UPLO, double *A, double *B, int n, int *ipiv)
{
    // UPLO = 'L' or 'U' 
    double *y = (double*) malloc(n * sizeof(double)); 
    // set 0
    memset(y, 0.0, sizeof(double)); 

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

    memcpy(B, y, sizeof(double)*n); 
    free(y); 
    return;
}

```

#### **3. Calculation**

To calculate the Performance of the algorithm, we should not only know the running time of our programs, but also need to know the total double floating-point operations. Because 
$$ P = totalOp/t $$
We know the algorithm of GE is composed of three parts: 

Factorization $A=L*U$, Solve $L*y=b$ and Solve $U*x=y$

For the factorization, the calculation is like 
$$A(i+1:n,i+1:n) = A(i+1:n , i+1:n) - A(i+1:n, i) * A(i, i+1:n)$$ 

There are one minus and one multiple, totally two double floating arithmetic operations. 

To calculate its Op, we have: 
$$ factOp = 2\sum_{i=1}^{n} i^2=2*\frac{n(n-1)(2n-1)}{6}\approx\frac{2}{3}n^3 $$
The $L*y=b$ have equation: 
$$ sum += y[j] * A[i*n + j] $$
Also have two double floating arithmetic operations.
$$ Op_L = 2\sum_{i=1}^{n-1} i=2*\frac{1}{2}(n-1)n\approx n^2 $$
The $U*x=b$ also have equation: 
$$ sum += y[j] * A[i*n + j] $$
It has two double floating arithmetic operations.
$$ Op_U = 2\sum_{i=1}^{n} i=2*\frac{1}{2}n(n+1)\approx n^2 $$
As a result, the total operation is: 
$$ totalOp=factOp+Op_L+Op_U=\frac{2}{3}n^3+2n^2 $$
#### **4. Performance** 

- Floating point operations

n | 1002 | 2001 | 3000 | 4002 | 5001 
-|-|-|-|-|-
Op(Flops)|672,682,680|5,349,345,336|18,018,000,000|42,762,730,680|83,433,363,336

- Time

n | 1002 | 2001 | 3000 | 4002 | 5001 
-|-|-|-|-|-
MKL LAPACK(s)|0.148049|0.572735|1.735190|3.778885|7.151238
naive LU(s)|3.762635|30.229238|104.493806|242.035430|486.754238


- Peformance

n | 1002 | 2001 | 3000 | 4002 | 5001 
-|-|-|-|-|-
MKL LAPACK(GFlops)|4.5436|9.3400|10.3839|11.3162|<font color=#DC143C>11.6670<color>
naive LU(GFlops)|<font color=#DC143C>0.1788<color>|0.1770|0.1724|0.1767|0.1714

![MKL](https://raw.githubusercontent.com/DiracSea/src/master/211_2_1.png)
![naive](https://raw.githubusercontent.com/DiracSea/src/master/211_2_2.png)

<center> 

### ***Part #2***

</center> 


#### **1. Code Design**

- blocked matrix multiplcation
Similar to the lab1, execept the order of outer loop is kij, and the element updated in inner loop of C is not plus but minus. $A(end+1:n, end+1:n) -= A(end+1:n, ib:end)*A(ib:end, end+1:n)$

- mydgetrf_block
Pivoting is the similar with the naive method. In this case, do pivoting in each block. 

Because in naive method, we use BLAS2 to factorize, in this case, we use BLAS3 instead. 

Divide the factorization into two parts. Delayed the update of U matrix.
#### **2. Code**

- *This is modified block Matrix Mutiplication*
```C++
void mydgemm(double *a, double *b, double *c, int n, int i, int j, int k, int B)
{
    // cache block
    /* B x B mini matrix multiplications */
    
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

                    // A(end+1:n, end+1:n) -= A(end+1:n, ib:end)*A(ib:end, end+1:n)    

                    c00 -= a0*b0; 
                    c01 -= a0*b1; 
                    c02 -= a0*b2; 
                    c10 -= a1*b0; 
                    c11 -= a1*b1; 
                    c12 -= a1*b2; 
                    c20 -= a2*b0; 
                    c21 -= a2*b1; 
                    c22 -= a2*b2; 
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
    return;
}
```

- *This is mydetrf_block*
```C++
int mydgetrf_block(double *A, int *ipiv, int n, int b) 
{
    int i_block, i, j, k, maxIdx;
    double max, sum;
    double *tmpR = (double*) malloc(sizeof(double) * n);

    // blocking, blocksize is b
    // process matrix b col at a time
    for (i_block = 0; i_block < n; i_block += b)
    {
        // prevent out of bound i < i_block+b
        // the block start point is i 
        // BLAS2 version of GEPP to block
        for (i = i_block; i < i_block+b && i < n; i++)
        {
            // pivoting
            maxIdx = i;
            // max value in a row
            max = fabs(A[i*n + i]);
            
            // find pivoting idx
            for (j = i+1; j < n; j++)
            {
                if (fabs(A[j*n + i]) > max)
                {
                    maxIdx = j;
                    max = fabs(A[j*n + i]);
                }
            }
            if (max == 0)
            {
                printf("A is singular, Terminated.\n");
                return -1;
            }
            else
            {
                // begin swap
                if (maxIdx != i)
                {
                    // save pivoting 
                    int tmp = ipiv[i];
                    ipiv[i] = ipiv[maxIdx];
                    ipiv[maxIdx] = tmp;
                    
                    // swap rows
                    memcpy(tmpR, A + i*n, n * sizeof(double));
                    memcpy(A + i*n, A + maxIdx*n, n * sizeof(double));
                    memcpy(A + maxIdx*n, tmpR, n * sizeof(double));
                }
            }

            // factorization of block
            // get A(i_block:n, i_block:i_block+b) = P*L*U
            // delay update
            // i = i_block:i_block+b

            for (j = i+1; j < n; j++)
            {
                A[j*n + i] = A[j*n + i] / A[i*n + i]; // store multiple coefficiency
                
                int k;
                for (k = i+1; k < i_block+b && k < n; k++) 
                {
                    A[j*n + k] -= A[j*n +i] * A[i*n + k]; // get naive U
                }
            }
        }

        // BLAS3 

        // update next b rows of U
        // A(ib:end, end+1:n) = LL-1*A(ib:end, end+1:n)
        // update A(ib:end, end+1:n)
        for (i = i_block; i < i_block+b && i < n; i++)
        {
            for (j = i_block+b; j < n; j++)
            {
                sum = 0.0;
                for (k = i_block; k < i; k++)
                {
                    sum += A[i*n + k] * A[k*n + j];
                }
                A[i*n + j] -= sum; // update U
            }
        }

        // update A(end+1:n, end+1:n)
        // apply delayed updates with MM with inner dimension b
        // kij ijk i_block+b
        for (i = i_block+b; i < n; i += b)
        {
            for (j = i_block+b; j < n; j += b)
            {
                // mydgemm(double *a, double *b, double *c, int n, int i, int j, int k, int blocksize)
                mydgemm(A, A, A, n, i, j, i_block, b);
            }
        }
    }
    return 0;
}
```

#### **3. Performance** 

The total operation is: 
$$ totalOp=factOp+Op_L+Op_U=\frac{2}{3}n^3+2n^2 $$

- Floating point operations

n | 1002 | 2001 | 3000 | 4002 | 5001 
-|-|-|-|-|-
Op(Flops)|672,682,680|5,349,345,336|18,018,000,000|42,762,730,680|83,433,363,336

- Time

n | 1002 | 2001 | 3000 | 4002 | 5001 
-|-|-|-|-|-
block LU(s)|1.510022|10.156972|32.807879|74.948826|142.978749

- Peformance

n | 1002 | 2001 | 3000 | 4002 | 5001 
-|-|-|-|-|-
block LU(GFlops)|0.4455|0.5267|0.5492|0.5706|<font color=#DC143C>0.5835<font>
![block](https://raw.githubusercontent.com/DiracSea/src/master/211_2_3.png)