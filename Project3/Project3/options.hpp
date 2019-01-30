//
//  options.hpp
//  Project2
//
//  Created by Huanyu Liu on 1/22/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#ifndef options_hpp
#define options_hpp

#include <stdio.h>
#include <cmath>
#include "stats.hpp"
#include "random_generator.hpp"
class options {
    double s,T,X,r,sigma;
public:
    options(double s, double T, double X, double r, double sigma);
    void set_s(double s);
    double european_call(int simulation_count);
    double black_scholes();
    double improved_call(int simulation_count);
    double delta(int simulation_count);
    double gamma(int simulation_count);
    double theta(int simulation_count);
    double vega(int simulation_count);
    double rho(int simulation_count);
};


#endif /* options_hpp */
