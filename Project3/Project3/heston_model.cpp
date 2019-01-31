//
//  heston_model.cpp
//  Project3
//
//  Created by Huanyu Liu on 1/29/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include "heston_model.hpp"

heston::heston(double rho, double r, double s0, double v0, double sigma, double alpha, double beta, double K, double T){
    this->rand = new random_generator;
    this->rho = rho;
    this->r = r;
    this->s0 = s0;
    this->sigma = sigma;
    this->v0 = v0;
    this->alpha = alpha;
    this->beta = beta;
    this->K = K;
    this->T = T;
    
}
template <typename Function>
double heston::heston_model(int simulation_count, Function&& f1, Function&& f2, Function&& f3){
    double s_sum = s0;
    double v_sum = v0;
    double delta = T / simulation_count;
    double f3_v;
    double** w;
    w = rand->bivariate_normal(simulation_count, sqrt(delta), sqrt(delta), rho);
    for (int i = 0; i < simulation_count; i++){
        f3_v = sqrt(f3(v_sum));
        s_sum += r * s_sum * delta + f3_v * s_sum * w[0][i];
        v_sum = f1(v_sum) + alpha * (beta - f2(v_sum)) * delta + sigma * f3_v * w[1][i];
    }
    return s_sum;
}
double heston::european_call_r(int simulation_count){
    return european_call(simulation_count, f_1, f_1, f_1);
}

double heston::european_call_p(int simulation_count){
    return european_call(simulation_count, f_2, f_2, f_3);
}

double heston::european_call_f(int simulation_count){
    return european_call(simulation_count, f_2, f_3, f_3);
}

template <typename Function>
double heston::european_call(int simulation_count, Function&& f1, Function&& f2, Function&& f3){
    double sum = 0;
    double temp;
    rand->delfault();
    for (int i = 0; i < simulation_count; i++){
        temp = heston_model(simulation_count, f1, f2, f3) - K;
        sum += temp > 0 ? temp : 0;
    }
    return exp(-r * T) * sum / simulation_count;
}
