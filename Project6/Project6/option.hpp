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
#endif /* option_hpp */

class option{
    double s0, r, sigma, x, t;
    double ** path;
    bool is_call;
public:
    option(double s0, double r, double sigma, double x, double t, bool is_call);
    double look_back(int size, int path_count);
    void set_sigma(double sigma);
};
