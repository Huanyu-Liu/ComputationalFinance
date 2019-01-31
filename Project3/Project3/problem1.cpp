//
//  problem1.cpp
//  Project3
//
//  Created by Huanyu Liu on 1/28/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include "problem1.hpp"

double problem1::y_t(double y0, double t, int size, random_generator & r){
    double delta = t/size;
    //random_generator rg(seed);
    double* z = r.brownian_motion(size, delta);
    double sum = y0;
    double b;
    for (int i = 0; i < size; i++){
        double t_counter = delta * i;
        b = (1 + t_counter*t_counter*t_counter)/3;
        sum += (2 / (1+t_counter) * sum + b) * delta + b * z[i];
    }
    return sum;
}

double problem1::x_t(double x0, double t, int size, random_generator & r){
    double delta = t/size;
    double* w = r.brownian_motion(size, delta);
    for (int i = 0; i < size; i++){
        x0 += (0.2 - 0.5 * x0) * delta + 2.0/3 * w[i];
    }
    return x0;
}

