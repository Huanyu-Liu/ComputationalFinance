//
//  greeks.hpp
//  Project4
//
//  Created by Huanyu Liu on 2/1/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#ifndef greeks_hpp
#define greeks_hpp

#include <stdio.h>
#include "option.hpp"
#endif /* greeks_hpp */

namespace greeks{
    double delta(option op, int n);
    double theta(option op, int n);
    double gamma(option op, int n);
    double vega(option op, int n);
    double rho(option op, int n);
}
