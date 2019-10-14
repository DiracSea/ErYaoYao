/*
 * @Author: Longze Su
 * @Date: 2019-10-14 02:00:03
 * @Description: CS211_Project1
 * @LastEditTime: 2019-10-14 02:06:57
 * @LastEditors: Longze Su
 */
#include "src/functions.hpp"
#include <iostream> 
#include <algorithm> 
#include <ctime> 

int main()
{
    double c1, c2;
    int i; 
    int n = 2048; 
    int size = n*n; 
    srand(time(NULL)); 
    
    for (i = 0; i < 6; i++) 
    {
        // init
        double* a = new double[size]; 
        double* b = new double[size]; 
        double* c = new double[size];

        Init init; 
        init.init_matrix(a, b, c, size); 

        double* c1 = new double[size]; 
        double* c2 = new double[size]; 

        // deep copy c
        std::copy(c, c + size, c1);
        std::copy(c, c + size, c2);

        // matrix multiplication
        Dgemm dg; 
        dg.dgemm_ijk_blockn(a, b, c1, n, block[i]);
        dg.dgemm5(a, b, c2, n, block[i]); 

        Validate valid; 
        double max_diff1 = valid.validate(c1, c2, size); 

        IO io; 
        io.output_diff(1, max_diff1); 

        // free matrix space
        init.term_matrix(a, b, c); 
        delete c1;
        delete c2;
    }

    return 0; 
}