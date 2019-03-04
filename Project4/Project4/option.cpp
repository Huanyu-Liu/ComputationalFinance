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

double option::trinomial(int n){
    double delta = t / n;
    double d = exp(-sigma * sqrt(3 * delta));
    double u = 1 / d;
    double a = r * r * delta * delta + sigma * sigma * delta;
    double b = 1 - d;
    double c = u - d;
    double pd = (r * delta * (1 - u) + a) / c / b;
    double pu = (r * delta * b + a) / c / (u - 1);
    double pm = 1 - pd - pu;
    int final_branch = 2 * n + 1;
    double stock_price[final_branch];
    double payoff[final_branch];
    stock_price[0] = s0 * pow(u, n);
    payoff[0] = max::max(stock_price[0] - k, 0);
    for (int i = 0; i < final_branch - 1; ++i){
        stock_price[i + 1] = stock_price[i] * d;
        payoff[i + 1] = max::max(stock_price[i + 1] - k, 0);
    }
    for (int i = n; i > 0; i--){
        for (int j = 0; j < i * 2 - 1; ++j){
            payoff[j] = pu * payoff[j] + pm * payoff[j + 1] + pd * payoff[j + 2];
        }
    }
    payoff[0] *= exp(-r * t);
    return payoff[0];
}

double option::trinomial_log(int n){
    double delta = t / n;
    double delta_xu = sigma * sqrt(3 * delta);
    double a = (r - sigma * sigma / 2) * delta;
    double b = sigma * sigma * delta;
    double c = a * delta;
    double pd = 0.5 * ((b + c) / delta_xu / delta_xu - a / delta_xu);
    double pu = pd + a / delta_xu;
    double pm = 1 - pu - pd;
    int final_branch = 2 * n + 1;
    double stock_price[final_branch];
    double payoff[final_branch];
    double x0 = log(s0);
    stock_price[0] = x0 + n * delta_xu;
    payoff[0] = max::max(exp(stock_price[0]) - k, 1);
    for (int i = 0; i < final_branch - 1; ++i){
        stock_price[i + 1] = stock_price[i] - delta_xu;
        payoff[i + 1] = max::max(exp(stock_price[i + 1]) - k, 0);
    }
    for (int i = n; i > 0; i--){
        for (int j = 0; j < i * 2 - 1; ++j){
            payoff[j] = pu * payoff[j] + pm * payoff[j + 1] + pd * payoff[j + 2];
        }
    }
    payoff[0] *= exp(-r * t);
    return payoff[0];
}

double option::halton_option_price(int n, int base1, int base2){
    double* h1 = halton::halton_sequence(n, base1);
    double* h2 = halton::halton_sequence(n, base2);
    double* z1 = new double[n];
    double* z2 = new double[n];
    double temp;
    double temp2;
    double sum = 0;
    for (int i = 0; i < n; i++){
        temp = sqrt(-2 * log(h1[i]));
        z1[i] = temp * cos(2 * M_PI * h2[i]);
        z2[i] = temp * sin(2 * M_PI * h2[i]);
    }
    for (int i = 0; i < n; i++){
        temp = s0 * exp((r - sigma * sigma / 2) * t + sigma * sqrt(t) * z1[i]);
        temp = max::max(temp - k, 0);
        temp2 = s0 * exp((r - sigma * sigma / 2) * t + sigma * sqrt(t) * z2[i]);
        temp2 = max::max(temp2 - k, 0);
        sum += temp + temp2;
    }
    return exp(-r * t) * sum / 2 / n;
}
