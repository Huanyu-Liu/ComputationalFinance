//
//  integral.hpp
//  Project2
//
//  Created by Huanyu Liu on 1/22/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#ifndef integral_hpp
#define integral_hpp

#include <stdio.h>
#include <cmath>

namespace integral {
    double f(double x);
    double euler(int size);
    double monte_carlo(int size);
    double importance_sampling(int size);
}
#endif /* integral_hpp */
