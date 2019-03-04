//
//  laguerre.cpp
//  Project5
//
//  Created by Huanyu Liu on 2/17/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include "laguerre.hpp"

void laguerre::laguerre(double * y, double ** x, double * result, int n){
    
    double * b = new double[4]();
    double ** A = new double*[4];
    for (int i = 0; i < 4; ++i){
        A[i] = new double[4]();
    }
    double k_1 = 1, k_2, k_3, k_4;
    for (int i = 0; i < 100000; ++i){
        k_2 = x[i][n];
        k_3 = x[i][n] * x[i][n];
        k_4 = k_2 * k_3;
        b[0] += y[i] * 1;
        b[1] += y[i] * k_2;
        b[2] += y[i] * k_3;
        b[3] += y[i] * k_4;
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
    }
    double * a = new double[4];
    int *p = new int[4];
    matrix_cal::LUPDecompose(A, p, 4, SMALL);
    matrix_cal::LUPSolve(A, p, b, a, 4);
   // matrix_cal::matrix(A, b, a, 4);
    
    for (int i = 0; i < 100000; ++i){
        
        result[i] = a[0] + a[1] * x[i][n] + a[2] * x[i][n] * x[i][n] + a[3] * x[i][n] * x[i][n] * x[i][n];
    }
    delete [] a;
    delete [] b;
    delete [] p;
//    //delete [] a;
    for (int i = 0; i < 4; ++i){
        delete [] A[i];
    }
    delete [] A;
}

void laguerre::laguerre(double * y, double ** x, double * result, int n, int k){
    
    double * b = new double[k]();
    double ** A = new double*[k];
    for (int i = 0; i < k; ++i){
        A[i] = new double[k]();
    }
    double k_1 = 1, k_2, k_3, k_4;
    for (int i = 0; i < 100000; ++i){
        k_2 = x[i][n];
        k_3 = x[i][n] * x[i][n];
        k_4 = k_2 * k_3;
        b[0] += y[i] * 1;
        b[1] += y[i] * k_2;
        
        A[0][0] += k_1 * k_1;
        A[1][1] += k_2 * k_2;
        A[0][1] += k_1 * k_2;
        A[1][0] += k_1 * k_2;
        if (k > 2 && k < 4){
            A[0][2] += k_1 * k_3;
            A[1][2] += k_2 * k_3;
            A[2][2] += k_3 * k_3;
            A[2][0] += k_1 * k_3;
            A[2][1] += k_2 * k_3;
            b[2] += y[i] * k_3;
        }
        else if (k >= 4){
            A[0][2] += k_1 * k_3;
            A[1][2] += k_2 * k_3;
            A[2][2] += k_3 * k_3;
            A[2][0] += k_1 * k_3;
            A[2][1] += k_2 * k_3;
            b[2] += y[i] * k_3;
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
    double * a = new double[k];
    //int *p = new int[k];
//    matrix_cal::LUPDecompose(A, p, k, 0);
//    matrix_cal::LUPSolve(A, p, b, a, k);
    matrix_cal::matrix(A, b, a, k);
    
    for (int i = 0; i < 100000; ++i){
        
        result[i] = a[0] + a[1] * x[i][n];
        if (k > 2){
            result[i] += a[2] * x[i][n] * x[i][n];
        }
        if (k > 3){
            result[i] += a[3] * x[i][n] * x[i][n] * x[i][n];
        }
    }
    delete [] a;
    delete [] b;
    //delete [] p;
    //delete [] a;
    for (int i = 0; i < k; ++i){
        delete [] A[i];
    }
    delete [] A;
}

void laguerre::laguerre(double * y, double ** x, double * result, int n, int k, int method){
    
    double * b = new double[k]();
    double ** A = new double*[k];
    for (int i = 0; i < k; ++i){
        A[i] = new double[k]();
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
    double * a = new double[k];
    int *p = new int[k];
    matrix_cal::LUPDecompose(A, p, k, SMALL);
    matrix_cal::LUPSolve(A, p, b, a, k);
    
    //matrix_cal::matrix(A, b, a, k);
    
    for (int i = 0; i < 100000; ++i){
        
        result[i] = a[0] * k1(x[i][n], method) + a[1] * k2(x[i][n], method);
        if (k > 2){
            result[i] += a[2] * k3(x[i][n], method);
        }
        if (k > 3){
            result[i] += a[3] * k4(x[i][n], method);
        }
    }
    delete [] a;
    delete [] b;
    delete [] p;
    //delete [] a;
    for (int i = 0; i < k; ++i){
        delete [] A[i];
    }
    delete [] A;
}


void laguerre::laguerre(double * y, double ** x, double * result, int n, int forward, int k,int method){
    double * b = new double[k]();
    double ** A = new double*[k];
    for (int i = 0; i < k; ++i){
        A[i] = new double[k]();
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
    }
    A[4][0] = A[0][4];
    A[4][1] = A[1][4];
    A[4][2] = A[2][4];
    A[4][3] = A[3][4];
    double * a = new double[k];
    int *p = new int[k];
    matrix_cal::LUPDecompose(A, p, k, SMALL);
    matrix_cal::LUPSolve(A, p, b, a, k);
    for (int i = 0; i < 100000; ++i){
        
        result[i] = a[0] * k1(x[i][n], method) + a[1] * k2(x[i][n], method) + a[2] * k3(x[i][n], method) + a[3] * k2(x[i][forward], method) + a[4] * k3(x[i][forward],method);
    }
    delete [] b;
    delete [] a;
    delete [] p;
    for (int i = 0; i < k; ++i){
        delete [] A[i];
    }
    delete [] A;
}
