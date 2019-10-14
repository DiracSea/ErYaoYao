/*
 * @Author: Longze Su
 * @Date: 2019-10-12 16:53:42
 * @Description: CS211_Project1
 * @LastEditTime: 2019-10-13 01:08:32
 * @LastEditors: Longze Su
 */

#include "functions.hpp"
#include <cstdlib> 
#include <cmath> 

Validate::Validate(){}
Validate::~Validate(){}

double Validate::validate(double* c1, double* c2, int size)
{
    double max_diff = fabs(c1[0] - c2[0]); 

    for (int i = 1; i < size; i++) 
    {
        double diff = fabs(c1[i] - c2[i]); 
        if (diff > max_diff) 
            max_diff = diff; 
    }
    return max_diff > 1e-3 ? max_diff : 0; 
}