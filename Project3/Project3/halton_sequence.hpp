//
//  halton_sequence.hpp
//  Project3
//
//  Created by Huanyu Liu on 1/30/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#ifndef halton_sequence_hpp
#define halton_sequence_hpp

#include <stdio.h>
#include <cmath>
#endif /* halton_sequence_hpp */

namespace halton {
    double* halton_sequence(int length, int base);
    double integral_function(double x, double y);
    double integral(int base1, int base2, int length);
}
