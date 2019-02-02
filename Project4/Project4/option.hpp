//
//  option.hpp
//  Project4
//
//  Created by Huanyu Liu on 2/1/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#ifndef option_hpp
#define option_hpp
#pragma once
#include <stdio.h>
#include <cmath>
#include "max.hpp"
#include "halton_sequence.hpp"
#endif /* option_hpp */

class option{
    double s0, k, r, sigma, t;
    bool is_call, is_european;
public:
    option(double s0, double k, double r, double sigma, double t, bool is_call, bool is_european);
    double binomial_tree(int n, double u, double d, double p);
    double binomial_method1(int n);
    double binomial_method2(int n);
    double binomial_method3(int n);
    double binomial_method4(int n);
    double trinomial(int n);
    double trinomial_log(int n);
    double halton_option_price(int n, int base1, int base2);
    inline void set_s0(double s0) {this->s0 = s0;}
    inline void set_r(double r){this->r = r;}
    inline void set_sigma(double sigma){this->sigma = sigma;}
    inline void set_t(double t){this->t = t;}
    inline double get_s0(){return s0;}
    inline double get_r(){return r;}
    inline double get_sigma(){return sigma;}
    inline double get_t(){return t;}
};
