#include "methods.h"
#include <algorithm>    // std::next_permutation, std::sort
#include <math.h>       // for tgamma, sqrt
#include <random>


long long factorial(long long k) {
    return tgamma(k+1);
}


/*
Example of next_l. Suppose n=2. Initialize l to {0, 0}.
Consider the following code:
    do {
        std::cout << l[0] << l[1] << std::endl;
    } while (next_l(n, 4, l));
This code will print:
    00
    01
    02
    03
    ...
    33
*/
bool next_l(int n, int k, int *l) {
    for(int i=n-1; i>=0; i--) {
        if(l[i] < k - 1) {
            l[i]++;
            return true;
        } else {
            l[i] = 0;
        }
    }
    return false;
}


cnum hafnian(int n, cnum **X) {
  cnum sum = 0;
  cnum product;

  int *sigma = (int*)malloc(sizeof(int) * 2 * n);
  for(int i=0; i<2*n; i++) { sigma[i] = i; }

  do {
    product = 1;
    for(int j=0; j<n; j++) {
      product *= X[sigma[2*j]][sigma[2*j+1]];
    }
    sum += product;
  } while (std::next_permutation(sigma, sigma + 2*n));

  free(sigma);

  return sum / ((double)(factorial(n) * (1 << n)));
}


void random_gaussian_matrix(int rows, int cols, cnum **X) {

  std::random_device rd{};
  std::mt19937 gen{rd()};
  std::normal_distribution<> d{0., 1./sqrt(2.)};
  for(int r=0; r<rows; r++) {
    for(int c=0; c<cols; c++) {
      cnum num(d(gen), d(gen));
      X[r][c] = num;
    }
  }
}


// compute X^T X and update Y in place.
void XtrX(int rows, int cols, cnum **X, cnum **Y) {
  // X is rows by cols. So Y = X^T X is cols by cols.

  for(int r=0; r<cols; r++) {
    for(int c=0; c<cols; c++) {
      Y[r][c] = 0;
      for(int k=0; k<rows; k++){
        Y[r][c] += X[k][r] * X[k][c];
      }
    }
  }

}
