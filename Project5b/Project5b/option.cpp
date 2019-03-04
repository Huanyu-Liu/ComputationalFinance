//
//  option.cpp
//  Project5
//
//  Created by Huanyu Liu on 2/18/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include "option.hpp"

option::option(double s0, double r, double sigma, double x, double t, int size, int path_count){
    this->s0 = s0;
    this->r = r;
    this->sigma = sigma;
    this->x = x;
    this->t = t;
    this->size = size;
    this->path_count = path_count;
    random_generator rg;
    path = new double*[path_count];
    for (int i = 0; i < path_count; ++i){
        path[i] = new double[size];
        rg.stock_path(path[i], size, t, r, sigma, s0);
    }
}

//option::~option(){
//    for (int i = 0; i < path_count; ++i){
//        delete [] path[i];
//    }
//    delete [] path;
//}

option::option(const option & op){
    for (int i = 0; i < path_count; ++i){
        for (int j = 0; j < size; ++j){
            path[i][j] = op.path[i][j];
        }
    }
}

option & option::operator=(const option & op){
    if (this == &op) return *this;
    else {
        // free the storage pointed to by Items
        for (int i = 0; i < path_count; ++i){
            delete path[i];
        }
        delete [] path;
        size = op.size;
        path_count = op.path_count;
        path = new double * [path_count];
        for (int i = 0; i < path_count; ++i){
            path[i] = new double[size];
        }
        for (int i = 0; i < path_count; ++i){
            for (int j = 0; j < size; ++j){
                path[i][j] = op.path[i][j];
            }
        }
    }
    return *this;
}

double option::price(int k, int method){
    int* index = new int[path_count];
    double delta = t / size;
    double * test = new double[path_count];
    double * yn = new double[path_count];
    for (int i = 0; i < path_count; ++i){
        if (path[i][size - 1] < x){
            index[i] = size - 1;
        }
        else{
            index[i] = size;
        }
    }
    for (int i = size - 2; i > 0; --i){
        for (int j = 0; j < path_count; ++j){
            if (index[j] < size){
                double temp = index[j] - i;
                test[j] = exp(-r * delta * temp) * (x - path[j][index[j]]);
            }
            else{
                test[j] = 0;
            }
        }
        laguerre::laguerre(test, path, yn, i);
        
        for (int j = 0; j < path_count; ++j){
            if (yn[j] < x - path[j][i] && x - path[j][i] > 0){
                index[j] = i;
            }
        }
    }
    double sum = 0;
    for (int i = 0; i < path_count; ++i){
        if (index[i] < size){
            sum += exp(-r * delta * index[i]) * (x - path[i][index[i]]);
            if (x - path[i][index[i]] < 0){
                std::cout << "(x - path[i][index[i]]): " << (x - path[i][index[i]]) << std::endl;
            }
        }
        
    }
    delete [] index;
    delete [] test;
    delete [] yn;
    return sum / path_count;
}


double option::forward_option(double forward_date){
    double sum = 0;
    double temp1;
    double delta = t / size;
    int forward = int(forward_date / delta);
    //std::cout << forward << std::endl;
    for (int i = 0; i < path_count; i++){
        temp1 = path[i][forward] - path[i][size - 1];
        sum += temp1 > 0 ? temp1 : 0;
    }
    return exp(-r * t)  * sum / path_count;
}

double option::forward_american_option(double forward_date){
    int* index = new int[path_count];
    double delta = t / size;
    double * test = new double[path_count];
    double * exercise = new double[path_count];
    double * yn = new double[path_count];
    int forward = int(forward_date / delta);
    for (int i = 0; i < path_count; ++i){
        exercise[i] = path[i][forward];
    }
    for (int i = 0; i < path_count; ++i){
        if (path[i][size - 1] < exercise[i]){
            index[i] = size - 1;
        }
        else{
            index[i] = size;
        }
    }
    for (int i = size - 2; i > forward; --i){
        for (int j = 0; j < path_count; ++j){
            if (index[j] < size){
                double temp = index[j] - i;
                test[j] = exp(-r * delta * temp) * (exercise[j] - path[j][index[j]]);
            }
            else{
                test[j] = 0;
            }
        }
        laguerre::laguerre(test, path, yn, i, forward, 5, 2);
        
        for (int j = 0; j < path_count; ++j){
            if (yn[j] < exercise[j] - path[j][i] && exercise[j] - path[j][i] > 0){
                index[j] = i;
            }
        }
    }
    double sum = 0;
    for (int i = 0; i < path_count; ++i){
        if (index[i] < size){
            sum += (exercise[i] - path[i][index[i]]);
            if (exercise[i] - path[i][index[i]] < 0){
                std::cout << "(x - path[i][index[i]]): " << (exercise[i] - path[i][index[i]]) << std::endl;
            }
        }
        
    }
    delete [] index;
    delete [] test;
    delete [] exercise;
    delete [] yn;
    return sum / path_count;
}

void option::set(double s0,  double t, double r, double sigma, double x){
    if (!isnan(s0)){
        this->s0 = s0;
    }
    if (!isnan(r)){
        this->r = r;
    }
    if (!isnan(sigma)){
        this->sigma = sigma;
    }
    if (!isnan(x)){
        this->x = x;
    }
    if (!isnan(t)){
        this->t = t;
    }
    random_generator rg;
    for (int i = 0; i < path_count; ++i){
        rg.stock_path(path[i], size, this->t, this->r, this->sigma, this->s0);
    }

}

