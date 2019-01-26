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

#endif /* options_hpp */

double european_call(double T, double X, double r, double sigma, double s, int n);
double black_scholes(double T, double X, double r, double sigma, double s);
double improved_call(double T, double X, double r, double sigma, double s, int n);
