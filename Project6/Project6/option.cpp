//
//  option.cpp
//  Project5
//
//  Created by Huanyu Liu on 2/18/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include "option.hpp"

option::option(double s0, double r, double sigma, double x, double t, bool is_call){
    this->s0 = s0;
    this->r = r;
    this->sigma = sigma;
    this->x = x;
    this->t = t;
    this->is_call = is_call;
}

double option::look_back(int size, int path_count){
    random_generator rg;
    path = new double*[path_count];
    for (int i = 0; i < path_count; ++i){
        path[i] = rg.stock_path(size, t, r, sigma, s0);
    }
    double payoff, sum = 0;
    double smax, smin;
    for (int i = 0; i < path_count; ++i){
        smax = path[i][0];
        smin = path[i][0];
        for (int j = 0; j < size; ++j){
            if (smax < path[i][j]) {smax = path[i][j];}
            if (smin > path[i][j]) {smin = path[i][j];}
        }
        if (is_call){
            payoff = smax > x ? smax - x : 0;
        }
        else{
            payoff = x > smin ? x - smin : 0;
        }
        sum += payoff;
    }
    return sum * exp(-r * t) / path_count;
    
}

void option::set_sigma(double sigma){
    this->sigma = sigma;
}
