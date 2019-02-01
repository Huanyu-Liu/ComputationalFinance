//
//  main.cpp
//  Project4
//
//  Created by Huanyu Liu on 1/31/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include <iostream>
#include "binomial_method.hpp"

using std::cout;
using std::endl;
int main(int argc, const char * argv[]) {
    // Problem 1
    double t = 0.5, r = 0.05, sigma = 0.24, s0 = 32, k = 30;
    int n[7] = {10,20,40,80,100,200,500};
    double price_a[7], price_b[7], price_c[7], price_d[7];
    for (int i = 0; i < 7; i++){
        price_a[i] = binomial::binomial_method1(n[i], r, sigma, s0, k, t);
        price_b[i] = binomial::binomial_method2(n[i], r, sigma, s0, k, t);
        price_c[i] = binomial::binomial_method3(n[i], r, sigma, s0, k, t);
        price_d[i] = binomial::binomial_method4(n[i], r, sigma, s0, k, t);
        cout << price_a[i] << ", " << price_b[i] << ", " << price_c[i] << ", " << price_d[i] << endl;
    }
    // Problem 2
    k = 1240;
    t = 1;
    r = 0.02;
    s0 = 1125.89;
    sigma = 0.234; // By using last 60 month daily price, and calculated the volatility in R
    double option_price = binomial::binomial_method1(252, r, sigma, s0, k, t);
    double yahoo_price = 72.91;
    cout << option_price << endl;
    cout << "Google Option Price on Yahoo Finance: " << yahoo_price << endl;
    
    return 0;
}
