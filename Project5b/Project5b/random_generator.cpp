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


void random_generator::normal_generator(double * normal, int size){
    double u1, u2;
    for (int i = 0; i < size; i+=2){
        u1 = uniform_generator();
        u2 = uniform_generator();
        normal[i] = sqrt(-2 * log(u1)) * cos(2 * M_PI * u2);
        normal[i+1] = sqrt(-2 * log(u1)) * sin(2 * M_PI * u2);
        if (i == size - 6){
            std::cout << "got it" << std::endl;
        }
    }
    
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

void random_generator::bivariate_normal(double ** xy, int size,double x_sigma, double y_sigma, double rho){
    double * normal = new double[size * 2];
    normal_generator(normal, size * 2);
    for (int i = 0; i < size; i++){
        xy[0][i] = x_sigma * normal[i];
        xy[1][i] = y_sigma * rho * normal[i] + y_sigma * sqrt(1 - rho * rho) * normal[i+size];
    }
    delete [] normal;
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

void random_generator::brownian_motion(double * bm, int size, double t){
    normal_generator(bm, size);
    for (int i = 0; i < size; ++i){
        bm[i] *= sqrt(t);
    }
}

double* random_generator::brownian_motion(int size, double t){
    double* w = new double[size];
    w = normal_generator(size);
    for (int i = 0; i < size; i++){
        w[i] *= sqrt(t);
    }
    return w;
}

void random_generator::geometric_brownian_motion(double * geobm, int size, double t, double r, double sigma, double s){
    double * w = new double[size];
    brownian_motion(w, size, t);
    for (int i = 0; i < size; ++i){
        geobm[i] = s * exp(sigma * w[i] + (r - sigma * sigma / 2) * t);
    }
    delete [] w;
}

double* random_generator::geometric_brownian_motion(int size, double t, double r, double sigma, double s0){
    double* w = brownian_motion(size, t);
    double* st = new double[size];
    for (int i = 0; i < size; i++){
        st[i] = s0 * exp(sigma * w[i] + (r - sigma * sigma / 2) * t);
    }
    return st;
}

void random_generator::stock_path(double * path, int size, double t, double r, double sigma, double s0){
    double delta = t / size;
    double * bm = new double[size - 1];
    brownian_motion(bm, size - 1, delta);
    path[0] = s0;
    for (int i = 1; i < size; ++i){
        if (path[i - 1] > 0){
            path[i] = path[i-1] + r * delta * path[i-1] + sigma * path[i - 1] * bm[i - 1];
        }
        else{
            path[i] = 0;
        }
    }
    delete [] bm;
}

double* random_generator::stock_path(int size, double t, double r, double sigma, double s0){
    double* path = new double[size];
    double delta = t/size;
    double* bm = brownian_motion(size - 1, delta);
    path[0] = s0;
    for (int i = 1; i < size; i++){
        if (path[i - 1] > 0){
            path[i] = path[i-1] + r * delta * path[i-1] + sigma * path[i - 1] * bm[i - 1];
        }
        else{
            path[i] = 0;
        }
    }
    return path;
}

unsigned long random_generator::get_seed(){
    return seed;
}
void random_generator::set_seed(unsigned long seed){
    this->seed = seed;
}
void random_generator::delfault(){
    set_seed(1025);
}
