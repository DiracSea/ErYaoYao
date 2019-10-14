/*
 * @Author: Longze Su
 * @Date: 2019-10-13 13:09:41
 * @Description: CS211_Project1
 * @LastEditTime: 2019-10-13 20:36:49
 * @LastEditors: Longze Su
 */


#include "src/functions.hpp"
#include "src/dg.hpp"
#include <iostream> 
#include <algorithm> 
#include <ctime> 

int main() 
{
    int n = 2046; 
    int size = n*n; 
    double c1, c2, c3; 
    srand(time(NULL)); 
    int i; 

    for (i = 0; i < 5; i++) 
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
        std::cout << "block: " << block3[i] << std::endl; 

        Dgemm dg; 
        dg.dgemm3(a, b, c1, n); 
        dg.dgemm_ijk_blockn(a, b, c2, n, block3[i]);
        dg.dgemm_3x3_blockn(a, b, c3, n, block3[i]);

        Validate valid; 
        double max_diff1 = valid.validate(c1, c2, size); 
        double max_diff2 = valid.validate(c1, c3, size); 

        // output difference log
        IO io; 
        io.output_diff(123, max_diff1); 
        io.output_diff(303, max_diff2);

        // free matrix space
        init.term_matrix(a, b, c); 
        init.term_matrix(c1, c2, c3); 
    }

    return 0; 
}