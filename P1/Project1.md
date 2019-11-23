<!--
 * @Author: Longze Su
 * @Date: 2019-10-12 16:13:59
 * @Description: CS211_Project1
 * @LastEditTime: 2019-10-18 17:42:29
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

n | 66 | 126 | 258 | 510 | 1026 | 2046 
-|-|-|-|-|-|-
dgemm0 (FOps) | 574,992 | 4,000,752 | 34,347,024 | 265,302,000 | 2,160,091,152 | 17,129,586,672‬
dgemm1 (FOps) | 574,992 | 4,000,752 | 34,347,024 | 265,302,000 | 2,160,091,152 | 17,129,586,672‬

Maximum Difference

diff | 66 | 126 | 258 | 510 | 1026 | 2046 
-|-|-|-|-|-|-
dgemm0 | 0.0 | 0.0 | 0.0 | 0.0 | 0.0 | 0.0
dgemm1 | 0.0 | 0.0 | 0.0 | 0.0 | 0.0 | 0.0

#### **4.Results**

Time

n | 66 | 126 | 258 | 510 | 1026 | 2046 
-|-|-|-|-|-|-
dgemm0(seconds)|0.00061|0.00388|0.03889|0.58626|5.35272|51.74367
dgemm1(seconds)|0.00054|0.00365|0.03521|0.49139|3.86265|38.18782

Performance

n | 66 | 126 | 258 | 510 | 1026 | 2046 
-|-|-|-|-|-|-
dgemm0(GFlops)|0.9426|<font color=#DC143C>1.0311</font>|0.8832|0.4525|0.4035|0.3310
dgemm1(GFlops)|1.0648|<font color=#DC143C>1.0961</font>|0.9755|0.5399|0.5592|0.4486

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

n | 66 | 126 | 258 | 510 | 1026 | 2046 
-|-|-|-|-|-|-
dgemm2 (FOps) | 574,992 | 4,000,752 | 34,347,024 | 265,302,000 | 2,160,091,152 | 17,129,586,672‬

#### **3. Performance**

Time

n | 66 | 126 | 258 | 510 | 1026 | 2046 
-|-|-|-|-|-|-
dgemm2(second)|0.00016|0.00144|0.01421|0.16182|1.99811|28.49845

Performance

n | 66 | 126 | 258 | 510 | 1026 | 2046 
-|-|-|-|-|-|-
dgemm2(GFlops)|<font color=#DC143C>3.5937</font>|2.7783‬|2.4171|1.6395|1.0811|0.6011
dgemm0(GFlops)|0.9426|<font color=#DC143C>1.0311</font>|0.8832|0.4525|0.4035|0.3310
dgemm1(GFlops)|1.0648|<font color=#DC143C>1.0961</font>|0.9755|0.5399|0.5592|0.4486

Maximum Difference

diff | 66 | 126 | 258 | 510 | 1026 | 2046 
-|-|-|-|-|-|-
dgemm2 | 0.0 | 0.0 | 0.0 | 0.0 | 0.0 | 0.0

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

n | 66 | 126 | 258 | 510 | 1026 | 2046 
-|-|-|-|-|-|-
dgemm3 (FOps) | 574,992 | 4,000,752 | 34,347,024 | 265,302,000 | 2,160,091,152 | 17,129,586,672‬


#### **4. Performance**

Time

n | 66 | 126 | 258 | 510 | 1026 | 2046 
-|-|-|-|-|-|-
dgemm3(second)|0.00012|0.00099|0.01095|0.10390|1.09313|5.68864

Performance 

n | 66 | 126 | 258 | 510 | 1026 | 2046 
-|-|-|-|-|-|-
dgemm3(GFlops)|<font color=#DC143C>4.7916</font>|4.0412|3.1367|2.5534|1.9761|3.0112
dgemm2(GFlops)|<font color=#DC143C>3.5937</font>|2.7783‬|2.4171|1.6395|1.0811|0.6011
dgemm0(GFlops)|0.9426|<font color=#DC143C>1.0311</font>|0.8832|0.4525|0.4035|0.3310
dgemm1(GFlops)|1.0648|<font color=#DC143C>1.0961</font>|0.9755|0.5399|0.5592|0.4486


Maximum Difference

diff | 66 | 126 | 258 | 510 | 1026 | 2046 
-|-|-|-|-|-|-
dgemm3 | 0.0 | 0.0 | 0.0 | 0.0 | 0.0 | 0.0

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

*This is dgemmijk*
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

Same as part I, $CR = 2n^3+n^3/BS$

Other algorithms are the similar.

#### **2. Result**

*Cache miss per element for $n=10000$ and $BS=10$*
matrix\Type|ijk|jik|ikj|kij|jki|kji
-|-|-|-|-|-|-
$A[i][k]$|`k%10==0?n/BS:0`|`k%10==0?n/BS:0`|`j%10==0?1:0`|`j%10==0?1:0`|`i%10==0?n/BS:0`|`i%10==0?n/BS:0`
$B[k][j]$|`k%10==0?n/BS:0`|`k%10==0?n/BS:0`|`j%10==0?n/BS:0`|`j%10==0?n/BS:0`|`i%10==0?1:0`|`i%10==0?1:0`
$C[i][j]$|`k%10==0?1:0`|`k%10==0?1:0`|`j%10==0?n/BS:0`|`j%10==0?n/BS:0`|`i%10==0?n/BS:0`|`i%10==0?n/BS:0`
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
*This is dgemmijk*

See [***Part #2***](#part-2-1)

*This is dgemmijk_blockn*

See [***Part #4***](#part-4)

#### **2. Performance**


*The blocksize is 10, the matrixsize is 2046*

Operation numbers are all 17,129,586,672

n\Type|ijk|jik|ikj|kij|jki|kji
-|-|-|-|-|-|-
no block|39.23978|20.60740|16.95061|<font color=#DC143C>16.41684</font>|64.02065|64.34116
block|19.93646|<font color=#DC143C>16.26251</font>|21.25568|20.31971|21.35640|33.54339

Performance

n\Type|ijk|jik|ikj|kij|jki|kji
-|-|-|-|-|-|-
no block|0.4365|0.8312|1.0105|<font color=#DC143C>1.0434</font>|0.2676|0.2662
block|0.8592|<font color=#DC143C>1.0533</font>|0.8059|0.8430|0.8020|0.5107

Difference

n\Type|ijk|jik|ikj|kij|jki|kji
-|-|-|-|-|-|-
no block|0.0|0.0|0.0|0.0|0.0|0.0
block|0.0|0.0|0.0|0.0|0.0|0.0

Optimize Block Size

*matrixsize = 2048*

Operation Numbers are all 17,179,869,184‬

Time & Performance(= Time/Flops)

B(blocksize)\Type|ijk|jik|ikj|kij|jki|kji
-|-|-|-|-|-|-
32|82.8176|84.3773|89.6571|89.6571|104.902|120.757
64|<font color=#DC143C>80.7872</font>|82.8945|85.0216|85.0216|99.0263|117.133
128|81.2457|<font color=#DC143C>82.5721</font>|<font color=#DC143C>82.6826</font>|<font color=#DC143C>82.6826</font>|<font color=#DC143C>87.703</font>|<font color=#DC143C>116.266</font>
256|132.493|136.547|92.1752|92.1752|91.938|184.099
512|146.807|140.909|115.511|115.511|108.756|193.609
1024|281.297|310.537|99.501|99.501|105.739|366.994

Block 128 have better performance

Difference

B(blocksize)\Type|ijk|jik|ikj|kij|jki|kji
-|-|-|-|-|-|-
32|0.0|0.0|0.0|0.0|0.0|0.0
64|0.0|0.0|0.0|0.0|0.0|0.0
128|0.0|0.0|0.0|0.0|0.0|0.0
256|0.0|0.0|0.0|0.0|0.0|0.0
512|0.0|0.0|0.0|0.0|0.0|0.0
1024|0.0|0.0|0.0|0.0|0.0|0.0

<center>

### ***Part #4***

</center>

#### **1. Code**
*This is dgemmijk_blockn*

```C++
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

```

#### **2. Performance**

Both cache block and register block 

*n = 2046, blocksize = 66* 

Operation Numbers are all 17,129,586,672

Time

Optimize Flag|O0|O1|O2|O3
-|-|-|-|-|-
Time|4.64026|4.65767|4.64383|4.65082

Performance

Optimize Flag|O0|O1|O2|O3
-|-|-|-|-|-
GFlops|<font color=#DC143C>3.6915</font>|3.6777|3.6887|3.6831

<center>

## **III. Bonus** 

### ***Part #1***

</center>


#### **1. Code**
*This is dgemm4*
```C++
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
```


#### **2. Performance**

Operation Numbers

for dgemm4 $Ops=27*(n/2)^3$

n|64|128|256|512|1024|2048
-|-|-|-|-|-|-
dgemm2|524,288‬|4,194,304|33,554,432|268,435,456|2,147,483,648‬|17,179,869,184‬
dgemm4|1,769,472‬|14,155,776|113,246,208‬|905,969,664‬|7,247,757,312‬‬|57,982,058,496‬

Time

n|64|128|256|512|1024|2048
-|-|-|-|-|-|-
dgemm2(second)|0.000586987|0.00419307|0.0440731|0.360863|4.31796|60.4289
dgemm4(second)|0.000628948|0.00524998|0.0564129|0.460355|4.90356|66.7572

Performance

n|64|128|256|512|1024|2048
-|-|-|-|-|-|-
dgemm2(GFlops)|0.8932|<font color=#DC143C>1.0003</font>|0.7613|0.7439|0.4973|0.2843
dgemm4(GFlops)|<font color=#DC143C>2.8134</font>|2.6963|2.0074|1.9680|1.4779|0.8684

<center>

### ***Part #2***

</center>


#### **1. Code**
*This is dgemm5*

Cache reuse and Rigester reuse strassen

```C++
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
```
#### **2. Performance**

Operation Numbers

n|2048
-|-
dgemm_ijk_block|‬17,179,869,184‬
degmm5(strassen modified)|‬‬57,982,058,496‬

Time

*matrixsize is 2048, change the blocksize*

B(blocksize)|64|128|256|512|1024
-|-|-|-|-|-
dgemm_ijk_block|120.301|115.83|117.525|188.534|202.71|308.41
degmm5(strassen modified)|56.7539|54.6359|61.8577|75.1173|83.4699|122.258


Performance
B(blocksize)|64|128|256|512|1024
-|-|-|-|-|-
dgemm_ijk_block|0.1428|<font color=#DC143C>0.1483</font>|0.1462|0.0911|0.0848|0.0557
degmm5(strassen modified)|1.0216|<font color=#DC143C>1.0612</font>|0.9373|0.7719|0.6946|0.4742