//
//  mbs.cpp
//  Project9
//
//  Created by Huanyu Liu on 3/3/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include "mbs.hpp"

MBS::MBS(double r0, double k, double r_bar, double sigma, double T, double wac, double loan){
    this->r0 = r0;
    this->k = k;
    this->r_bar = r_bar;
    this->sigma = sigma;
    this->T = T;
    this->wac = wac;
    this->loan = loan;
}

double MBS::CPR(double t, int month, double pvt, double rt){
    double delta = 1.0 / 12;
    int step = (int)(10 / delta);
    double r10 = rt;
    random_generator rg;
    vector<double> bm = rg.brownian_motion(step, delta);
    for (int i = 0; i != step; ++i){
        r10 += k * (r_bar - r10) * delta + sigma * sqrt(r10) * bm[i];
    }
    double RI = 0.28 + 0.14 * atan(-8.57 + 430 * (wac - r10));
    double BU = 0.3 + 0.7 * pvt / loan;
    double SG = t / 30 > 1 ? t / 30 : 1;
    double SY[12] = {0.94,0.76,0.74,0.95,0.98,0.92,0.98,1.1,1.18,1.22,1.23,0.98};
    return RI * BU * SG * SY[month - 1];
}

double MBS::price(int month){
    double delta = 1.0 / 12;
    double pvt = loan;
    double TPP, ct;
    double temp1, temp2;
    double r = wac / 12;
    int step = (int)(T * 12);
    random_generator rg;
    vector<double> bm = rg.brownian_motion(step, delta);
    double rt = r0;
    double R = r0;
    double sum = 0;
    for (int i = 0; i != step; ++i){
        
        temp1 = 1 / (pow(1 + r, i - step) - 1);
        temp2 = 1 - pow(CPR(i, month, pvt, rt), delta);
        TPP = pvt * r * temp1 + (pvt - pvt * r * temp1) * temp2;
        ct = TPP + pvt * r;
        pvt -= TPP;
        rt += k * (r_bar - rt) * delta + sigma * sqrt(rt) * bm[i];
        R += rt;
        sum += ct * exp(-R * delta);
        month = month % 12 + 1;
    }
    return sum;
}
