//
//  main.cpp
//  Project3
//
//  Created by Huanyu Liu on 1/26/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "problem1.hpp"
#include "problem2.hpp"
#include "options.hpp"
#include "heston_model.hpp"
#include "halton_sequence.hpp"

using std::cout;
using std::endl;

std::ofstream data;
std::string file_path = "/Users/huanyu/Desktop/ComputationalFinance/data/Project3/";

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
        if (y2[i] > 5) {counter++;}
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
    double p_y2 = counter/simulation_count;
    double expectation_x2 = stats::mean(x2_1_3,simulation_count);
    double expectation_y3 = stats::mean(y3,simulation_count);
    double expectation_xy = sum / simulation_count;
    cout << "Problem 1: " << endl;
    cout << "Prob: " << p_y2 << endl;
    cout << "E1: " << expectation_x2 << endl;
    cout << "E2: " << expectation_y3 << endl;
    cout << "E3: " << expectation_xy << endl;
    
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
    cout << endl << "Problem 2: " << endl;
    cout << "E1: " << expectation_x3_2 << endl;
    cout << "E2: " << expectation_y3_2 << endl;
    
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
    data.open(file_path + "Project3_P3.csv");
    data << "s0,Monte Carlo Call,Black-Scholes Call,Delta,Gamma,Theta,Vega,Rho"<< endl;
    cout << endl << "Problem 3: " << endl;
    for (int i = 0; i < 11; i++){
        op.set_s(s0[i]);
        c1[i] = op.european_call(simulation_count);
        c2[i] = op.black_scholes();
        delta[i] = op.delta(simulation_count);
        gamma[i] = op.gamma(simulation_count);
        theta[i] = op.theta(simulation_count);
        vega[i] = op.vega(simulation_count);
        rho[i] = op.rho(simulation_count);
        cout << endl << "S0 = " << s0[i] << ": " << endl;
        cout << "Monte Carlo Call: " << c1[i] << endl;
        cout << "Black Scholes Call: " << c2[i] << endl;
        cout << "Delta: " << delta[i] << endl;
        cout << "Gamma: " << gamma[i] << endl;
        cout << "Theta: " << theta[i] << endl;
        cout << "Vega: " << vega[i] << endl;
        cout << "Rho: " << rho[i] << endl;
        data << s0[i] << "," <<c1[i] << ","<< c2[i] << "," << delta[i] << "," << gamma[i] << ",";
        data << theta[i] << "," << vega[i] << "," << rho[i] << endl;
    }
    
    data.close();
    // Problem 4
    heston ht(-0.6,0.03,48,0.05,0.42,5.8,0.0625,50,0.5);
    double c1_4 = ht.european_call_f(simulation_count);
    double c2_4 = ht.european_call_p(simulation_count);
    double c3_4 = ht.european_call_r(simulation_count);
    cout << endl << "Problem 4: " << endl;
    cout << "C1: " << c1_4 << endl;
    cout << "C2: " << c2_4 << endl;
    cout << "C3: " << c3_4 << endl;
//
    // Problem 5
    data.open(file_path + "Project3_P5.csv");
    double uniform_2dim[2][100];
    for (int i = 0; i < 100; i++){
        uniform_2dim[0][i] = rg.uniform_generator();
        uniform_2dim[1][i] = rg.uniform_generator();
    }
    int length = 100;
    double* seq1[2];
    double* seq2[2];
    seq1[0] = halton::halton_sequence(length, 2);
    seq1[1] = halton::halton_sequence(length, 7);
    seq2[0] = halton::halton_sequence(length, 2);
    seq2[1] = halton::halton_sequence(length, 4);
    
    for (int i = 0; i < length; i++){
        data << uniform_2dim[0][i] << "," << uniform_2dim[1][i] << ",";
        data << seq1[0][i] << "," << seq1[1][i] << ",";
        data << seq2[0][i] << "," << seq2[1][i] << "," << endl;
    }
    data.close();
    length = 10000;
    double integral_2_4 = halton::integral(2, 4, length);
    double integral_2_7 = halton::integral(2, 7, length);
    double integral_5_7 = halton::integral(5, 7, length);
    cout << endl << "Problem 5: " << endl;
    cout << "(2,4): " << integral_2_4 << endl;
    cout << "(2,7): " << integral_2_7 << endl;
    cout << "(5,7): " << integral_5_7 << endl;
    
    return 0;
}
