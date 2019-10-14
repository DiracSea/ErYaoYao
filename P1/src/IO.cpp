/*
 * @Author: Longze Su
 * @Date: 2019-10-12 19:57:32
 * @Description: CS211_Project1
 * @LastEditTime: 2019-10-13 03:44:28
 * @LastEditors: Longze Su
 */

#include "functions.hpp" 
#include <iostream>

#include <cstdlib> 
extern "C"
{
    #include <sys/time.h> 
} 

#include <string> 
#include <cstring> 

using std::string; 

Time::Time(){}
Time::~Time(){}

double Time::get_time()
{
    struct timeval time;
    gettimeofday(&time, NULL); 
    return (time.tv_sec + 1e-6*time.tv_usec); 
}

IO::IO(){}
IO::~IO(){}

void IO::output(string info, int dgemm, int n, double t) 
{
    std::cout << info << ": dgemm" << dgemm << " - When n = " << n << ": elapsed time is " << t << "seconds.\n"; 
}

void IO::output_b(string info, int block_size, int n, double t) 
{
    if (block_size == 0) 
        std::cout << info << " - When n = " << n << ": elapsed time is " << t << "seconds.\n"; 
    else
        std::cout << info << ": block_size is " << block_size << " - When n = " << n << ": elapsed time is " << t << "seconds.\n"; 
}

void IO::output_diff(int dgemm, int diff) 
{
    std::cout << "dgemm" << dgemm << "'s max difference is " << diff << ", result is " << (diff==0?"right~":"wrong!") << std::endl;
}

