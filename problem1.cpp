//
//  problem1.cpp
//  Project3
//
//  Created by Huanyu Liu on 1/28/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include "problem1.hpp"

namespace problem1{
    double y_t(double y0, double t, int size, random_generator & r){
        double delta = t/size;
        //random_generator rg(seed);
        double* z = r.brownian_motion(size, delta);
        double sum = y0;
        double b = (1 + t*t*t)/3;
        for (int i = 0; i < size; i++){
            double temp = sum;
            sum += (2 / (1+t) * temp + b) * delta + b * z[i];
        }
        return sum;
    }
    
    double x_t(double x0, double t, int size, random_generator & r){
        double delta = t/size;
        double* w = r.brownian_motion(size, t);
        double temp;
        for (int i = 0; i < size; i++){
            temp = x0;
            x0 += (0.2 - 0.5 * temp) * delta + 2.0/3 * w[i];
        }
        return x0;
    }
}
