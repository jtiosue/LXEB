#ifndef METHODS_H_INCLUDED
#define METHODS_H_INCLUDED

#include <complex>

typedef std::complex<double> cnum;

long long factorial(long long k);

bool next_l(int n, int k, int *l);

cnum hafnian(int n, cnum **X);

void random_gaussian_matrix(int rows, int cols, cnum **X);

void XtrX(int rows, int cols, cnum **X, cnum **Y);

#endif