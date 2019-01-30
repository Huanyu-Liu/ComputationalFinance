//
//  main.cpp
//  Project3
//
//  Created by Huanyu Liu on 1/26/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include <iostream>
#include "random_generator.hpp"
#include "stats.hpp"
#include "problem1.hpp"
#include "problem2.hpp"

using std::cout;
using std::endl;

//double y_t(double y0, double t, int size, random_generator & r){
//    double delta = t/size;
//    //random_generator rg(seed);
//    double* z = r.brownian_motion(size, delta);
//    double sum = y0;
//    double b = (1 + t*t*t)/3;
//    for (int i = 0; i < size; i++){
//        double temp = sum;
//        sum += (2 / (1+t) * temp + b) * delta + b * z[i];
//    }
//    return sum;
//}
//
//double x_t(double x0, double t, int size, random_generator & r){
//    double delta = t/size;
//    double* w = r.brownian_motion(size, t);
//    double temp;
//    for (int i = 0; i < size; i++){
//        temp = x0;
//        x0 += (0.2 - 0.5 * temp) * delta + 2.0/3 * w[i];
//    }
//    return x0;
//}

//double x_t_2(double x0, double t, int size, random_generator & r){
//    double delta = t/size;
//    double* w = r.brownian_motion(size, t);
//    double* z = r.brownian_motion(size, t);
//    double temp;
//    for (int i = 0; i < size; i++){
//        temp = x0;
//        x0 += (0.25 * temp * delta) + 1.0/3 * temp * w[i] - 0.75 * temp * z[i];
//    }
//    return x0;
//}
//
//double problem2(double* array, int size){
//    double sum = 0;
//    for (int i = 0; i < size; i++){
//        double x = 1 + array[i];
//        sum += (x > 0) ? pow(x,1.0/3) : -pow(-x,1.0/3);
//    }
//    return sum/size;
//}

int main(int argc, const char * argv[]) {
    // Problem 1
    int size = 1000;
    double t = 2;
    double y_0 = 0.75;
    int n = 1000;
    double y2[n];
    double counter = 0;
    double x2[n];
    double x2_1_3[n];
    double x0 = 1;
    double y3[n];
    double sum = 0;
    random_generator rg;
    for (int i = 0; i < n; i++){
        y2[i] = problem1::y_t(y_0, t, size, rg);
        if (y2[i] > 5) counter++;
    }
    for (int i = 0; i < n; i++){
        x2[i] = problem1::x_t(x0,t,size,rg);
        x2_1_3[i] = x2[i] > 0 ? pow(x2[i],1.0/3) : -pow(-x2[i],1.0/3);
    }
    for (int i = 0; i < n; i++){
        y3[i] = problem1::y_t(y_0, 3, size, rg);
    }
    for (int i = 0; i < n; i++){
        if (x2[i] > 1){
            sum += y2[i] * x2[i];
        }
    }
    double expectation_x2 = stats::mean(x2,n);
    double expectation_y3 = stats::mean(y3,n);
    cout << counter/n << endl;
    cout << expectation_x2 << endl;
    cout << expectation_y3 << endl;
    cout << sum / n << endl;
    
    // Problem 2
    
    double x3_2[n];
    double y3_2[n];
    
    t = 3;
    for (int i = 0; i < n; i++){
        x3_2[i] = problem2::x_t(x0, t, size, rg);
    }
    double expectation_x3_2 = problem2::expectation(x3_2, n);
    
    double* w;
    double* z;
    w = rg.brownian_motion(size, 3);
    z = rg.brownian_motion(size, 3);
    
    for (int i = 0; i < size; i++){
        y3_2[i] = exp(-0.08 * t + 1.0/3 * w[i] + 0.75 * z[i]);
    }
    double expectation_y3_2 = problem2::expectation(y3_2, size);
    cout << expectation_x3_2 << endl;
    cout << expectation_y3_2 << endl;
    
    // Problem 3
    // (a)
    
    return 0;
}
