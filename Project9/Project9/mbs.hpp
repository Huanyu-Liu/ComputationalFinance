//
//  mbs.hpp
//  Project9
//
//  Created by Huanyu Liu on 3/3/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#ifndef mbs_hpp
#define mbs_hpp
#define SMALL 1
#include <stdio.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <tuple>
#include "random_generator.hpp"
#endif /* mbs_hpp */
using std::vector;
using std::tuple;
class MBS{
    double r0, k, r_bar, sigma, T, wac, loan;
public:
    MBS(double r0, double k, double r_bar, double sigma, double T, double wac, double loan);
    vector<double> rf_rate_path(int size, double delta);
    double CPR(double t, int month, double pvt, double rt);
    double price(int month, double oas, int simulation_count);
    tuple<double, double, double> oas(int month, double market_price, int simulation_count);
    static double sum(vector<double> v, int start, int end);
    inline void set_k(double k){this->k = k;}
    inline void set_r_bar(double r_bar){this->r_bar = r_bar;}
    inline void set_sigma(double sigma){this->sigma = sigma;}
};
