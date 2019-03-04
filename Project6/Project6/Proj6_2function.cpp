//
//  Proj6_2function.cpp
//  Project6
//
//  Created by Huanyu Liu on 2/21/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include "Proj6_2function.hpp"

double * Proj6_2function(double lambda1, double lambda2, double T){
    double mu = -0.1, sigma = 0.2, gamma = -0.4;
    double delta = 0.25, alpha = 0.7, epsilon = 0.95, r0 = 0.02;
    double beta = (epsilon - alpha) / T;
    double r = (r0 + delta * lambda2) / 12;
    double v0 = 20000, L0 = 22000;
    int size = 1000;
    double step = T / size;
    double n = T * 12;
    double pmt = L0 * r / (1 - 1 / pow(1 + r,n));
    double a = pmt / r;
    double b = pmt / r / pow(1 + r, n);
    double c = 1 + r;
    random_generator rg;
    double exp1;
    
    double * v = new double[size];
    double LQ, VQ, VS;
    double Q;
    double S;
    int simulation_count = 1000;
    double value = 0, payoff;
    double tau;
    double expect_tau = 0;
    int default_count = 0;
    for (int i = 0; i < simulation_count; ++i){
        payoff = 0;
        tau = T;
        Q = T;
        S = rg.exponential(1, 1/lambda2)[0];
        exp1 = rg.exponential(1, 1/lambda1)[0];
        
        v[0] = v0;
        for (int j = 0; j < size - 1; ++j){
            double t = j * step;
            if (t > exp1){
                exp1 += rg.exponential(1, 1/lambda1)[0];
                v[j] *= (1 + gamma);
            }
            if (t > S){
                VS = v[j];
                tau = S;
                break;
            }
            double  Lt = a - b * pow(c, 12 * t);
            double qt = alpha + beta * t;
            if (v[j] <= qt * Lt){
                Q = t;
                LQ = Lt;
                VQ = v[j];
                tau = Q;
                break;
            }
            
            v[j + 1] = v[j] + v[j] * mu * step + sigma * v[j] * rg.brownian_motion(1, step)[0];
        }
        if (tau < T){
            default_count++;
            expect_tau += tau;
            //std::cout << "tau: " << tau << std::endl;
            if (Q < S){
                payoff = LQ > epsilon * VQ ? LQ - epsilon * VQ : 0;
                value += payoff * exp(-r0 * Q);
            }
            else{
                payoff = abs(a - b * pow(c, 12 * S) - epsilon * VS);
                value += payoff * exp(-r0 * S);
            }
        }
    }
    double * result = new double[3];
    result[0] = value / simulation_count;
    result[1] = default_count * 1.0 / simulation_count;
    result[2] = expect_tau / default_count;
    return result;
}
