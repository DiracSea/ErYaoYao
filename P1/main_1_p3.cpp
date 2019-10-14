/*
 * @Author: Longze Su
 * @Date: 2019-10-13 04:14:21
 * @Description: CS211_Project1
 * @LastEditTime: 2019-10-13 14:38:14
 * @LastEditors: Longze Su
 */

#include "src/functions.hpp"
#include <iostream> 
#include <algorithm> 
#include <ctime> 

int main() 
{
    double c1, c2, c3, c4; 
    int i; 
    srand(time(NULL)); 
    for (i = 0; i < 6; i++) 
    {
        // initialize matrix
        int size = num3[i]*num3[i]; 
        double* a = new double[size]; 
        double* b = new double[size]; 
        double* c = new double[size];

        Init init; 
        init.init_matrix(a, b, c, size); 

        double* c1 = new double[size]; 
        double* c2 = new double[size]; 
        double* c3 = new double[size];
        double* c4 = new double[size]; 

        // deep copy c
        std::copy(c, c + size, c1);
        std::copy(c, c + size, c2);
        std::copy(c, c + size, c3);
        std::copy(c, c + size, c4);

        // mm
        Dgemm dg; 
        dg.dgemm0(a, b, c1, num3[i]);
        dg.dgemm1(a, b, c2, num3[i]); 
        dg.dgemm2(a, b, c3, num3[i]); 
        dg.dgemm3(a, b, c4, num3[i]); 

        // validation, the base is dgemm0
        Validate valid; 
        double max_diff1 = valid.validate(c1, c2, size); 
        double max_diff2 = valid.validate(c1, c3, size); 
        double max_diff3 = valid.validate(c1, c4, size); 

        // output difference log
        IO io; 
        io.output_diff(1, max_diff1); 
        io.output_diff(2, max_diff2);
        io.output_diff(3, max_diff3);

        // free matrix space
        init.term_matrix(a, b, c); 
        init.term_matrix(c1, c2, c3); 
        delete(c4); 
    }

    return 0;
}