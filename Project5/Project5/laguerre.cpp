//
//  laguerre.cpp
//  Project5
//
//  Created by Huanyu Liu on 2/17/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include "laguerre.hpp"

double* laguerre::laguerre(double * y, double ** x, int n, int k, int method){

    double * b = new double[k];
    double ** A = new double*[k];
    for (int i = 0; i < k; ++i){
        A[i] = new double[k];
    }
    double k_1, k_2, k_3, k_4;
    for (int i = 0; i < 100000; ++i){
        k_1 = k1(x[i][n], method);
        k_2 = k2(x[i][n], method);
        
        b[0] += y[i] * k_1;
        b[1] += y[i] * k_2;
        A[0][0] += k_1 * k_1;
        A[1][1] += k_2 * k_2;
        A[0][1] += k_1 * k_2;
        A[1][0] += k_1 * k_2;

        if (k > 2){
            k_3 = k3(x[i][n], method);
            b[2] += y[i] * k_3;
            A[0][2] += k_1 * k_3;
            A[1][2] += k_2 * k_3;
            A[2][2] += k_3 * k_3;
            A[2][0] += k_1 * k_3;
            A[2][1] += k_2 * k_3;
        }
        if (k > 3){
            k_4 = k4(x[i][n], method);
            b[3] += y[i] * k_4;
            A[0][3] += k_1 * k_4;
            A[1][3] += k_2 * k_4;
            A[2][3] += k_3 * k_4;
            A[3][3] += k_4 * k_4;
            A[3][0] += k_1 * k_4;
            A[3][1] += k_2 * k_4;
            A[3][2] += k_3 * k_4;
        }
    }
    double * a = matrix_cal::matrix(A,b,k);
//    if (n == 98 || n == 97){
//        for (int i = 0; i < 3; ++i){
//            std::cout << a[i] << std::endl;
//        }
//    }
    double * result;
    result = new double[100000];
    for (int i = 0; i < 100000; ++i){
        
        result[i] = a[0] * k1(x[i][n], method) + a[1] * k2(x[i][n], method);
        if (k > 2){
            result[i] += a[2] * k3(x[i][n], method);
        }
        if (k > 3){
            result[i] += a[3] * k4(x[i][n], method);
        }
        
//        if (k == 2){
//            result[i] = a[0] * k1(x[i][n], method) + a[1] * k2(x[i][n], method);
//        }
//        else if (k == 3){
//            result[i] = a[0] * k1(x[i][n], method) + a[1] * k2(x[i][n], method) + a[2] * k3(x[i][n], method);
//        }
//        else{
//            result[i] = a[0] * k1(x[i][n], method) + a[1] * k2(x[i][n], method) + a[2] * k3(x[i][n], method) + a[3] * k4(x[i][n], method);
//        }
    }
    return result;
}


double* laguerre::laguerre(double * y, double ** x, int n, int forward, int k,int method){
    double * b = new double[k];
    double ** A = new double*[k];
    for (int i = 0; i < k; ++i){
        A[i] = new double[k];
    }
    double k_1, k_2, k_3, k_4, k_5;
    for (int i = 0; i < 100000; ++i){
        k_1 = k1(x[i][n], method);
        k_2 = k2(x[i][n], method);
        k_3 = k3(x[i][n], method);
        k_4 = k2(x[i][forward], method);
        k_5 = k3(x[i][forward], method);
        b[0] += y[i] * k_1;
        b[1] += y[i] * k_2;
        b[2] += y[i] * k_3;
        b[3] += y[i] * k_4;
        b[4] += y[i] * k_5;
        A[0][0] += k_1 * k_1;
        A[1][1] += k_2 * k_2;
        A[0][1] += k_1 * k_2;
        A[1][0] += k_1 * k_2;
        A[0][2] += k_1 * k_3;
        A[1][2] += k_2 * k_3;
        A[2][2] += k_3 * k_3;
        A[2][0] += k_1 * k_3;
        A[2][1] += k_2 * k_3;
        A[0][3] += k_1 * k_4;
        A[1][3] += k_2 * k_4;
        A[2][3] += k_3 * k_4;
        A[3][3] += k_4 * k_4;
        A[3][0] += k_1 * k_4;
        A[3][1] += k_2 * k_4;
        A[3][2] += k_3 * k_4;
        A[0][4] += k_1 * k_5;
        A[1][4] += k_2 * k_5;
        A[2][4] += k_3 * k_5;
        A[3][4] += k_4 * k_5;
        A[4][4] += k_5 * k_5;
        
//        if (k > 2){
//            k_3 = k3(x[i][n], method);
//            b[2] += y[i] * k_3;
//            A[0][2] += k_1 * k_3;
//            A[1][2] += k_2 * k_3;
//            A[2][2] += k_3 * k_3;
//            A[2][0] += k_1 * k_3;
//            A[2][1] += k_2 * k_3;
//        }
//        if (k > 3){
//            k_4 = k4(x[i][n], method);
//            b[3] += y[i] * k_4;
//            A[0][3] += k_1 * k_4;
//            A[1][3] += k_2 * k_4;
//            A[2][3] += k_3 * k_4;
//            A[3][3] += k_4 * k_4;
//            A[3][0] += k_1 * k_4;
//            A[3][1] += k_2 * k_4;
//            A[3][2] += k_3 * k_4;
//        }
    }
    A[4][0] = A[0][4];
    A[4][1] = A[1][4];
    A[4][2] = A[2][4];
    A[4][3] = A[3][4];
    double * a = matrix_cal::matrix(A,b,k);
    //    if (n == 98 || n == 97){
    //        for (int i = 0; i < 3; ++i){
    //            std::cout << a[i] << std::endl;
    //        }
    //    }
    double * result;
    result = new double[100000];
    for (int i = 0; i < 100000; ++i){
        
        result[i] = a[0] * k1(x[i][n], method) + a[1] * k2(x[i][n], method) + a[2] * k3(x[i][n], method) + a[3] * k2(x[i][forward], method) + a[4] * k3(x[i][forward],method);
        //        if (k == 2){
        //            result[i] = a[0] * k1(x[i][n], method) + a[1] * k2(x[i][n], method);
        //        }
        //        else if (k == 3){
        //            result[i] = a[0] * k1(x[i][n], method) + a[1] * k2(x[i][n], method) + a[2] * k3(x[i][n], method);
        //        }
        //        else{
        //            result[i] = a[0] * k1(x[i][n], method) + a[1] * k2(x[i][n], method) + a[2] * k3(x[i][n], method) + a[3] * k4(x[i][n], method);
        //        }
    }
    return result;
}
