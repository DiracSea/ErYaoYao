/*
 * @Author: Longze Su
 * @Date: 2019-10-13 04:02:45
 * @Description: CS211_Project1
 * @LastEditTime: 2019-10-13 14:40:48
 * @LastEditors: Longze Su
 */
// II 
#pragma once 
typedef void (*gemm)(double *, double *, double *, int);
typedef void (*gemm_block)(double *, double *, double *, int, int);

void dgemm_ijk(double* a, double* b, double* c, int n);
void dgemm_jik(double* a, double* b, double* c, int n);
void dgemm_ikj(double* a, double* b, double* c, int n);
void dgemm_kij(double* a, double* b, double* c, int n);
void dgemm_jki(double* a, double* b, double* c, int n);
void dgemm_kji(double* a, double* b, double* c, int n);

void dgemm_ijk_blockn(double* a, double* b, double* c, int n, int B);
void dgemm_jik_blockn(double* a, double* b, double* c, int n, int B);
void dgemm_ikj_blockn(double* a, double* b, double* c, int n, int B);
void dgemm_kij_blockn(double* a, double* b, double* c, int n, int B);
void dgemm_jki_blockn(double* a, double* b, double* c, int n, int B);
void dgemm_kji_blockn(double* a, double* b, double* c, int n, int B);
