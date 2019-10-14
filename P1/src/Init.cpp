/*
 * @Author: Longze Su
 * @Date: 2019-10-12 15:44:56
 * @Description: CS211_Project1
 * @LastEditTime: 2019-10-13 04:15:13
 * @LastEditors: Longze Su
 */

#include "functions.hpp"
#include <cstdlib> 
#include <cmath> 
#include <ctime> 
#include <iostream> 

#define MAX_ELE_1 1000
#define MAX_ELE_2 100000

Init::Init(){}
Init::~Init(){}

void Init::init_matrix(double* a, double* b, double* c, int size)
{

    // a = new double[size]; 
    // b = new double[size]; 
    // c = new double[size]; 

    for (int i = 0; i < size; i++) 
    { 
        a[i] = (double)(rand() % MAX_ELE_1) + 1e-5 * (rand() % MAX_ELE_2);  
        b[i] = (double)(rand() % MAX_ELE_1) + 1e-5 * (rand() % MAX_ELE_2); 
        c[i] = 0;
    }
    // std::cout << "first:" << std::endl;
    // std::cout << a[0] << " " << a[size-1] << std::endl;
    // std::cout << b[0] << " " << b[size-1] << std::endl;
    // std::cout << c[0] << " " << c[size-1] << std::endl;
}

void Init::term_matrix(double* a, double* b, double* c)
{
    delete a; 
    delete b; 
    delete c; 
}