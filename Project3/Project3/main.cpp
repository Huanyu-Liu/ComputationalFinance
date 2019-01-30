//
//  main.cpp
//  Project3
//
//  Created by Huanyu Liu on 1/26/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include <iostream>
#include "problem1.hpp"
#include "problem2.hpp"
#include "options.hpp"
#include "heston_model.hpp"

using std::cout;
using std::endl;

int main(int argc, const char * argv[]) {
    // Problem 1
    int size = 1000;
    double t = 2;
    double y_0 = 0.75;
    int simulation_count = 1000;
    double y2[simulation_count];
    double counter = 0;
    double x2[simulation_count];
    double x2_1_3[simulation_count];
    double x0 = 1;
    double y3[simulation_count];
    double sum = 0;
    random_generator rg;
    for (int i = 0; i < simulation_count; i++){
        y2[i] = problem1::y_t(y_0, t, size, rg);
        if (y2[i] > 5) counter++;
    }
    for (int i = 0; i < simulation_count; i++){
        x2[i] = problem1::x_t(x0,t,size,rg);
        x2_1_3[i] = x2[i] > 0 ? pow(x2[i],1.0/3) : -pow(-x2[i],1.0/3);
    }
    for (int i = 0; i < simulation_count; i++){
        y3[i] = problem1::y_t(y_0, 3, size, rg);
    }
    for (int i = 0; i < simulation_count; i++){
        if (x2[i] > 1){
            sum += y2[i] * x2[i];
        }
    }
    double expectation_x2 = stats::mean(x2,simulation_count);
    double expectation_y3 = stats::mean(y3,simulation_count);
    cout << counter/simulation_count << endl;
    cout << expectation_x2 << endl;
    cout << expectation_y3 << endl;
    cout << sum / simulation_count << endl;
    
    // Problem 2
    
    double x3_2[simulation_count];
    double y3_2[simulation_count];
    
    t = 3;
    for (int i = 0; i < simulation_count; i++){
        x3_2[i] = problem2::x_t(x0, t, size, rg);
    }
    double expectation_x3_2 = problem2::expectation(x3_2, simulation_count);
    
    double* w;
    double* z;
    w = rg.brownian_motion(size, 3);
    z = rg.brownian_motion(size, 3);
    
    for (int i = 0; i < size; i++){
        y3_2[i] = exp(-0.08 * t + 1.0/3 * w[i] + 0.75 * z[i]);
    }
    double expectation_y3_2 = problem2::expectation(y3_2, size);
    cout << expectation_x3_2 << endl;
    cout << expectation_y3_2 << endl;
    
    // Problem 3
    // (a)
    double s0[11] = {15,16,17,18,19,20,21,22,23,24,25};
    double c1[11];
    double c2[11];
    double delta[11];
    double gamma[11];
    double theta[11];
    double vega[11];
    double rho[11];
    double sigma = 0.25;
    double r = 0.04;
    double T = 0.5;
    double X = 20;
    options op(s0[0],T,X,r,sigma);
    for (int i = 0; i < 11; i++){
        op.set_s(s0[i]);
        c1[i] = op.european_call(simulation_count);
        c2[i] = op.black_scholes();
        delta[i] = op.delta(simulation_count);
        gamma[i] = op.gamma(simulation_count);
        theta[i] = op.theta(simulation_count);
        vega[i] = op.vega(simulation_count);
        rho[i] = op.rho(simulation_count);
        cout << c1[i] << ", " << c2[i] << endl;
        cout << delta[i] << endl;
        cout << gamma[i] << endl;
        cout << theta[i] << endl;
        cout << vega[i] << endl;
        cout << rho[i] << endl;
    }
    
    // Problem 4
    heston ht(&rg,-0.6,0.03,48,0.05,0.42,5.8,0.0625,50,0.5);
    double c1_4 = ht.european_call_f(simulation_count);
    double c2_4 = ht.european_call_p(simulation_count);
    double c3_4 = ht.european_call_r(simulation_count);
//
    cout << c1_4 << endl;
    cout << c2_4 << endl;
    cout << c3_4 << endl;
//
    // Problem 5
    double uniform_2dim[100][2];
    for (int i = 0; i < 100; i++){
        uniform_2dim[i][0] = rg.uniform_generator();
        uniform_2dim[i][1] = rg.uniform_generator();
    }
    
    return 0;
}
