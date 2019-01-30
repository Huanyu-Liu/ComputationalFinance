//
//  problem2.hpp
//  Project3
//
//  Created by Huanyu Liu on 1/28/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#ifndef problem2_hpp
#define problem2_hpp
#include "random_generator.hpp"
#include <stdio.h>
#include <cmath>

#endif /* problem2_hpp */

namespace problem2{
    double x_t(double x0, double t, int size, random_generator & r);
    double expectation(double* array, int size);
}

