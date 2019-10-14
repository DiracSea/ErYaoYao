/*
 * @Author: Longze Su
 * @Date: 2019-10-14 01:09:29
 * @Description: CS211_Project1
 * @LastEditTime: 2019-10-14 01:14:17
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
    srand(time(NULL)); 
    for (i = 0; i < 6; i++) 
    {
        // init
        int size = num2[i]*num2[i]; 
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
        dg.dgemm2(a, b, c1, num2[i]);
        dg.dgemm4(a, b, c2, num2[i]); 

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