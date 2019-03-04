//
//  matrix_cal.hpp
//  Project5
//
//  Created by Huanyu Liu on 2/18/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#ifndef matrix_cal_hpp
#define matrix_cal_hpp
#define SMALL 0.000000001

#pragma once

#include <stdio.h>
#include <cmath>
#endif /* matrix_cal_hpp */

namespace matrix_cal {
    double * matrix(double ** a, double * b, int k);
    void matrix(double **a, double *b, double * result, int k);
    double * matrix_multi(double ** a, double * b, int k);
    void matrix_multi(double **a, double *b, double * result, int k);
    //double ** matrix_inv(double ** a, int k);
    void matrix_inv(double **a, int k);
    double matrix_det(double ** a, int k);
    double ** getCofactor(double ** a, int p, int q, int n);
    void getCofactor(double **m, double ** temp, int p, int q, int n);
    double ** adjoint(double **a,int k);
    void adjoint(double ** a, double ** adj, int N);
    void addition(double * a, double * b, double * result, int k);
    void LUPDecompose(double **A, int * P, int N, double Tol);
    void LUPDecompose(double **A, double ** updated_A,int * P, int N, double Tol);

    void LUPSolve(double **A, int *P, double *b, double * result, int N);
    void linear_equation(double ** A, double * b, double * result,int N);
}
