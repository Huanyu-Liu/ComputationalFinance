//
//  mbs.hpp
//  Project9
//
//  Created by Huanyu Liu on 3/3/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#ifndef mbs_hpp
#define mbs_hpp

#include <stdio.h>
#include <cmath>
#include <vector>
#include "random_generator.hpp"
#endif /* mbs_hpp */
using std::vector;
class MBS{
    double r0, k, r_bar, sigma, T, wac, loan;
public:
    MBS(double r0, double k, double r_bar, double sigma, double T, double wac, double loan);
    double CPR(double t, int month, double pvt, double rt);
    double price(int month);
    inline void set_k(double k){this->k = k;}
    inline void set_r_bar(double r_bar){this->r_bar = r_bar;}
    inline void set_sigma(double sigma){this->sigma = sigma;}
};
