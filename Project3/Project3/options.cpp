//
//  options.cpp
//  Project2
//
//  Created by Huanyu Liu on 1/22/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include "options.hpp"


options::options(double s, double T, double X, double r, double sigma){
    this->s = s;
    this->T = T;
    this->X = X;
    this->r = r;
    this->sigma = sigma;
}

void options::set_s(double s){
    this->s = s;
}

double options::european_call(int simulation_count){
    double sum = 0;
    double temp;
    double max;
    random_generator rand;
    double* w = rand.brownian_motion(simulation_count, T);
    for (int i = 0; i < simulation_count; i++){
        temp = s * exp((r - sigma * sigma / 2) * T + sigma * w[i]) - X;
        max = temp > 0 ? temp : 0;
        sum += max;
    }
    return exp(-r * T) / simulation_count * sum;
}

double options::black_scholes(){
    double d1 = 1 / sigma / sqrt(T) * (log(s/X) + (r + sigma * sigma / 2) * T);
    double d2 = d1 - sigma * sqrt(T);
    double pk = X * exp(-r * T);
    return stats::normal_cdf(d1) * s - stats::normal_cdf(d2) * pk;
}

double options::improved_call(int simulation_count){
    double sum = 0;
    double temp1;
    double temp2;
    double max1;
    double max2;
    random_generator rand;
    double* w = rand.brownian_motion(simulation_count, T);
    for (int i = 0; i < simulation_count; i++){
        temp1 = s * exp((r - sigma * sigma / 2) * T + sigma * w[i]) - X;
        temp2 = s * exp((r - sigma * sigma / 2) * T + sigma * -w[i]) - X;
        max1 = temp1 > 0 ? temp1 : 0;
        max2  = temp2 > 0 ? temp2 : 0;
        sum += (max1 + max2) / 2;
    }
    return exp(-r * T) / simulation_count * sum;
}

double options::delta(int simulation_count){
    double temp = s;
    double epsilon = 0.01;
    double call;
    s += epsilon;
    call = european_call(simulation_count);
    s -= 2 * epsilon;
    call -= european_call(simulation_count);
    s = temp;
    return call / 2 / epsilon;
}

double options::gamma(int simulation_count){
    double temp = s;
    double epsilon = 1;
    double d;
    s += epsilon;
    d = delta(simulation_count);
    s -= 2 * epsilon;
    d -= delta(simulation_count);
    s = temp;
    return d / 2 / epsilon;
}

double options::theta(int simulation_count){
    double temp = T;
    double epsilon = 0.01;
    double call;
    T -= epsilon;
    call = european_call(simulation_count);
    T += 2 * epsilon;
    call -= european_call(simulation_count);
    T = temp;
    return call / 2 / epsilon;
}

double options::vega(int simulation_count){
    double temp = sigma;
    double epsilon = 0.01;
    double call;
    sigma += epsilon;
    call = european_call(simulation_count);
    sigma -= 2 * epsilon;
    call -= european_call(simulation_count);
    sigma = temp;
    return call / 2 / epsilon;
}

double options::rho(int simulation_count){
    double temp = r;
    double epsilon = 0.01;
    double call;
    r += epsilon;
    call = european_call(simulation_count);
    r -= 2 * epsilon;
    call -= european_call(simulation_count);
    r = temp;
    return call / 2 / epsilon;
}
