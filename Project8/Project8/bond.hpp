//
//  bond.hpp
//  Project8
//
//  Created by Huanyu Liu on 3/2/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#ifndef bond_hpp
#define bond_hpp

#include <stdio.h>
#include <iostream>
#include "random_generator.hpp"
#endif /* bond_hpp */

class Bond{
    double r0, sigma, k, r_bar;
public:
    Bond(double r0, double sigma, double k, double r_bar);
    double vasicek(double T, double face, int path_count);
    double coupon_bond(double *coupon, double *T, int cp_count, int path_count);
    double explicit_bond(double T, double t, double rt, double face);
    double option_zcb(double T, double t, double face, double x, int path_count);
    double option_cpbond(double *coupon, double *T, int cp_count, double t, double x, int path_count);
    inline void set_r0(double r0){this->r0 = r0;}
    static double sum(vector<double> vector, int start, int end);
    double cir_bond(double T, double face, int path_count);
    double cir_option(double S, double face, double T, double x, int path_count);
    double cir_explicit(double T, double t, double rt, double face);
    double g2_model_bond(double S, double face, double phi, double rho, double a, double b, double eta, double x0, double y0, int path_count);
    double g2_model_option(double S, double face, double T, double strike, double phi, double rho, double a, double b, double eta, int path_count);
    static double chi_square(double x, double p, double q);
};
