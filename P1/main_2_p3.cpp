/*
 * @Author: Longze Su
 * @Date: 2019-10-13 04:22:38
 * @Description: CS211_Project1
 * @LastEditTime: 2019-10-13 18:08:19
 * @LastEditors: Longze Su
 */


#include "src/functions.hpp"
#include "src/dg.hpp"
#include <iostream> 
#include <algorithm> 
#include <ctime> 

int main() 
{
    int n = 2050; 
    int size = n*n; 
    double c1, c2, c3; 
    srand(time(NULL)); 
    int i; 

    // function arrays
    char *func_name[] = {"ijk", "jik", "ikj", "kij", "jki", "kji"};
    gemm alg1[] = {&dgemm_ijk, &dgemm_jik, &dgemm_ikj, &dgemm_kij, &dgemm_jki, &dgemm_kji};
    gemm_block alg2[] = {&dgemm_ijk_blockn, &dgemm_jik_blockn, &dgemm_ikj_blockn, &dgemm_kij_blockn, &dgemm_jki_blockn, &dgemm_kji_blockn};
    for (i = 0; i < 6; i++)
    {   
        // initilization
        double* a = new double[size]; 
        double* b = new double[size]; 
        double* c = new double[size]; 

        Init init; 
        init.init_matrix(a, b, c, size);

        double* c1 = new double[size]; 
        double* c2 = new double[size]; 
        double* c3 = new double[size]; 

        // deep copy c
        std::copy(c, c + size, c1);
        std::copy(c, c + size, c2);
        std::copy(c, c + size, c3);

        // matrix multiplication
        std::cout << func_name[i] << std::endl; 

        Dgemm dg; 
        dg.dgemm2(a, b, c1, n);
        alg1[i](a, b, c2, n); 
        alg2[i](a, b, c3, n, 10); 

        Validate valid; 
        double max_diff1 = valid.validate(c1, c2, size); 
        double max_diff2 = valid.validate(c1, c3, size); 

        // output difference log
        IO io; 
        io.output_diff(123, max_diff1); 
        io.output_diff(12310, max_diff2);

        // free matrix space
        init.term_matrix(a, b, c); 
        init.term_matrix(c1, c2, c3); 
    }
    
    return 0; 
}