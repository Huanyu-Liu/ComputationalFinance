//
//  main.cpp
//  Project9
//
//  Created by Huanyu Liu on 3/3/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include <iostream>
#include "mbs.hpp"
using std::cout;
using std::endl;

int main(int argc, const char * argv[]) {
    // Problem 1
    // (a)
    double T = 30;
    double wac = 0.08;
    double loan = 100000;
    double r0 = 0.078;
    double k = 0.6;
    double r_bar = 0.08;
    double sigma = 0.12;
    int month = 1;
    MBS mbs(r0, k, r_bar,sigma,T,wac,loan);
    cout << mbs.price(month) << endl;
    
    // (b)
    k = 0.3;
    while (k < 1) {
        mbs.set_k(k);
        cout << mbs.price(month) << endl;
        k += 0.1;
    }
    
    // (c)
    r_bar = 0.03;
    while (r_bar < 0.1){
        mbs.set_r_bar(r_bar);
        cout << mbs.price(month) << endl;
        r_bar += 0.01;
    }
    
    // (d)
    sigma = 0.1;
    while (sigma < 0.21) {
        mbs.set_sigma(sigma);
        cout << mbs.price(month) << endl;
        sigma += 0.01;
    }
    return 0;
}
