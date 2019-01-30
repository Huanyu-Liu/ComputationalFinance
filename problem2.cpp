//
//  problem2.cpp
//  Project3
//
//  Created by Huanyu Liu on 1/28/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include "problem2.hpp"

namespace problem2 {
    double x_t(double x0, double t, int size, random_generator & r){
        double delta = t/size;
        double* w = r.brownian_motion(size, t);
        double* z = r.brownian_motion(size, t);
        double temp;
        for (int i = 0; i < size; i++){
            temp = x0;
            x0 += (0.25 * temp * delta) + 1.0/3 * temp * w[i] - 0.75 * temp * z[i];
        }
        return x0;
    }
    
    double expectation(double* array, int size){
        double sum = 0;
        for (int i = 0; i < size; i++){
            double x = 1 + array[i];
            sum += (x > 0) ? pow(x,1.0/3) : -pow(-x,1.0/3);
        }
        return sum/size;
    }
}
