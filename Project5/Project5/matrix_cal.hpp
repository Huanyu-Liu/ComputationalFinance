//
//  matrix_cal.hpp
//  Project5
//
//  Created by Huanyu Liu on 2/18/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#ifndef matrix_cal_hpp
#define matrix_cal_hpp

#include <stdio.h>

#endif /* matrix_cal_hpp */

namespace matrix_cal {
    double * matrix(double ** a, double * b, int k);
    double * matrix_multi(double ** a, double * b, int k);
    double ** matrix_inv(double ** a, int k);
    double matrix_det(double ** a, int k);
    double ** getCofactor(double ** a, int p, int q, int n);
    double ** adjoint(double **a,int k);
}
