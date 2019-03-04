//
//  greeks.cpp
//  Project4
//
//  Created by Huanyu Liu on 2/1/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include "greeks.hpp"

double greeks::delta(option op, int n){
    double s0 = op.get_s0();
    double epsilon = 1;
    op.set_s0(s0 + epsilon);
    double c0 = op.binomial_method1(n);
    op.set_s0(s0 - epsilon);
    double c1 = op.binomial_method1(n);
    return (c0 - c1) / 2 / epsilon;
}

double greeks::theta(option op, int n){
    double t = op.get_t();
    double epsilon = 0.1;
    op.set_t(t - epsilon);
    double c0 = op.binomial_method1(n);
    op.set_t(t + epsilon);
    double c1 = op.binomial_method1(n);
    return (c0 - c1) / 2 / epsilon;
}

double greeks::gamma(option op, int n){
    double s0 = op.get_s0();
    double epsilon = 2;
    op.set_s0(s0 + epsilon);
    double delta0 = delta(op, n);
    op.set_s0(s0 - epsilon);
    double delta1 = delta(op, n);
    return (delta0 - delta1) / 2 / epsilon;
}

double greeks::vega(option op, int n){
    double sigma = op.get_sigma();
    double epsilon = 0.1;
    op.set_sigma(sigma + epsilon);
    double c0 = op.binomial_method1(n);
    op.set_sigma(sigma - epsilon);
    double c1 = op.binomial_method1(n);
    return (c0 - c1) / 2 / epsilon;
}

double greeks::rho(option op, int n){
    double r = op.get_r();
    double epsilon = 0.1;
    op.set_r(r + epsilon);
    double c0 = op.binomial_method1(n);
    op.set_r(r - epsilon);
    double c1 = op.binomial_method1(n);
    return (c0 - c1) / 2 / epsilon;
}
