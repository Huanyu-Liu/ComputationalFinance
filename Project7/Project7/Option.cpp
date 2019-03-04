//
//  Option.cpp
//  Project7
//
//  Created by Huanyu Liu on 2/28/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include "Option.hpp"

Option::Option(double s0, double r, double sigma, double k, double t){
    this->s0 = s0;
    this->r = r;
    this->sigma = sigma;
    this->k = k;
    this->t = t;
}

void Option::log_stock(double * stock_price, int N, double delta_x){
    double x0 = std::log(s0);
    for (int i = 0; i < 2 * N + 1; ++i){
        stock_price[i] = x0 + (N - i) * delta_x;
    }
}

void Option::stock(double * stock_price, int N, double delta_s){
    for (int i = 0; i < 2 * N + 1; ++i){
        stock_price[i] = s0 + (N - i) * delta_s;
    }
}
void Option::efd(int N, double delta, double delta_x, double * F){
    double temp1 = sigma * sigma / delta_x / delta_x;
    double temp2 = (r - sigma * sigma / 2) / 2 /delta_x;
    int m = (int)(t / delta);
    double pu = delta * (temp1 / 2 + temp2);
    double pm = 1 - delta * temp1 - r * delta;
    double pd = delta * (temp1 / 2 - temp2);
    int dimension = 2 * N + 1;
    double ** A = new double * [dimension];
    for (int i = 0; i < dimension; ++i){
        A[i] = new double[dimension]();
    }
    A[0][0] = pu;
    A[0][1] = pm;
    A[0][2] = pd;
    A[dimension - 1][dimension - 3] = pu;
    A[dimension - 1][dimension - 2] = pm;
    A[dimension - 1][dimension - 1] = pd;
    double * B = new double[dimension]();
    double * stock_price = new double[dimension];
    log_stock(stock_price,N,delta_x);
    B[dimension - 1] = exp(stock_price[dimension - 2]) - exp(stock_price[dimension - 1]);
    for (int i = 1; i < dimension - 1; ++i){
        A[i][i - 1] = pu;
        A[i][i] = pm;
        A[i][i+1] = pd;
    }
    for (int i = 0; i < dimension; ++i){
        double payoff = k - exp(stock_price[i]);
        F[i] = payoff > 0 ? payoff : 0;
    }
    delete [] stock_price;
    double * result = new double[dimension];
    for (int i = 0; i < m; ++i){
        matrix_cal::matrix_multi(A, F, result, dimension);
        matrix_cal::addition(result, B, F, dimension);
    }
    
    for (int i = 0; i < dimension; ++i){
        delete [] A[i];
    }
    delete [] A;
    delete [] B;
    delete [] result;
}

void Option::ifd(int N, double delta, double delta_x, double * F){
    double temp1 = sigma * sigma / delta_x / delta_x;
    double temp2 = (r - sigma * sigma / 2 ) / delta_x;
    double pu = -0.5 * delta * (temp1 + temp2);
    double pm = 1 + delta * temp1 + r * delta;
    double pd = -0.5 * delta * (temp1 - temp2);
    int m = (int)(t / delta);
    int dimension = 2 * N + 1;
    double ** A = new double * [dimension];
    for (int i = 0; i < dimension; ++i){
        A[i] = new double[dimension]();
    }
    A[0][0] = 1;
    A[0][1] = -1;
    A[dimension - 1][dimension - 2] = 1;
    A[dimension - 1][dimension - 1] = -1;
    double * B = new double[dimension]();
    double * stock_price = new double[dimension];
    log_stock(stock_price,N,delta_x);
    B[dimension - 1] = exp(stock_price[dimension - 2]) - exp(stock_price[dimension - 1]);
    for (int i = 1; i < dimension - 1; ++i){
        A[i][i - 1] = pu;
        A[i][i] = pm;
        A[i][i+1] = pd;
    }
    for (int i = 0; i < dimension; ++i){
        double payoff = k - exp(stock_price[i]);
        F[i] = payoff > 0 ? payoff : 0;
    }
    delete [] stock_price;
    int * p = new int[dimension];
    matrix_cal::LUPDecompose(A, p, dimension, SMALL);
    for (int i = 0; i < m; ++i){
        for (int j = 1; j < dimension - 1; ++j){
            B[j] = F[j];
        }
        matrix_cal::LUPSolve(A, p, B, F, dimension);
    }
    for (int i = 0; i < dimension; ++i){
        delete [] A[i];
    }
    delete [] A;
    delete [] B;
    delete [] p;
}

void Option::cnfd(int N, double delta, double delta_x, double * F){
    double temp1 = sigma * sigma / delta_x / delta_x;
    double temp2 = (r - sigma * sigma / 2) / delta_x;
    double pu = -0.25 * delta * (temp1 + temp2);
    double pm = 1 + delta * temp1 / 2 + r * delta / 2;
    double pd = -0.25 * delta * (temp1 - temp2);
    int m = (int)(t / delta);
    int dimension = 2 * N + 1;
    double ** A = new double * [dimension];
    for (int i = 0; i < dimension; ++i){
        A[i] = new double[dimension]();
    }
    A[0][0] = 1;
    A[0][1] = -1;
    A[dimension - 1][dimension - 2] = 1;
    A[dimension - 1][dimension - 1] = -1;
    double * B = new double[dimension]();
    double * stock_price = new double[dimension];
    log_stock(stock_price,N,delta_x);
    B[dimension - 1] = exp(stock_price[dimension - 2]) - exp(stock_price[dimension - 1]);
    for (int i = 1; i < dimension - 1; ++i){
        A[i][i - 1] = pu;
        A[i][i] = pm;
        A[i][i+1] = pd;
    }
    for (int i = 0; i < dimension; ++i){
        double payoff = k - exp(stock_price[i]);
        F[i] = payoff > 0 ? payoff : 0;
    }
    delete [] stock_price;
    int * p = new int[dimension];
    matrix_cal::LUPDecompose(A, p, dimension, SMALL);
    for (int i = 0; i < m; ++i){
        for (int j = 1; j < dimension - 1; ++j){
            B[j] = F[j - 1] * -pu - (pm - 2) * F[j] - pd * F[j + 1];
        }
        matrix_cal::LUPSolve(A, p, B, F, dimension);
    }
    for (int i = 0; i < dimension; ++i){
        delete [] A[i];
    }
    delete [] A;
    delete [] B;
    delete [] p;
}

void Option::american_efd(double delta, double delta_s, bool is_call, double * F){
    int N = (int)(s0 / delta_s);
    int dimension = 2 * N + 1;
    int m = (int)(t / delta);
    double * stock_price = new double[dimension];
    stock(stock_price, N, delta_s);
    double * B = new double[dimension]();
    double * exercise = new double[dimension];
    if (is_call){
        B[0] = stock_price[0] - stock_price[1];
        for (int i = 0; i < dimension; ++i){
            exercise[i] = stock_price[i] - k > 0 ? stock_price[i] - k : 0;
            F[i] = exercise[i];
        }
    }
    else{
        B[dimension - 1] = stock_price[dimension - 2] - stock_price[dimension - 1];
        for (int i = 0; i < dimension; ++i){
            exercise[i] = k - stock_price[i] > 0 ? k - stock_price[i] : 0;
            F[i] = exercise[i];
            //std::cout << F[i] << std::endl;
        }
    }
    delete [] stock_price;
    double * pu = new double[dimension - 2];
    double * pm = new double[dimension - 2];
    double * pd = new double[dimension - 2];
    for (int i = 0; i < dimension - 2; ++i){
        double temp1 = r * (i + 1) / 2;
        double temp2 = sigma * sigma * (i + 1) * (i + 1);
        pu[i] = delta * (temp1 + temp2 / 2);
        pm[i] = 1 - delta * (temp2 + r);
        pd[i] = delta * (-temp1 + temp2 / 2);
    }
    double ** A = new double * [dimension];
    for (int i = 0; i < dimension; ++i){
        A[i] = new double[dimension]();
    }
    A[0][0] = pu[dimension - 3];
    A[0][1] = pm[dimension - 3];
    A[0][2] = pd[dimension - 3];
    A[dimension - 1][dimension - 3] = pu[0];
    A[dimension - 1][dimension - 2] = pm[0];
    A[dimension - 1][dimension - 1] = pd[0];
    for (int i = 1; i < dimension - 1; ++i){
        A[i][i - 1] = pu[2 * N - 1 - i];
        A[i][i] = pm[2 * N - 1 - i];
        A[i][i + 1] = pd[2 * N - 1 - i];
    }
    delete [] pu;
    delete [] pm;
    delete [] pd;
    double * ecv = new double[dimension];
    for (int i = 0; i < m; ++i){
        matrix_cal::matrix_multi(A, F, ecv, dimension);
        for (int j = 0; j < dimension; ++j){
            //std::cout << B[j] << std::endl;
            ecv[j] += B[j];
            F[j] = exercise[j] > ecv[j] ? exercise[j] : ecv[j];
            
        }
    }
    for (int i = 0; i < dimension; ++i){
        delete [] A[i];
    }
    delete [] A;
    delete [] B;
    delete [] exercise;
    delete [] ecv;
}

void Option::american_ifd(double delta, double delta_s, bool is_call, double * F){
    int N = (int)(s0 / delta_s);
    int dimension = 2 * N + 1;
    int m = (int)(t / delta);
    double * stock_price = new double[dimension];
    stock(stock_price, N, delta_s);
    double * B = new double[dimension]();
    double * exercise = new double[dimension];
    if (is_call){
        B[0] = stock_price[0] - stock_price[1];
        for (int i = 0; i < dimension; ++i){
            exercise[i] = stock_price[i] - k > 0 ? stock_price[i] - k : 0;
            F[i] = exercise[i];
        }
    }
    else{
        B[dimension - 1] = stock_price[dimension - 2] - stock_price[dimension - 1];
        for (int i = 0; i < dimension; ++i){
            exercise[i] = k - stock_price[i] > 0 ? k - stock_price[i] : 0;
            F[i] = exercise[i];
            //std::cout << F[i] << std::endl;
        }
    }
    delete [] stock_price;
    double * a1 = new double[dimension - 2];
    double * a2 = new double[dimension - 2];
    double * a3 = new double[dimension - 2];
    for (int i = 0; i < dimension - 2; ++i){
        double temp1 = r * (i + 1) / 2;
        double temp2 = sigma * sigma * (i + 1) * (i + 1);
        a1[i] = -delta * (temp1 + temp2 / 2);
        a2[i] = 1 + delta * (temp2 + r);
        a3[i] = -delta * (-temp1 + temp2 / 2);
    }
    double ** A = new double * [dimension];
    for (int i = 0; i < dimension; ++i){
        A[i] = new double[dimension]();
    }
    A[0][0] = 1;
    A[0][1] = -1;
    A[dimension - 1][dimension - 2] = 1;
    A[dimension - 1][dimension - 1] = -1;
    for (int i = 1; i < dimension - 1; ++i){
        A[i][i - 1] = a1[2 * N - 1 - i];
        A[i][i] = a2[2 * N - 1 - i];
        A[i][i + 1] = a3[2 * N - 1 - i];
    }
    delete [] a1;
    delete [] a2;
    delete [] a3;
    int * p = new int[dimension];
    matrix_cal::LUPDecompose(A, p, dimension, SMALL);
    double * ecv = new double[dimension];
    for (int i = 0; i < m; ++i){
        for (int j = 1; j < dimension - 1; ++j){
            B[j] = F[j];
        }
        matrix_cal::LUPSolve(A, p, B, ecv, dimension);
        
        for (int j = 0; j < dimension; ++j){
            //std::cout << B[j] << std::endl;
            F[j] = exercise[j] > ecv[j] ? exercise[j] : ecv[j];
            
        }
    }
    for (int i = 0; i < dimension; ++i){
        delete [] A[i];
    }
    delete [] A;
    delete [] B;
    delete [] exercise;
    delete [] ecv;
    delete [] p;
}

void Option::american_cnfd(double delta, double delta_s, bool is_call, double * F){
    int N = (int)(s0 / delta_s);
    int dimension = 2 * N + 1;
    int m = (int)(t / delta);
    double * stock_price = new double[dimension];
    stock(stock_price, N, delta_s);
    double * B = new double[dimension]();
    double * exercise = new double[dimension];
    if (is_call){
        B[0] = stock_price[0] - stock_price[1];
        for (int i = 0; i < dimension; ++i){
            exercise[i] = stock_price[i] - k > 0 ? stock_price[i] - k : 0;
            F[i] = exercise[i];
        }
    }
    else{
        B[dimension - 1] = stock_price[dimension - 2] - stock_price[dimension - 1];
        for (int i = 0; i < dimension; ++i){
            exercise[i] = k - stock_price[i] > 0 ? k - stock_price[i] : 0;
            F[i] = exercise[i];
            //std::cout << F[i] << std::endl;
        }
    }
    delete [] stock_price;
    double * a1 = new double[dimension - 2];
    double * a2 = new double[dimension - 2];
    double * a3 = new double[dimension - 2];
    double * b1 = new double[dimension - 2];
    double * b2 = new double[dimension - 2];
    double * b3 = new double[dimension - 2];
    for (int i = 0; i < dimension - 2; ++i){
        double temp1 = r * (i + 1);
        double temp2 = sigma * sigma * (i + 1) * (i + 1);
        a1[i] = -delta * (temp1 + temp2) / 4;
        a2[i] = 1 + delta * (temp2 + r) / 2;
        a3[i] = -delta * (-temp1 + temp2) / 4;
        b1[i] = -a1[i];
        b2[i] = 2 - a2[i];
        b3[i] = -a3[i];
    }
    double ** A = new double * [dimension];
    for (int i = 0; i < dimension; ++i){
        A[i] = new double[dimension]();
    }
    A[0][0] = 1;
    A[0][1] = -1;
    A[dimension - 1][dimension - 2] = 1;
    A[dimension - 1][dimension - 1] = -1;
    for (int i = 1; i < dimension - 1; ++i){
        A[i][i - 1] = a1[2 * N - 1 - i];
        A[i][i] = a2[2 * N - 1 - i];
        A[i][i + 1] = a3[2 * N - 1 - i];
    }
    delete [] a1;
    delete [] a2;
    delete [] a3;
    int * p = new int[dimension];
    matrix_cal::LUPDecompose(A, p, dimension, SMALL);
    double * ecv = new double[dimension];
    for (int i = 0; i < m; ++i){
        for (int j = 1; j < dimension - 1; ++j){
            B[j] = F[j - 1] * b1[j - 1] + F[j] * b2[j - 1] + F[j + 1] * b3[j - 1];
        }
        matrix_cal::LUPSolve(A, p, B, ecv, dimension);
        
        for (int j = 0; j < dimension; ++j){
            //std::cout << B[j] << std::endl;
            F[j] = exercise[j] > ecv[j] ? exercise[j] : ecv[j];
            
        }
    }
    delete [] b1;
    delete [] b2;
    delete [] b3;
    for (int i = 0; i < dimension; ++i){
        delete [] A[i];
    }
    delete [] A;
    delete [] B;
    delete [] exercise;
    delete [] ecv;
    delete [] p;
}
