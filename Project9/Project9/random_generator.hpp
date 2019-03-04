//
//  random_generator.hpp
//  Project8
//
//  Created by Huanyu Liu on 3/2/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#ifndef random_generator_hpp
#define random_generator_hpp

#include <stdio.h>
#include <vector>
#include <cmath>
#include <numeric>
#endif /* random_generator_hpp */

using std::vector;

class random_generator{
    unsigned long seed;
    unsigned long m;
    unsigned long a;
public:
    random_generator(unsigned long x = (1 << 10) + 1);
    unsigned long get_seed();
    double uniform_generator();
    vector<double> normal_generator(int size);
    vector<double> brownian_motion(int size, double t);
    void set_seed(unsigned long seed);
    void delfault();
};
