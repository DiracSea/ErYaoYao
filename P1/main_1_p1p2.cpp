/*
 * @Author: Longze Su
 * @Date: 2019-10-12 20:13:32
 * @Description: CS211_Project1
 * @LastEditTime: 2019-10-13 04:18:25
 * @LastEditors: Longze Su
 */
// main function of problem I, part1 and part2 

#include "src/functions.hpp"
#include <iostream> 
#include <algorithm> 
#include <ctime> 

int main() 
{
    double c1, c2, c3; 
    int i;
    srand(time(NULL));
    for (i = 0; i < 6; i++) 
    {
        // initialize matrix
        int size = num2[i]*num2[i]; 
        double* a = new double[size]; 
        double* b = new double[size]; 
        double* c = new double[size]; 
        // std::cout << a[0] << " " << a[size-1] << std::endl;
        // std::cout << b[0] << " " << b[size-1] << std::endl;
        // std::cout << c[0] << " " << c[size-1] << std::endl;

        Init init; 
        init.init_matrix(a, b, c, size);

        // std::cout << "init:" << std::endl;
        // std::cout << a[0] << " " << a[size-1] << std::endl;
        // std::cout << b[0] << " " << b[size-1] << std::endl;
        // std::cout << c[0] << " " << c[size-1] << std::endl;

        double* c1 = new double[size]; 
        double* c2 = new double[size]; 
        double* c3 = new double[size]; 

        // deep copy c
        std::copy(c, c + size, c1);
        std::copy(c, c + size, c2);
        std::copy(c, c + size, c3);

        // matrix multiplication
        Dgemm dg; 
        dg.dgemm0(a, b, c1, num2[i]);
        dg.dgemm1(a, b, c2, num2[i]); 
        dg.dgemm2(a, b, c3, num2[i]); 

        // std::cout << "mm:" << std::endl;
        // std::cout << c1[0] << " " << c1[size-1] << std::endl; 
        // std::cout << c2[0] << " " << c2[size-1] << std::endl;
        // std::cout << c3[0] << " " << c3[size-1] << std::endl; 

        // validation, the base is dgemm0
        Validate valid; 
        double max_diff1 = valid.validate(c1, c2, size); 
        double max_diff2 = valid.validate(c1, c3, size); 

        // output difference log
        IO io; 
        io.output_diff(1, max_diff1); 
        io.output_diff(2, max_diff2);

        // free matrix space
        init.term_matrix(a, b, c); 
        init.term_matrix(c1, c2, c3); 
    }


    return 0;
}

