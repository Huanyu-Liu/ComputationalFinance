//
//  heston_model.hpp
//  Project3
//
//  Created by Huanyu Liu on 1/29/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#ifndef heston_model_hpp
#define heston_model_hpp

#include <stdio.h>
# include "random_generator.hpp"
#endif /* heston_model_hpp */

class heston{
    double rho, r, s0, v0, sigma, alpha, beta, K, T;
    random_generator* rand;
public:
    heston(double rho, double r, double s0, double v0, double sigma, double alpha, double beta,double K, double T);
    template <typename Function>
    double heston_model(int simulation_count, Function&& f1, Function&& f2, Function&& f3);
    double european_call_r(int simulation_count);
    double european_call_p(int simulation_count);
    double european_call_f(int simulation_count);
    template <typename Function>
    double european_call(int simulation_count, Function&& f1, Function&& f2, Function&& f3);
    inline static double f_1(double x) {return abs(x);}
    inline static double f_2(double x) {return x;}
    inline static double f_3(double x) {return x > 0 ? x : 0;}
};
