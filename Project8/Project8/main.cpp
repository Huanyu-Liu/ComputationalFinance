//
//  main.cpp
//  Project8
//
//  Created by Huanyu Liu on 3/2/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include <iostream>
#include "bond.hpp"
#include <ctime>

using std::cout;
using std::endl;
int main(int argc, const char * argv[]) {
    // Problem 1
    // (a)
    double r0 = 0.05;
    double sigma = 0.18;
    double k = 0.82;
    double r_bar = 0.05;
    double T = 0.5;
    double face = 1000;
    double t = 0;
    int path_count = 1000;
    std::clock_t start = std::clock();
    Bond bond(r0,sigma,k,r_bar);
    cout << "Q1(a): " << bond.vasicek(T, face, path_count) << endl;
    
    // (b)
    double coupon[8];
    coupon[7] = 1030;
    for (int i = 0; i != 7; ++i){
        coupon[i] = 30;
    }
    double T_b[8];
    T_b[0] = 0.5;
    for (int i = 1; i != 8; ++i){
        T_b[i] = T_b[i - 1] + 0.5;
    }
    cout << "Q1(b): " << bond.coupon_bond(coupon, T_b, 8, path_count) << endl;
    
    // (c)
    double x = 980;
    t = 0.25;
    
    //cout << "Q1(c): " << bond.option_zcb(T, t, face, x, path_count) << endl;
    //path_count = 500;
    // (d)
    //cout << "Q1(d): " << bond.option_cpbond(coupon, T_b, 8, t, x, path_count) << endl;
    
    // Problem 2
    k = 0.92;
    r_bar = 0.055;
    double S = 1;
    Bond bond2(r0,sigma,k,r_bar);
    //cout << bond2.cir_bond(1, 1000, path_count) << endl;
    //cout << "Q2(a): " << bond2.cir_option(S, face, T, x, path_count) << endl;
    
    // Problem 3
    double phi = 0.03, rho = 0.7, a = 0.1, b = 0.3, eta = 0.08;
    sigma = 0.03;
    r0 = 0.03;
    x = 985;
    Bond bond3(r0,sigma,k,r_bar);
    //cout << bond3.g2_model_bond(S, face, phi, rho, a, b, eta, 0, 0, path_count) << endl;
    double price3 = bond3.g2_model_option(S, face, T, x, phi, rho, a, b, eta, path_count);
    cout << "Q3: " << price3 << endl;
    double duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
    cout << "Total runtime: " << duration << endl;
    return 0;
}
