//
//  stats.cpp
//  Project2
//
//  Created by Huanyu Liu on 1/21/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include "stats.hpp"

namespace stats {
    double mean(double * x, int size){
        double sum = 0;
        for (int i = 0; i < size; i++){
            sum += x[i];
        }
        return sum/size;
    }
    
    double variance(double * x, int size){
        double sum = 0;
        double mu = mean(x, size);
        for (int i = 0; i < size; i++){
            sum += (x[i] - mu) * (x[i] - mu);
        }
        return sum / (size - 1);
    }
    
    double covariance(double * x, double * y, int size){
        double sum = 0;
        double x_mean = mean(x,size);
        double y_mean = mean(y, size);
        for (int i = 0; i < size; i++){
            sum += (x[i] - x_mean) * (y[i] - y_mean);
        }
        return sum / (size - 1);
    }
    
    double correlation(double * x, double * y, double size){
        return (covariance(x, y, size)/sqrt(variance(x, size) * variance(y, size)));
    }
    
    double normal_cdf(double x){
        return erfc(-x/sqrt(2))/2;
    }
    double standard_deviation(double * x, int size){
        double v = variance(x, size);
        return sqrt(v);
    }
}
