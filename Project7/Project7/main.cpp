//
//  main.cpp
//  Project7
//
//  Created by Huanyu Liu on 2/28/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include <iostream>
#include "Option.hpp"
#include "matrix_cal.hpp"

using std::cout;
using std::endl;

int main(int argc, const char * argv[]) {
    // Problem 1
    double s0 = 10;
    double r = 0.04;
    double sigma = 0.2;
    double k = 10;
    double t = 0.5;
    double delta = 0.002;
    double delta_x = sigma * sqrt(4 * delta);
    double delta_s = 0.25;
    int N = 200;
    int dimension = 2 * N + 1;
    double * F = new double[dimension];
    
    Option op(s0,r,sigma,k,t);
    op.efd(N, delta, delta_x, F);
    cout << F[N] << endl;
    op.ifd(N, delta, delta_x, F);
    cout << F[N] << endl;
    op.cnfd(N, delta, delta_x, F);
    cout << F[N] << endl;
    
    // Problem 2
    N = (int)(s0 / delta_s);
    F = new double[2 * N + 1];
    op.american_efd(delta, delta_s, false, F);
    cout << F[N] << endl;
    op.american_efd(delta, delta_s, true, F);
    cout << F[N] << endl;
    op.american_ifd(delta, delta_s, false, F);
    cout << F[N] << endl;
    op.american_ifd(delta, delta_s, true, F);
    cout << F[N] << endl;
    op.american_cnfd(delta, delta_s, false, F);
    cout << F[N] << endl;
    op.american_cnfd(delta, delta_s, true, F);
    cout << F[N] << endl;
    return 0;
}
