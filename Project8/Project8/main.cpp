//
//  main.cpp
//  Project8
//
//  Created by Huanyu Liu on 3/2/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include <iostream>
#include "bond.hpp"
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
    Bond bond(r0,sigma,k,r_bar);
    cout << bond.vasicek(T, face, path_count) << endl;
    
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
    cout << bond.coupon_bond(coupon, T_b, 8, path_count) << endl;
    
    // (c)
    double x = 980;
    t = 0.25;
    cout << bond.option_zcb(T, t, face, x, path_count) << endl;
    cout << bond.option_cpbond(coupon, T_b, 8, t, x, path_count) << endl;
    
    // Problem 2
    k = 0.92;
    r_bar = 0.055;
    double S = 1;
    Bond bond2(r0,sigma,k,r_bar);
    cout << bond2.cir_option(S, face, T, x, path_count) << endl;
    
    // Problem 3
    double phi = 0.03, rho = 0.7, a = 0.1, b = 0.3, eta = 0.08;
    sigma = 0.03;
    r0 = 0.03;
    x = 985;
    Bond bond3(r0,sigma,k,r_bar);
    double price3 = bond3.g2_model(S, face, T, x, phi, rho, a, b, eta, path_count);
    cout << price3 << endl;
    return 0;
}
