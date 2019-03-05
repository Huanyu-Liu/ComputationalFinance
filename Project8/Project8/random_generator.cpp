//
//  random_generator.cpp
//  Project8
//
//  Created by Huanyu Liu on 3/2/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include "random_generator.hpp"

random_generator::random_generator(unsigned long x){
    seed = x;
    m = (1 << 31) - (unsigned long)1;
    a = 168019;
}

double random_generator::uniform_generator(){
    seed = (a * seed) % m;
    return (double)seed / m;
}

vector<double> random_generator::normal_generator(int size){
    vector<double> box_muller_norm;
    for (int i = 0; i < size; i+=2){
        double u1 = this->uniform_generator();
        double u2 = this->uniform_generator();
        box_muller_norm.push_back(sqrt(-2 * log(u1)) * cos(2 * M_PI * u2));
        box_muller_norm.push_back(sqrt(-2 * log(u1)) * sin(2 * M_PI * u2));
    }
    return box_muller_norm;
}

vector<double> random_generator::brownian_motion(int size, double t){
    vector<double> w;
    w = normal_generator(size);
    for (int i = 0; i < size; i++){
        w[i] *= sqrt(t);
    }
    return w;
}
