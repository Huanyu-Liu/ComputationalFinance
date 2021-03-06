//
//  random_generator.hpp
//  Project2
//
//  Created by Huanyu Liu on 1/21/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#ifndef random_generator_hpp
#define random_generator_hpp
#pragma once
#include <stdio.h>
#include <cmath>
#include <numeric>
#include <iostream>

#endif /* random_generator_hpp */

class random_generator{
    unsigned long seed;
    unsigned long m;
    unsigned long a;
public:
    random_generator(unsigned long x = (1 << 10) + 1);
    unsigned long get_seed();
    double uniform_generator();
    double* normal_generator(int size);
    void normal_generator(double *, int size);
    double** bivariate_normal(int size,double x_sigma, double y_sigma, double rho);
    void bivariate_normal(double ** xy, int size,double x_sigma, double y_sigma, double rho);
    double* brownian_motion(int size, double t);
    void brownian_motion(double * bm, int size, double t);
    double* geometric_brownian_motion(int size, double t, double r, double sigma, double s);
    void geometric_brownian_motion(double * geobm, int size, double t, double r, double sigma, double s);
    double* stock_path(int size, double t, double r, double sigma, double s0);
    void stock_path(double * path, int size, double t, double r, double sigma, double s0);
    void set_seed(unsigned long seed);
    void delfault();
};
