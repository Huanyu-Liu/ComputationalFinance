//
//  option.hpp
//  Project5
//
//  Created by Huanyu Liu on 2/18/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#ifndef option_hpp
#define option_hpp

#include <stdio.h>
#include <iostream>
#include "random_generator.hpp"
#include "laguerre.hpp"
#endif /* option_hpp */

class option{
    double s0, r, sigma, x, t;
    double ** path;
    int size, path_count;
public:
    option(double s0, double r, double sigma, double x, double t, int size, int path_count);
    //~option();
    option(const option & op);
    option & operator=(const option & op);
    void set(double s0 = NAN, double r = NAN, double sigma = NAN, double x = NAN, double t = NAN);
    double price(int k, int method);
    double forward_option(double forward_date);
    double forward_american_option(double forward_date);
    double get_s0(){return this->s0;}
    inline double get_t(){return this->t;}
    inline double get_sigma(){return this->sigma;}
};
