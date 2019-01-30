//
//  stats.hpp
//  Project2
//
//  Created by Huanyu Liu on 1/21/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#ifndef stats_hpp
#define stats_hpp
#include <stdio.h>
#include <cmath>

#endif /* stats_hpp */

namespace stats {
    double mean(double * x, int size);
    double variance(double * x, int size);
    double covariance(double * x, double * y, int size);
    double correlation(double * x, double * y, double size);
    double normal_cdf(double x);
}

