//
//  options.cpp
//  Project2
//
//  Created by Huanyu Liu on 1/22/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include "options.hpp"
#include "stats.hpp"
#include "random_generator.hpp"

double european_call(double T, double X, double r, double sigma, double s, int n){
    double sum = 0;
    double temp;
    double max;
    random_generator rand;
    double* w = rand.brownian_motion(n, T);
    for (int i = 0; i < n; i++){
        temp = s * exp((r - sigma * sigma / 2) * T + sigma * w[i]) - X;
        max = temp > 0 ? temp : 0;
        sum += max;
    }
    return exp(-r * T) / n * sum;
}

double black_scholes(double T, double X, double r, double sigma, double s){
    double d1 = 1 / sigma / sqrt(T) * (log(s/X) + (r + sigma * sigma / 2) * T);
    double d2 = d1 - sigma * sqrt(T);
    double pk = X * exp(-r * T);
    return stats::normal_cdf(d1) * s - stats::normal_cdf(d2) * pk;
}

double improved_call(double T, double X, double r, double sigma, double s, int n){
    double sum = 0;
    double temp1;
    double temp2;
    double max1;
    double max2;
    random_generator rand;
    double* w = rand.brownian_motion(n, T);
    for (int i = 0; i < n; i++){
        temp1 = s * exp((r - sigma * sigma / 2) * T + sigma * w[i]) - X;
        temp2 = s * exp((r - sigma * sigma / 2) * T + sigma * -w[i]) - X;
        max1 = temp1 > 0 ? temp1 : 0;
        max2  = temp2 > 0 ? temp2 : 0;
        sum += (max1 + max2) / 2;
    }
    return exp(-r * T) / n * sum;
}
