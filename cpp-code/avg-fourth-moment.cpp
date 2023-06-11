#include <iostream>     // std::cout
// #include <algorithm>    // std::next_permutation, std::sort
// #include <set>
#include <tuple>
#include <fstream>
#include "methods.h"
#include <cmath>


typedef std::tuple<double, double> ituple;


ituple fourth_moment_approx_mean_std(int n, int k, int iters) {

    double sample;
    double mean = 0;
    double variance = 0;

    cnum **X = (cnum**)malloc(sizeof(cnum*) * k);
    for(int i=0; i<k; i++) {
        X[i] = (cnum*)malloc(sizeof(cnum) * 2 * n);
    }
    cnum ** Y = (cnum**)malloc(sizeof(cnum*) * 2 * n);
    for(int i=0; i<2*n; i++) {
        Y[i] = (cnum*)malloc(sizeof(cnum) * 2 * n);
    }

    for(int i=0; i<iters; i++) {
        random_gaussian_matrix(k, 2*n, X);
        XtrX(k, 2*n, X, Y);
        sample = (double)std::pow(std::abs(hafnian(n, Y)), 4);
        mean += sample;
        variance += sample * sample;
    }

    for(int i=0; i<k; i++) {free(X[i]);}
    free(X);
    for(int i=0; i<2*n; i++) {free(Y[i]);}
    free(Y);

    mean /= (double)iters;
    variance /= (double)iters;

    return std::make_tuple(mean, std::sqrt(variance - mean * mean));
}


int main(int argc, char** argv) {

    std::ofstream file;
    file.open("fourth_moment_approx_mean_std.csv");
    file << "n,k,iters,mean,std\n";

    ituple mean_var;
    int iters = 1e5;
    for(int n=1; n<=5; n++) {
        if(n == 4) {iters = 2500;}
        else if(n>4) {iters = 150;}
        for(int k=1; k<=5; k++) {
            std::cout << n << "," << k << std::endl;
            mean_var = fourth_moment_approx_mean_std(n, k, iters);
            file << n << "," << k << "," << iters << ",";
            file << std::get<0>(mean_var) << "," << std::get<1>(mean_var) << "\n";
        }
    }


    file.close();

    return 0;
}