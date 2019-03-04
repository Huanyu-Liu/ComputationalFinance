//
//  laguerre.hpp
//  Project5
//
//  Created by Huanyu Liu on 2/17/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#ifndef laguerre_hpp
#define laguerre_hpp

#pragma once

#include <stdio.h>
#include <cmath>
#include <iostream>
#include "matrix_cal.hpp"
#include "linear_equation.hpp"

#endif /* laguerre_hpp */

namespace laguerre {
    //double* laguerre(double * y, double ** x, int n, int k,int method);
    void laguerre(double * y, double ** x, double * result, int n);
    void laguerre(double * y, double ** x, double * result, int n, int k);
    void laguerre(double * y, double ** x, double * result, int n, int forward, int k, int method);
    void laguerre(double * y, double ** x, double * result, int n, int k, int method);
    inline double k1(double x, int method){
        if (method == 0){
            return exp(-x / 2);
        }
    
        else {
            return 1;
        }
    }
    inline double k2(double x, int method){
        if(method == 0){
            return exp(-x / 2) * (1 - x);
        }
    
        else if ( method == 1){
            return 2 * x;
        }
    
        else {
            return x;
        }
    }
    inline double k3(double x, int method){
        if (method == 0){
            return exp(-x / 2) * (1 - 2 * x + x * x / 2);
        }
    
        else if (method == 1){
            return 4 * x * x - 2;
        }
    
        else {
            return x * x;
        }
    }
    inline double k4(double x, int method){
        if (method == 0){
            return exp(-x / 2) * (1 - 3 * x + 1.5 * x * x - x * x * x / 6);
        }
    
        else if (method == 1){
            return 8 * x * x * x - 12 * x;
        }
    
        else{
            return x * x * x;
        }
    }
}
