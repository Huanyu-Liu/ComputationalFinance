//
//  accept_reject.cpp
//  Project2
//
//  Created by Huanyu Liu on 1/22/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include "accept_reject.hpp"
#include "random_generator.hpp"

double t(double x){
    return (1 - 0.74 * x * x)/(1 -  0.74 / 3);
}

double* accept_reject(int size){
    double gx = t(0);
    double* output = new double[size];
    random_generator rdg;
    int i = 0;
    while(i < size){
        double u = rdg.uniform_generator();
        double y = rdg.uniform_generator();
        if (u <= t(y)/gx){
            output[i++] = y;
        }
    }
    return output;
}
