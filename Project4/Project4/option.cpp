//
//  option.cpp
//  Project4
//
//  Created by Huanyu Liu on 2/1/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include "option.hpp"

option::option(double s0, double k, double r, double sigma, double t, bool is_call, bool is_european){
    this->s0 = s0;
    this->k = k;
    this->r = r;
    this->sigma = sigma;
    this->t = t;
    this->is_call = is_call;
    this->is_european = is_european;
}

//inline void option::set_s0(double s0){
//    this->s0 = s0;
//}
//inline void option::set_r(double r){
//    this->r = r;
//}
//inline void option::set_sigma(double sigma){
//    this->sigma = sigma;
//}
//inline void option::set_t(double t){
//    this->t = t;
//}
//
//inline double option::get_s0(){
//    return s0;
//}
//inline double option::get_r(){
//    return r;
//}
//inline double option::get_sigma(){
//    return sigma;
//}
//inline double option::get_t(){
//    return t;
//}

double option::binomial_method1(int n){
    double delta = t / n;
    double c = 0.5 * (exp(-r * delta) + exp((r + sigma * sigma) * delta));
    double d = c - sqrt(c * c - 1);
    double u = 1 / d;
    double p = (exp(r * delta) - d) / (u - d);
    return binomial_tree(n, u, d, p);
}

double option::binomial_method2(int n){
    double delta = t / n;
    double p = 0.5;
    double a = exp(r * delta);
    double b = sqrt(exp(sigma * sigma * delta) - 1);
    double u = a * (1 + b);
    double d = a * (1 - b);
    return binomial_tree(n, u, d, p);
}

double option::binomial_method3(int n){
    double delta = t / n;
    double p = 0.5;
    double a = (r - sigma * sigma / 2) * delta;
    double b = sigma * sqrt(delta);
    double u = exp(a + b);
    double d = exp(a - b);
    return binomial_tree(n, u, d, p);
}

double option::binomial_method4(int n){
    double delta = t / n;
    double a = sigma * sqrt(delta);
    double u = exp(a);
    double d = exp(-a);
    double p = 0.5 + 0.5 * ((r - sigma * sigma / 2) * sqrt(delta) / sigma);
    return binomial_tree(n, u, d, p);
}

double option::binomial_tree(int n, double u, double d, double p){
    double pd = 1 - p;
    double stock_price[n + 1];
    double payoff[n + 1];
    double delta = t / n;
    stock_price[0] = s0 * pow(u, n);
    if (is_call){
        payoff[0] = max::max(stock_price[0] - k, 0);
    }
    else{
        payoff[0] = max::max(k - stock_price[0], 0);
    }
    for (int i = 0; i < n; i++){
        stock_price[i + 1] = stock_price[i] * d / u;
        if (is_call){
            payoff[i + 1] = max::max(stock_price[i + 1] - k, 0);
        }
        else{
            payoff[i + 1] = max::max(k - stock_price[i + 1], 0);
        }
    }
    if (is_european){
        for (int i = n; i > 0; i--){
            for (int j = 0; j < i; j++){
                payoff[j] = payoff[j] * p + pd * payoff[j + 1];
            }
        }
        payoff[0] *= exp(-r * t);
    }
    else{
        double continue_p, exercise_p;
        for (int i = n; i > 0; --i) {
            for (int j = 0; j < i; ++j){
                stock_price[j] /= u;
                continue_p = exp(-r * delta) * (p * payoff[j] + pd * payoff[j + 1]);
                if (is_call){
                    exercise_p = max::max(stock_price[j] - k, 0);
                }
                else{
                    exercise_p = max::max(k - stock_price[j], 0);
                }
                payoff[j] = max::max(continue_p, exercise_p);
            }
        }
    }
    return payoff[0];
}
