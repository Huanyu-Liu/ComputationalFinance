//
//  linear_equation.hpp
//  Project5
//
//  Created by Huanyu Liu on 2/21/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#ifndef linear_equation_hpp
#define linear_equation_hpp

#include <stdio.h>
#include <cmath>
#endif /* linear_equation_hpp */

void LUPDecompose(double **A, int N, double Tol);
void LUPSolve(double **A, int *P, double *b, int N);
void linear_equation(double ** A, double * b, double * result, int N);
