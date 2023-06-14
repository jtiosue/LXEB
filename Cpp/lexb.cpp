
#include <iostream>     // std::cout
#include <algorithm>    // std::next_permutation, std::sort
#include <set>
#include <tuple>
#include "methods.h"


long long evaluate_sum(int n, int k, long long (*summand)(int, int*, int*, int*, int*, int*, int*, int*, int*)) {

    long long sum = 0;

    int *sigma = (int*)malloc(sizeof(int) * 2 * n);
    int *tau   = (int*)malloc(sizeof(int) * 2 * n);
    int *alpha = (int*)malloc(sizeof(int) * 2 * n);
    int *beta  = (int*)malloc(sizeof(int) * 2 * n);

    int *l = (int*)malloc(sizeof(int) * n);
    int *o = (int*)malloc(sizeof(int) * n);
    int *p = (int*)malloc(sizeof(int) * n);
    int *q = (int*)malloc(sizeof(int) * n);

    for(int i=0; i<2*n; i++) { sigma[i] = i; }
    do { // loop over sigma
        for(int i=0; i<2*n; i++) { tau[i] = i; }
        do { // loop over tau
            for(int i=0; i<2*n; i++) { alpha[i] = i; }
            do { // loop over alpha
                for(int i=0; i<2*n; i++) { beta[i] = i; }
                do { // loop over beta
                    for(int i=0; i<n; i++) { l[i] = 0; }
                    do { // loop over l
                        for(int i=0; i<n; i++) { o[i] = 0; }
                        do { // loop over o
                            for(int i=0; i<n; i++) { p[i] = 0; }
                            do { // loop over p
                                for(int i=0; i<n; i++) { q[i] = 0; }
                                do { // loop over q

                                    sum += summand(n, sigma, tau, alpha, beta, l, o, p, q);

                                } while ( next_l(n, k, q) );
                            } while ( next_l(n, k, p) );
                        } while ( next_l(n, k, o) );
                    } while ( next_l(n, k, l) );
                } while ( std::next_permutation(beta, beta + 2*n) );
            } while ( std::next_permutation(alpha, alpha + 2*n) );
        } while ( std::next_permutation(tau, tau + 2*n) );
    } while ( std::next_permutation(sigma, sigma + 2*n) );


    free(sigma); free(tau); free(alpha); free(beta);
    free(l); free(o); free(p); free(q);

    return sum;
}


typedef std::tuple<int, int> ituple;
typedef std::multiset<ituple> imultiset;
typedef std::set<ituple> iset;

long long equation189_summand(int n, int *sigma, int *tau, int *alpha, int *beta, int *l, int *o, int *p, int *q) {

    imultiset unstar, star;
    for(int j=0; j<n; j++) {
        unstar.insert(std::make_tuple(l[j], sigma[2*j]));
        unstar.insert(std::make_tuple(l[j], sigma[2*j+1]));
        unstar.insert(std::make_tuple(p[j], alpha[2*j]));
        unstar.insert(std::make_tuple(p[j], alpha[2*j+1]));

        star.insert(std::make_tuple(o[j], tau[2*j]));
        star.insert(std::make_tuple(o[j], tau[2*j+1]));
        star.insert(std::make_tuple(q[j], beta[2*j]));
        star.insert(std::make_tuple(q[j], beta[2*j+1]));
    }

    if(!(unstar == star)) {
        return 0;
    }

    long long product = 1;

    // create set from the multiset to get rid of duplicates.
    iset star_set(star.cbegin(), star.cend());

    for(ituple item : star_set) {
        product *= factorial(star.count(item));
    }

    return product;
}



long long equation200_summand(int n, int *sigma, int *tau, int *alpha, int *beta, int *l, int *o, int *p, int *q) {

    long long product = 1;
    long long first_term;
    long long second_term;
    for(int j=0; j<n; j++) {

        first_term = 0; second_term = 0;

        // floor division is automatically done

        if( o[tau[sigma[2*j]] / 2] == l[j] && p[alpha[sigma[2*j]] / 2] == q[beta[sigma[2*j]] / 2] ) {
            first_term += 1;
        }
        if( q[beta[sigma[2*j]] / 2] == l[j] && p[alpha[sigma[2*j]] / 2] == o[tau[sigma[2*j]] / 2] ) {
            first_term += 1;
        }


        if( o[tau[sigma[2*j+1]] / 2] == l[j] && p[alpha[sigma[2*j+1]] / 2] == q[beta[sigma[2*j+1]] / 2] ) {
            second_term += 1;
        }
        if( q[beta[sigma[2*j+1]] / 2] == l[j] && p[alpha[sigma[2*j+1]] / 2] == o[tau[sigma[2*j+1]] / 2] ) {
            second_term += 1;
        }

        if(first_term == 0 || second_term == 0) {
            return 0;
        }

        product *= first_term * second_term;

    }

    return product;
}



long long eq202(int n, int k) {

    long long sum = 0;
    long long term, product;

    int *tau   = (int*)malloc(sizeof(int) * 2 * n);
    int *alpha = (int*)malloc(sizeof(int) * 2 * n);
    int *beta  = (int*)malloc(sizeof(int) * 2 * n);

    int *o = (int*)malloc(sizeof(int) * n);
    int *p = (int*)malloc(sizeof(int) * n);
    int *q = (int*)malloc(sizeof(int) * n);


    for(int i=0; i<2*n; i++) { tau[i] = i; }
    do { // loop over tau
        for(int i=0; i<2*n; i++) { alpha[i] = i; }
        do { // loop over alpha
            for(int i=0; i<2*n; i++) { beta[i] = i; }
            do { // loop over beta
                for(int i=0; i<n; i++) { o[i] = 0; }
                do { // loop over o
                    for(int i=0; i<n; i++) { p[i] = 0; }
                    do { // loop over p
                        for(int i=0; i<n; i++) { q[i] = 0; }
                        do { // loop over q

                            product = 1;

                            for(int j=0; j<n; j++) {
                                term = 0;

                                if(o[tau[2*j]/2] == o[tau[2*j+1]/2] && p[alpha[2*j]/2] == q[beta[2*j]/2] && p[alpha[2*j+1]/2] == q[beta[2*j+1]/2]) {
                                    term += 1;
                                }
                                if(o[tau[2*j]/2] == q[beta[2*j+1]/2] && p[alpha[2*j]/2] == q[beta[2*j]/2] && p[alpha[2*j+1]/2] == o[tau[2*j+1]/2]) {
                                    term += 1;
                                }
                                if(q[beta[2*j]/2] == o[tau[2*j+1]/2] && p[alpha[2*j]/2] == o[tau[2*j]/2] && p[alpha[2*j+1]/2] == q[beta[2*j+1]/2]) {
                                    term += 1;
                                }
                                if(q[beta[2*j]/2] == q[beta[2*j+1]/2] && p[alpha[2*j]/2] == o[tau[2*j]/2] && p[alpha[2*j+1]/2] == o[tau[2*j+1]/2]) {
                                    term += 1;
                                }

                                product *= term;

                            }

                            sum += product;

                        } while ( next_l(n, k, q) );
                    } while ( next_l(n, k, p) );
                } while ( next_l(n, k, o) );
            } while ( std::next_permutation(beta, beta + 2*n) );
        } while ( std::next_permutation(alpha, alpha + 2*n) );
    } while ( std::next_permutation(tau, tau + 2*n) );


    free(tau); free(alpha); free(beta);
    free(o); free(p); free(q);

    return factorial(2*n) * sum;
}


double fourth_moment_approx(int n, int k, int iters) {
    double avg = 0;
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
        avg += std::pow(std::abs(hafnian(n, Y)), 4);
    }

    for(int i=0; i<k; i++) {free(X[i]);}
    free(X);
    for(int i=0; i<2*n; i++) {free(Y[i]);}
    free(Y);


    return avg / (double)iters;
}


int main(int argc, char** argv) {

    if(argc != 3) {
        std::cout << "Please provide n, k" << std::endl;
        return 0;
    }

    int n, k;
    sscanf(argv[1], "%d", &n);
    sscanf(argv[2], "%d", &k);
    std::cout << "n = " << n << ", k  = " << k << std::endl;

    // Only run this one for small n!
    // std::cout << "Eq 189: " << evaluate_sum(n, k, &equation189_summand) << std::endl;
    
    // This one is also pretty slow
    // std::cout << "Eq 200: " << evaluate_sum(n, k, &equation200_summand) << std::endl;

    // This is the fastest exact one.
    // std::cout << "Eq 202: " << eq202(n, k) << std::endl;

    // This is always fast; just generating a bunch of random matrices and averaging.
    std::cout << "Approx: " << fourth_moment_approx(n, k, 1e5) << std::endl;


    return 0;
}
