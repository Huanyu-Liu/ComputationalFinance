//
//  random_generator.cpp
//  Project2
//
//  Created by Huanyu Liu on 1/21/19.
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

double* random_generator::normal_generator(int size){
    double* box_muller_norm = new double[size];
    for (int i = 0; i < size; i+=2){
        double u1 = uniform_generator();
        double u2 = uniform_generator();
        box_muller_norm[i] = sqrt(-2 * log(u1)) * cos(2 * M_PI * u2);
        box_muller_norm[i+1] = sqrt(-2 * log(u1)) * sin(2 * M_PI * u2);
    }
    return box_muller_norm;
}

double** random_generator::bivariate_normal(int size, double x_sigma, double y_sigma, double rho){
    double** xy = new double*[2];;
    xy[0] = new double[size];
    xy[1] = new double[size];
    double* normal;
    normal = normal_generator(size * 2);
    for (int i = 0; i < size; i++){
        xy[0][i] = x_sigma * normal[i];
        xy[1][i] = y_sigma * rho * normal[i] + y_sigma * sqrt(1 - rho * rho) * normal[i+size];
    }
    return xy;
}

double* random_generator::brownian_motion(int size, double t){
    double* w = new double[size];
    w = normal_generator(size);
    for (int i = 0; i < size; i++){
        w[i] *= sqrt(t);
    }
    return w;
}

double* random_generator::geometric_brownian_motion(int size, double t, double r, double sigma, double s0){
    double* w = brownian_motion(size, t);
    double* st = new double[size];
    for (int i = 0; i < size; i++){
        st[i] = s0 * exp(sigma * w[i] + (r - sigma * sigma / 2) * t);
    }
    return st;
}
double* random_generator::stock_path(int size, double t, double r, double sigma, double s0){
    double* path = new double[size];
    double delta = t/size;
    path[0] = s0;
    for (int i = 1; i < size; i++){
        if (path[i - 1] > 0){
            path[i] = path[i-1] + r * delta * s0 + sigma * s0 * brownian_motion(1, delta)[0];
        }
        else{
            path[i] = 0;
        }
    }
    return path;
}
