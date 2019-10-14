/*
 * @Author: Longze Su
 * @Date: 2019-10-12 17:07:23
 * @Description: CS211_Project1
 * @LastEditTime: 2019-10-14 01:55:22
 * @LastEditors: Longze Su
 */
// DGEMM_HPP
#pragma once 

#include <string> 
#include <cstring> 

// global arrays of n
const int num2[6] = {64,128,256,512,1024,2048}; 
const int num3[6] = {66,132,258,516,1026,2052};
const int block[6] = {32,64,128,256,512,1024};
const int block3[5] = {6,33,66,186,1023};

// initilization class
class Init
{
public: 
    Init (); 
    ~Init (); 
    void init_matrix(double* a, double* b, double* c, int size); // initialization of matrix
    void term_matrix(double* a, double* b, double* c); // free space
}; 

// validation class
class Validate
{
public: 
    Validate (); 
    ~Validate (); 
    double validate(double* c1, double* c2, int size);
};

// time class
class Time
{
public:
    Time(); 
    ~Time(); 
    double get_time(); // second
}; 

// io class
class IO
{
public: 
    IO(); 
    ~IO(); 
    void output(std::string info, int dgemm, int n, double t);
    void output_b(std::string info, int block_size, int n, double t);
    void output_diff(int dgemm, int diff);
};

// algorithm class
class Dgemm
{
public: 
    Dgemm(); 
    ~Dgemm(); 

    // I
    void dgemm0(double* a, double* b, double* c, int n); 
    void dgemm1(double* a, double* b, double* c, int n);
    void dgemm2(double* a, double* b, double* c, int n);
    void dgemm3(double* a, double* b, double* c, int n);

    // II
    void dgemm_3x3_blockn(double* a, double* b, double* c, int n, int B);
    void dgemm_ijk_blockn(double* a, double* b, double* c, int n, int B); 
    
    void dgemm4(double* a, double* b, double* c, int n);
    void dgemm5(double* a, double* b, double* c, int n, int B);
}; 

