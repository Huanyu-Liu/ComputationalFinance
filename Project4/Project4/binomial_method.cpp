//
//  binomial_method.cpp
//  Project4
//
//  Created by Huanyu Liu on 1/31/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include "binomial_method.hpp"

double binomial::binomial_method1(int n, double r, double sigma, double s0, double k, double t){
    double delta = t / n;
    double c = 0.5 * (exp(-r * delta) + exp((r + sigma * sigma) * delta));
    double d = c - sqrt(c * c - 1);
    double u = 1 / d;
    double p = (exp(r * delta) - d) / (u - d);
    return exp(-r * t) * binomial_tree(n, s0, k, u, d, p);
}

double binomial::binomial_method2(int n, double r, double sigma, double s0, double k, double t){
    double delta = t / n;
    double p = 0.5;
    double a = exp(r * delta);
    double b = sqrt(exp(sigma * sigma * delta) - 1);
    double u = a * (1 + b);
    double d = a * (1 - b);
    return exp(-r * t) * binomial_tree(n, s0, k, u, d, p);
}

double binomial::binomial_method3(int n, double r, double sigma, double s0, double k, double t){
    double delta = t / n;
    double p = 0.5;
    double a = (r - sigma * sigma / 2) * delta;
    double b = sigma * sqrt(delta);
    double u = exp(a + b);
    double d = exp(a - b);
    return exp(-r * t) * binomial_tree(n, s0, k, u, d, p);
}

double binomial::binomial_method4(int n, double r, double sigma, double s0, double k, double t){
    double delta = t / n;
    double a = sigma * sqrt(delta);
    double u = exp(a);
    double d = exp(-a);
    double p = 0.5 + 0.5 * ((r - sigma * sigma / 2) * sqrt(delta) / sigma);
    return exp(-r * t) * binomial_tree(n, s0, k, u, d, p);
}

double binomial::binomial_tree(int n, double s0, double k, double u, double d, double p){
    double pd = 1 - p;
    double last_period[n + 1];
    last_period[0] = s0 * pow(u, n);
    for (int i = 0; i < n; i++){
        last_period[i + 1] = last_period[i] * d / u;
        last_period[i] = max::max(last_period[i] - k, 0);
    }
    last_period[n] = max::max(last_period[n], 0);
    for (int i = n; i > 0; i--){
        for (int j = 0; j < i; j++){
            last_period[j] = last_period[j] * p + pd * last_period[j + 1];
        }
    }
    return last_period[0];
}
