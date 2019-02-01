//
//  binomial_method.hpp
//  Project4
//
//  Created by Huanyu Liu on 1/31/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#ifndef binomial_method_hpp
#define binomial_method_hpp

#include <stdio.h>
#include <cmath>
#include "max.hpp"
#endif /* binomial_method_hpp */

namespace binomial {
    double binomial_method1(int n, double r, double sigma, double s0, double k, double t);
    double binomial_method2(int n, double r, double sigma, double s0, double k, double t);
    double binomial_method3(int n, double r, double sigma, double s0, double k, double t);
    double binomial_method4(int n, double r, double sigma, double s0, double k, double t);
    double binomial_tree(int n, double s0, double k, double u, double d, double p);
}
