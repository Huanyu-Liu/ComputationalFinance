//
//  Option.hpp
//  Project7
//
//  Created by Huanyu Liu on 2/28/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#ifndef Option_hpp
#define Option_hpp

#include <stdio.h>
#include <cmath>
#include <iostream>
#include "matrix_cal.hpp"

#endif /* Option_hpp */

class Option{
    double s0, r, sigma, k, t;
public:
    Option(double s0, double r, double sigma, double k, double t);
    void efd(int N, double delta, double delta_x, double * F);
    void ifd(int N, double delta, double delta_x, double * F);
    void cnfd(int N, double delta, double delta_x, double * F);
    void log_stock(double * stock, int N, double delta_x);
    void stock(double * stock, int N, double delta_s);
    void american_efd(double delta, double delta_s, bool is_call, double * F);
    void american_ifd(double delta, double delta_s, bool is_call, double * F);
    void american_cnfd(double delta, double delta_s, bool is_call, double * F);
};
