//
//  random_generator.hpp
//  Project2
//
//  Created by Huanyu Liu on 1/21/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//
#pragma once
#ifndef random_generator_hpp
#define random_generator_hpp

#include <stdio.h>
#include <cmath>
#include <numeric>

#endif /* random_generator_hpp */

class random_generator{
    unsigned long seed;
    unsigned long m;
    unsigned long a;
public:
    random_generator(unsigned long x = (1 << 10) + 1);
    double uniform_generator();
    double* normal_generator(int size);
    double** bivariate_normal(int size,double x_sigma, double y_sigma, double rho);
    double* brownian_motion(int size, double t);
    double* geometric_brownian_motion(int size, double t, double r, double sigma, double s);
    double* stock_path(int size, double t, double r, double sigma, double s0);
};
