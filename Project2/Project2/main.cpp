//
//  main.cpp
//  Project2
//
//  Created by Huanyu Liu on 1/21/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "random_generator.hpp"
#include "stats.hpp"
#include "options.hpp"
#include "integral.hpp"
#include "accept_reject.hpp"

using namespace std;

ofstream data;
string file_path = "/Users/huanyu/Desktop/ComputationalFinance/Code/Project2/Data/";

double problem3a(double* w, int size, double t){
    double sum = 0;
    for (int i = 0; i < size; i++){
        sum += exp(t/2) * cos(w[i]);
    }
    return sum/size;
}

// control variate
// Y = w^2
double problem3c(double* w, int size, double t){
    double sum = 0;
    double e_y = t;
    double gamma;
    double y[size];
    double x[size];
    for (int i = 0; i < size; i++){
        x[i] = exp(t/2) * cos(w[i]);
        y[i] = w[i] * w[i];
    }
    gamma = stats::covariance(x, y, size)/stats::variance(y, size);
    for (int i = 0; i < size; i++){
        sum += x[i] - gamma * (y[i] - e_y);
    }
    return sum/size;
}

int main(int argc, const char * argv[]) {
    
    // Problem 1
    double a = -0.7;
    double x_sigma = 1;
    double y_sigma = 1;
    double rho = a / x_sigma / y_sigma;
    int size = 1000;
    double** xy;
    random_generator rg;
    xy = rg.bivariate_normal(size, x_sigma, y_sigma, rho);
    double output = stats::correlation(xy[0], xy[1], size);
    cout << "Problem1 rho: " << output << endl;
    
    // Problem 2
    size = 10000;
    double rho2 = 0.6;
    double** xy2;
    double* x;
    double* y;
    xy2 = rg.bivariate_normal(size, x_sigma, y_sigma, rho2);
    x = xy2[0];
    y = xy2[1];
    double sum = 0;
    for (int i = 0; i < size; i++){
        double x_square = x[i] * x[i];
        double equation = x_square * x[i] + sin(y[i]) + x_square * y[i];
        double max = equation < 0 ? 0 : equation;
        sum += max;
    }
    cout << endl << "Problem2 Value E: " << sum / size << endl;
    
    // Problem 3
    // (a)
    double* w5 = rg.brownian_motion(size, 5);
    sum = 0;
    for (int i = 0; i < size; i++){
        sum += w5[i] * w5[i] + sin(w5[i]);
    }
    cout << endl << "Problem3 E(W5): " << sum /size << endl;
    
    double* w0_5 = rg.brownian_motion(size, 0.5);
    double* w3_2 = rg.brownian_motion(size, 3.2);
    double* w6_5 = rg.brownian_motion(size, 6.5);
    cout << "t = 0.5: " << problem3a(w0_5, size, 0.5) << endl;
    cout << "t = 3.2: " << problem3a(w3_2, size, 3.2) << endl;
    cout << "t = 6.5: " << problem3a(w6_5, size, 6.5) << endl;

    // (c) Antithetic Variates
    cout << "Problem 3(c): " << endl;
    double* w5c = rg.brownian_motion(size, 5);
    double* w0_5c = rg.brownian_motion(size * 2, 0.5);
    double* w3_2c = rg.brownian_motion(size * 2, 3.2);
    double* w6_5c = rg.brownian_motion(size * 2, 6.5);
    double ea1 = 0;
    double ea2 = problem3c(w0_5c, size, 0.5);
    double ea3 = problem3c(w3_2c, size, 3.2);
    double ea4 = problem3c(w6_5c, size, 6.5);
    for (int i = 0; i < size; i++){
        ea1 += (w5c[i] * w5c[i] + sin(w5c[i]) + w5c[i] * w5c[i] + sin(-w5c[i]) )/2;
    }
    ea1 = ea1 / size;
    cout << "Ea1: " << ea1 << endl;
    cout << "Ea2: " << ea2 << endl;
    cout << "Ea3: " << ea3 << endl;
    cout << "Ea4: " << ea4 << endl;
    
    // Problem 4
    // (a)
    double T = 5;
    double X = 100;
    double r = 0.04;
    double sigma = 0.2;
    double s = 88;
    double call;
    call = european_call(T, X, r, sigma, s, size);
    cout << endl << "Problem4: " << endl;
    cout << "Monte Carlo simulation call: " << call << endl;
    cout << "Black Scholes call: " << black_scholes(T, X, r, sigma, s) << endl;
    
    // (b)
    call = improved_call(T, X, r, sigma, s, size);
    cout << "Variance Reduction call: " << call << endl;
    
    // Problem 5
    // (a)
    size = 1000;
    cout << endl << "Problem 5: Data are exported to R by create csv data file." << endl;
    sigma = 0.18;
    double es[10];
    data.open(file_path + "stock_expectation.csv");
    for (int i = 1; i < 11; i++){
        double* g = rg.geometric_brownian_motion(size, i, r, sigma, s);
        double sum = 0;
        for (int j = 0; j < size; j++){
            sum += g[j];
        }
        es[i - 1] = sum / size;
        data << es[i - 1] << endl;
    }
    data.close();
    // (b)
    double* total_path[6];
    data.open(file_path + "stock_path.csv");
    for (int i = 0; i < 6; i++){
        total_path[i] = rg.stock_path(size, 10, r, sigma, s);
    }
    for (int i = 0; i < size; i++){
        for (int j = 0; j < 6; j++){
            data << total_path[j][i];
            if (j < 5) data << ",";
        }
        data << endl;
    }
    data.close();
    // (c)
    sigma = 0.35;
    double es_high_sigma[10];
    data.open(file_path + "high_sigma_stock_expectation.csv");
    for (int i = 1; i < 11; i++){
        double* g = rg.geometric_brownian_motion(size, i, r, sigma, s);
        double sum = 0;
        for (int j = 0; j < size; j++){
            sum += g[j];
        }
        es_high_sigma[i - 1] = sum / size;
        data << es_high_sigma[i - 1] << endl;
    }
    data.close();
    
    double* total_path_high_sigma[6];
    data.open(file_path + "high_sigma_stock_path.csv");
    for (int i = 0; i < 6; i++){
        total_path_high_sigma[i] = rg.stock_path(size, 10, r, sigma, s);
    }
    for (int i = 0; i < size; i++){
        for (int j = 0; j < 6; j++){
            data << total_path_high_sigma[j][i];
            if (j < 5) data << ",";
        }
        data << endl;
    }
    data.close();
    // Problem 6
    cout << endl << "Problem 6: " << endl;
    size = 10000;
    double eul = integral::euler(size);
    cout << "Euler's discretization scheme: " << eul << endl;
    
    double mc_integral = integral::monte_carlo(size);
    cout << "Monte Carlo simulation: " << mc_integral << endl;
    
    double* importance_sampling = accept_reject(size);
    sum = 0;
    for (int i = 0; i < size; i++){
        double x = importance_sampling[i];
        sum += integral::f(x) / t(x);
    }
    cout << "Importance sampling: " << 4 * sum / size << endl;
    return 0;
}
