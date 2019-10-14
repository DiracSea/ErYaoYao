<!--
 * @Author: Longze Su
 * @Date: 2019-10-12 16:13:59
 * @Description: CS211_Project1
 * @LastEditTime: 2019-10-13 15:23:38
 * @LastEditors: Longze Su
 -->
- [**CS211 Project1**](#cs211-project1)
    - [**I. Register Reuse**](#i-register-reuse)
        - [***Part #1***](#part-1)
            - [**1. Symbols**](#1-symbols)
            - [**2. Calculation**](#2-calculation)
            - [**3. Performance**](#3-performance)
                - [**Calculations**](#calculations)
            - [**4.Results**](#4results)
        - [***Part #2***](#part-2)
            - [**1. Code**](#1-code)
            - [**2. Calculations**](#2-calculations)
            - [**3. Performance**](#3-performance-1)
        - [***Part #3***](#part-3)
            - [**1. Analysis**](#1-analysis)
            - [**2. Code**](#2-code)
            - [**3. Calculations**](#3-calculations)
            - [**4. Performance**](#4-performance)
    - [**II. Cache Reuse**](#ii-cache-reuse)
        - [***Part #1***](#part-1-1)
            - [**1. Symbols**](#1-symbols-1)
            - [**2. Calculation**](#2-calculation-1)
            - [**3. Result**](#3-result)
        - [***Part #2***](#part-2-1)
            - [**1. Calculation**](#1-calculation)
            - [**2. Result**](#2-result)
        - [***Part #3***](#part-3-1)
            - [**1. Code**](#1-code-1)
            - [**2. Performance**](#2-performance)
        - [***Part #4***](#part-4)
            - [**1. Code**](#1-code-2)
            - [**2. Performance**](#2-performance-1)
    - [**III. Bonus**](#iii-bonus)
        - [***Part #1***](#part-1-2)
            - [**1. Code**](#1-code-3)
            - [**2. Performance**](#2-performance-2)
        - [***Part #2***](#part-2-2)
            - [**1. Code**](#1-code-4)
            - [**2. Performance**](#2-performance-3)
<center> 

# **CS211 Project1**

Name: Longze Su 

SID: 862188702

## **I. Register Reuse**

### ***Part #1***

</center> 

#### **1. Symbols**

 
Variable | Number | Unit | Description
-|-|-|-
CPF |  1/4  | cycle/double floating-point operations |  
MF | 2,000,000,000 | Hz | CPU clock frequency 
Delay | 100 | cycles | read/write one operand from/to MEM
n | 1000 | 1 | Matrix Dimension
FOps |  | double floating-point operations | 
DC |  | cycles | total delay cycles
Perf |  | Gflops | Performance
T | | s | time
Ops | | 1 | number of operand times
wastedRate | | 1 | wasted time divide total time


#### **2. Calculation** 

- *This is dgemm0*
``` C++
/* dgemm0: simple ijk version triple loop algorithms */ 
for (i = 0; i < n; i++) 
    for (j = 0; j < n; j++) 
        for (k = 0; k < n; k++) 
            c[i*n + j] += a[i*n + k]*b[k*n + j]; 
```
To calculate the total time of dgmm0, we have

$$ total T_0 = operation T_0 + wasted T_0 $$


Firstly, we know operation time of dgemm0 is 

$$ operationT_0 = \frac{FOps*CPF}{MF} $$

In the inner loop, we have 

$$ C += A*B $$

And there are totally **three** loops

Then the total double floating-point operations are

$$
FOps = 2*n^3
$$

The dimension of matrix is 1000, as a result, we get operation time of dgemm0 

$$
operationT_0 = \frac{[2*(1000)^3]*1/4}{2*10^9} = \frac{1}{4}s
$$

Secondly, the wasted time of dgemm0 is 

$$
wastedT_0 = \frac{DC_0}{MF}
$$

From $c[i*n + j] += a[i*n + k]*b[k*n + j]$ , we know the inner loop store operands and load operands of dgemm0

$$
innerOps_0 = 4
$$

There are three loops outside, DC of dgemm0 is

$$
DC_0 = innerOps_0 * Delay * n^3
$$

We get wasted time of dgemm0 

$$
wastedT_0 = \frac{400*(1000)^3}{2*10^9}=200s
$$

Finally, we get Total Time of dgemm0,

$$
totalT_0 = 200.25s 
$$

Wasted Time of dgemm0,

$$
wastedT_0 = 200s 
$$

and Wasted Rate of dgemm0

$$
wastedRate_0 = \frac{wastedT_0}{totalT_0}*100\% = 99.875\%
$$

- *This is dgemm1*
``` C++
/* dgemm1: simple ijk version triple loop algorithms with register reuse*/ 
for (i = 0; i < n; i++) 
    for (j = 0; j < n; j++) 
        register double r = c[i*n + j]; 
        for (k = 0; k < n; k++) 
            r += a[i*n + k]*b[k*n + j];
        c[i*n + j] = r; 
```

The operand time of dgemm0 is simmilar to dgemm1

$$
operandT_1 = 0.25s
$$

However, there are one load and one store in the second loop, and only two load in the inner loop. 

$$
innerOps_1 = 2 \\
secondLoopOps_1 = 2
$$

The operands of dgemm1 are 

$$
DC_1 = innerOps_1*Delay*n^3 + secondLoopOps_1*Delay*n^2
$$

The wasted time of dgemm1 is 

$$
wastedT_1 = \frac{DC_1}{MF} = \frac{2*100*(1000)^3+2*100*(1000)^2}{2*10^9} = 100.1s
$$

Finally, we get Total Time of dgemm1,

$$
totalT_1 = wastedT_1 + operandT_1 = 100.35s'
$$

Wasted Time of dgemm1,

$$
wastedT_1 = 100.1s
$$

and Wasted Rate of dgemm1

$$
wastedRate_1 = \frac{wastedT_0}{totalT_0}*100\% = 99.751\%
$$


#### **3. Performance**

##### **Calculations**

For dgemm0 and dgemm1, they have the same FOps 

$$ FOps_0 = FOps_1 = 2*n^3 $$

The results are

n | 64 | 128 | 256 | 512 | 1024 | 2048 
-|-|-|-|-|-|-
dgemm0 (FOps) | 524,288 | 4,194,304 | 33,554,432 | 268,435,456 | 2,147,483,648 | 17,179,869,184
dgemm1 (FOps) | 524,288 | 4,194,304 | 33,554,432 | 268,435,456 | 2,147,483,648 | 17,179,869,184

#### **4.Results**

Time

n | 64 | 128 | 256 | 512 | 1024 | 2048 
-|-|-|-|-|-|-

Performance

n | 64 | 128 | 256 | 512 | 1024 | 2048 
-|-|-|-|-|-|-


<center>

### ***Part #2***

</center>

#### **1. Code**

&ensp;&ensp; *This is dgemm2*

```C++
c = (double *) calloc(sizeof(double), n*n);

/* Multiply n x n matrices a and b  */
void mmm(double *a, double *b, double *c, int n) {
    int i, j, k;
    for (i = 0; i < n; i += 2)
        for (j = 0; j < n; j += 2) { 

            // define 4 registers for c 
            register double c00 = c[i*n + j]; 
            register double c01 = c[i*n + j+1]; 
            register double c10 = c[(i+1)*n + j]; 
            register double c11 = c[(i+1)*n + j+1]

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
```

#### **2. Calculations**

For dgemm2, it has 16 operations in the inner loop 

$$ FOps_2 = 16*(n/2)^3 == FOps_0 $$

The results are

n | 64 | 128 | 256 | 512 | 1024 | 2048 
-|-|-|-|-|-|-
dgemm2 (FOps) | 524,288 | 4,194,304 | 33,554,432 | 268,435,456 | 2,147,483,648 | 17,179,869,184

#### **3. Performance**

Time

n | 64 | 128 | 256 | 512 | 1024 | 2048 
-|-|-|-|-|-|-

Performance

n | 64 | 128 | 256 | 512 | 1024 | 2048 
-|-|-|-|-|-|-



<center>

### ***Part #3***

</center>

#### **1. Analysis** 

There are 16 registers, considering increase the size of blocks. The block matrix dimension should vary from 2 to 4. 

Assume the n is the common multiple of 3 and 4.  

The theoretical operands of dgemm2 are 
$$ Ops_2 = innerOps + outerOps = 2*4*(n/2)^3 + 2*4*(n/2)^2 = n^3 + 2*n^2 $$

Because C have both save and load operands, C has higher priority of register allocation.  

If 4\*4 uses 16 registers to store C, there are $16*8*(n/4)^3$ load in the inner loop, add outer operands $store+load = 2*16*(n/4)^2$,total operands are
$$ Ops_(4*4) = 2*n^3 + 2*n^2 $$

3\*4 will use 9 registers to store C, there are 7 remaining registers, A and B requires 8 register in each turn if registers are reused. So one element can't use register in each turn. 
$$ Ops_(3*4) = 3*(7+3)*(n/4)*(n/3)^2 + 2*9*(n/3)^2 = \frac{5}{6}*n^3 + 2*n^2 $$ 

We can see that if we allocate all C blocks to register, the outer loop operand numbers are the same

2\*4 uses 4 registers to store C, and uses 8 registers to store A and B in each turn
$$ Ops(2*4) = 2*8*(n/4)*(n/2)^2 +2*n^2 = n^3 + 2*n^2 $$

3\*3 uses 9 registers to store C, and uses 6 registers to store A and B in each turn 
$$ Ops(3*3) = 3*6*(n/3)^3+2*n^2 = \frac{2}{3}*n^3 + 2*n^2 $$

3\*1 has theoretically similar performance to 3\*3

Theoretical Performance (from slow to quick)
Blocks | 4*4 | 2*2 | 2*4 | 3*4 | 3*3 | 3*1
-|-|-|-|-|-|-
Register Used (maximum 16) | 16 | 12 | 12 | 16 | 15 | 15
Element not in Register in each inner loop | 8 | 0 | 0 | 1 | 0 | 0
Theoretical inner Operands ($*n^3$) | 2 | 1 | 1 | 5/6 | 2/3 | 2/3


#### **2. Code**
- *This is dgemm3*
```C++
    // 3*3 
    for (i = 0; i < n; i += 3)
        for (j = 0; j < n; j += 3) { 

            // define 9 registers for c 
            register double c00 = c[i*n + j]; 
            register double c01 = c[i*n + j+1]; 
            register double c02 = c[i*n + j+2];
            register double c10 = c[(i+1)*n + j]; 
            register double c11 = c[(i+1)*n + j+1]
            register double c12 = c[(i+1)*n + j+2]
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
```

#### **3. Calculations**

For dgemm3, it has $3*9*2 = 54$ operations in the inner loop 

$$ FOps_2 = 54*(n/3)^3 == FOps_0 $$

The results are

n | 66 | 132 | 258 | 516 | 1026| 2052
-|-|-|-|-|-|-
dgemm (FOps) | 574,992 | 4,599,936 | 34,347,024‬ | 274,776,192 | 2,160,091,152‬ | 17,280,729,216‬

#### **4. Performance**

<center>

## **II. Cache Reuse** 

### ***Part #1***

</center>

#### **1. Symbols**

 
Variable | Number | Unit | Description
-|-|-|-
L |  10  | doubles |  cache line
CS | 600 | doubles | cache size 
n | (10000) | 1 | Matrix Dimension
CM | | 1 | cache misses
CR | | 1 | cache read
BS|10|1|Block size

#### **2. Calculation** 

*This is dgemm4* 
```C++
// ijk simple triple loop 
// ikj, jik, jki, kij, kji are negotiated
for (i=0; i<n; i++)
    for (j=0; j<n; j++) 
        register double r=c[i*n+j]; 
        for (k=0; k<n; k++) 
            r += a[i*n+k]*b[k*n+j]; 
        c[i*n+j]=r;
```
Firstly, when $n=10000$, because $L=10$ and $CS=600$, for all the inner loop

For the column, we have: $columnCM = n$

For the row, we have: $rowCM = 0.1n$

For the register variable, the cache is always not reused, we have: $rCM=1$ 

For ijk and jik, we have $fixedC+=rowA*columnB$

The inner loop cache misses are 

$$ inCM_1 = inCM_2 = 1.1n+1 $$

For kij and ikj, we have $rowC+=fixedA*rowB$ 

The inner loop cache misses are 

$$ inCM_3 = inCM_4 = 0.2n+1 $$

For kji and jki, we have $columnC+=columnA*fixedB$

The inner loop cache misses are 

$$ inCM5 = inCM_6 = 2n+1 $$ 

As a result, we get 

$$ CM_1 = CM_2 = 1.1n^3 + n^2 $$
$$ CM_3 = CM_4 = 0.2n^3 + n^2 $$
$$ CM_5 = CM_6 = 2n^3 + n^2 $$

Because for the register variable, it has only two outer layer loops cache read, All the cache read are 
$$ CR = 2n^3+n^2 $$

Secondly, when $n=10$, because $L=10$ and $CS=600$, for all the inner loop, 

Cache has $600>3*100$, so it can store all of matrices, only the first one of each row will miss, for each first element in each row $eCM = 1$, others are all $oCM=0$

For all the functions, we have 
$$ CM = \frac{eCM*3}{L}*n^2 = 0.3n^2 $$

Same as n = 10000, $CR = 2n^3+n^2$

#### **3. Result**
*Cache miss per element for $n=10000$*
matrix\Type|ijk|jik|ikj|kij|jki|kji
-|-|-|-|-|-|-
$A[i][k]$|`k%10==0?n:0`|`k%10==0?n:0`|1|1|n|n
$B[k][j]$|n|n|`j%10==0?n:0`|`j%10==0?n:0`|1|1
$C[i][j]$|1|1|`j%10==0?n:0`|`j%10==0?n:0`|n|n

*Cache miss per element for $n=10$*
matrix\Type|ijk|jik|ikj|kij|jki|kji
-|-|-|-|-|-|-
$A[i][k]$|`k%10==0?1:0`|`k%10==0?1:0`|`j%10==0?1:0`|`j%10==0?1:0`|`i%10==0?1:0`|`i%10==0?1:0`
$B[k][j]$|`k%10==0?1:0`|`k%10==0?1:0`|`j%10==0?1:0`|`j%10==0?1:0`|`i%10==0?1:0`|`i%10==0?1:0`
$C[i][j]$|`k%10==0?1:0`|`k%10==0?1:0`|`j%10==0?1:0`|`j%10==0?1:0`|`i%10==0?1:0`|`i%10==0?1:0`

*Cache miss* 
n\Type|ijk|jik|ikj|kij|jki|kji
-|-|-|-|-|-|-
1,0000|$1.1n^3+n^2$|$1.1n^3+n^2$|$0.2n^3 + n^2$|$0.2n^3 + n^2$|$2n^3 + n^2$|$2n^3 + n^2$
10|$0.3n^2$|$0.3n^2$|$0.3n^2$|$0.3n^2$|$0.3n^2$|$0.3n^2$

*Cache miss percentages*
n\Type|ijk|jik|ikj|kij|jki|kji
-|-|-|-|-|-|-
1,0000|55%|55%|10%|10%|100%|100%
10|1.43%|1.43%|1.43%|1.43%|1.43%|1.43%

<center>

### ***Part #2***

</center>

#### **1. Calculation** 

*This is dgemm5*
```C++
// ijk blocked triple loop 
// ikj, jik, jki, kij, kji are negotiated
/* Multiply n x n matrices a and b  */
void mmm(double *a, double *b, double *c, int n) {
    int i, j, k;
    for (i = 0; i < n; i+=B)
	for (j = 0; j < n; j+=B)
            for (k = 0; k < n; k+=B)
		    /* B x B mini matrix multiplications */
                for (i1 = i; i1 < i+B; i1++)
                    for (j1 = j; j1 < j+B; j1++)
                        for (k1 = k; k1 < k+B; k1++)
	                    c[i1*n+j1] += a[i1*n + k1]*b[k1*n + j1];
```
Because $n=10000$, $BS=10$, $L=10$ and $CS=600$: $CS>3*BS^2$, all the blocks can be stored in the cache. 

We also know that the inner three loops have the same order with the outer three loops. 

In the inner three loops, A, B and C will both miss the first element in each row, after i, k changed, A needs to move, and after k, j changed, B needs to move. While C will only move when i,j changed. 

For ijk, A, B need to refresh their block in the k loop, C only needs to refresh at the first time. 

After a total loop of k

$$ blockCM_A = blockCM_B = n/BS*(BS)^2/L = n$$ 
$$ blockCM_C = (BS)^2/L = BS $$ 
$$ blockCM = 2*n*(n/BS)^2 + BS*(n/BS)^2 = 2/BS^2*n^3 + 1/BS*n^2 $$

Same as part I, $CR = 2n^3+n^2$

Other algorithms are the similar.

#### **2. Result**

*Cache miss per element for $n=10000$ and $BS=10$*
matrix\Type|ijk|jik|ikj|kij|jki|kji
-|-|-|-|-|-|-
$A[i][k]$|`k%10==0?n/BS:0`|`k%10==0?n/BS:0`|`j%10==0?1:0`|`j%10==0?1:0`|`i%10==0?n/BS:0`|`i%10==0?n/BS:0`
$B[k][j]$|`k%10==0?n/BS:0`|`k%10==0?n/BS:0`|`j%10==0?n/BS:0`|`j%10==0?n/BS:0`|`i%10==0?n/BS:0`|`i%10==0?n/BS:0`
$C[i][j]$|`k%10==0?1:0`|`k%10==0?1:0`|`j%10==0?n/BS:0`|`j%10==0?n/BS:0`|`i%10==0?1:0`|`i%10==0?1:0`

*Cache miss* 
n\Type|ijk|jik|ikj|kij|jki|kji
-|-|-|-|-|-|-
1,0000|$0.02n^3+0.1n^2$|$0.02n^3+0.1n^2$|$0.02n^3+0.1n^2$|$0.02n^3+0.1n^2$|$0.02n^3+0.1n^2$|$0.02n^3+0.1n^2$

*Cache miss percentages*
n\Type|ijk|jik|ikj|kij|jki|kji
-|-|-|-|-|-|-
1,0000|1%|1%|1%|1%|1%|1%

<center>

### ***Part #3***

</center>

#### **1. Code**
*This is dgemm5*

#### **2. Performance**


<center>

### ***Part #4***

</center>

#### **1. Code**
*This is dgemm6*

#### **2. Performance**



<center>

## **III. Bonus** 

### ***Part #1***

</center>


#### **1. Code**
*This is dgemm7*

#### **2. Performance**


<center>

### ***Part #2***

</center>


#### **1. Code**
*This is dgemm8*

#### **2. Performance**

