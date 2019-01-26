//
//  integral.cpp
//  Project2
//
//  Created by Huanyu Liu on 1/22/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include "integral.hpp"
#include "random_generator.hpp"

namespace integral {
    double f(double x){
        return sqrt(1 - x * x);
    }
    
    double euler(int size){
        double sum = 0;
        double delta = 1.0 / size;
        for (int i = 0; i < size; i++){
            sum += f(i * delta) * delta;
        }
        return 4 * sum;
    }
    
    double monte_carlo(int size){
        double sum = 0;
        double uf;
        random_generator r;
        for (int i = 0; i < size; i++){
            uf = r.uniform_generator();
            sum += f(uf);
        }
        return 4 * sum / size;
    }
}
