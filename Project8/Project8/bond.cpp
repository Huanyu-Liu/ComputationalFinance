//
//  bond.cpp
//  Project8
//
//  Created by Huanyu Liu on 3/2/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include "bond.hpp"

Bond::Bond(double r0, double sigma, double k, double r_bar){
    this->r0 = r0;
    this->sigma = sigma;
    this->k = k;
    this->r_bar = r_bar;
}

double Bond::sum(vector<double> vector, int start, int end){
    double sum = 0;
    for (int i = start; i != end; ++i){
        sum += vector[i];
    }
    return sum;
}

double Bond::vasicek(double T, double face, int path_count){
    int step = (int)(T * 252);
    double r;
    double delta = T / step;
    random_generator rg;
    vector<double> bm;
    double sum = 0;
    double R;
    for (int i = 0; i != path_count; ++i){
        bm = rg.brownian_motion(step, delta);
        r = r0;
        R = 0;
        for (int j = 0; j != step; ++j){
            r += k * (r_bar - r) * delta + sigma * bm[j];
            R += r;
        }
        sum += exp(- delta * R);
    }
    return face * sum / path_count;
}

double Bond::coupon_bond(double *coupon, double *T, int cp_count, int path_count){
    double sum = 0;
    for (int i = 0; i != cp_count; ++i){
        sum += vasicek(T[i], coupon[i], path_count);
    }
    return sum;
}

double Bond::explicit_bond(double T, double t, double rt, double face){
    double B = 1 / k * (1 - exp(-k * (T - t)));
    double A = exp((r_bar - sigma * sigma / 2 / k / k) * (B - T + t) - sigma * sigma / 4 / k * B * B);
    return face * A * exp(-B * rt);
}

double Bond::option_zcb(double T, double t, double face, double x, int path_count){
    int step = (int)(t * 252);
    double r;
    double delta = 1.0 / 252;
    random_generator rg;
    vector<double> bm;
    double sum = 0;
    double R;
    double option, bond;
    for (int i = 0; i != path_count; ++i){
        bm = rg.brownian_motion(step, delta);
        r = r0;
        R = 0;
        for (int j = 0; j != step; ++j){
            r += k * (r_bar - r) * delta + sigma * bm[j];
            R += r;
        }
        R *= delta;
        bond = explicit_bond(T, t, r,face);
        option = bond - x > 0 ? bond - x : 0;
        option *= exp(-R);
        sum += option;
    }
    return sum / path_count;
}

double Bond::option_cpbond(double *coupon, double *T, int cp_count, double t, double x, int path_count){
    double delta = 1.0 / 252;
    int step = (int)(T[cp_count - 1] / delta);
    vector<double> bm;
    double Rt;
    vector<double> r;
    //vector<double> R(cp_count, r0);
    double R;
    random_generator rg;
    int temp = (int)(t * 252);
    double option, bond;
    double sum = 0;
    for (int i = 0; i != path_count; ++i){
        bm = rg.brownian_motion(step, delta);
        bond = 0;
        r.clear();
        r.push_back(r0);
        for (int j = 0; j != step; ++j){
            r.push_back(r[j] + k * (r_bar - r[j]) * delta + sigma * bm[j]);
            
        }
        Rt = delta * Bond::sum(r, 1, temp + 1);
        for (int j = 0; j != cp_count; ++j){
            R = delta * Bond::sum(r,temp + 1,(int)(T[j] / delta) + 1);
            bond += coupon[j] * exp(-R);
        }
        option = bond - x > 0 ? bond - x : 0;
        sum += option * exp(-Rt);
    }
    return sum / path_count;
}

double Bond::cir_option(double S, double face, double T, double x, int path_count){
    int step = (int)(S * 252);
    double r;
    double delta = 1.0 / 252;
    random_generator rg;
    vector<double> bm;
    double sum = 0;
    double R, Rt;
    double bond, option;
    for (int i = 0; i != path_count; ++i){
        bm = rg.brownian_motion(step, delta);
        r = r0;
        R = 0;
        Rt = 0;
        for (int j = 0; j != step; ++j){
            r += k * (r_bar - r) * delta + sigma * sqrt(r) * bm[j];
            if (j * delta > T){
                R += r;
            }
            else{
                Rt += r;
            }
        }
        bond = face * exp(-delta * R);
        option = bond - x > 0 ? bond - x : 0;
        sum += option * exp(-delta * Rt);
    }
    return sum / path_count;
}

double Bond::cir_explicit(double T, double t, double rt, double face){
    double h1 = sqrt(k * k + 2 * sigma * sigma);
    double h2 = (k + h1) / 2;
    double h3 = 2 * k * r_bar / sigma / sigma;
    double temp1 = exp(h1 * (T - t)) - 1;
    double temp2 = exp(h2 * (T - t));
    double B = temp1 / (h2 * temp1 + h1);
    double A = pow(h1 * temp2 / (h2 * temp1 + h1), h3);
    return 0;
}

double Bond::g2_model(double S, double face, double T, double strike, double phi, double rho, double a, double b, double eta, int path_count){
    double delta = 1.0 /252;
    int step = (int)(S / delta);
    double r, x0, y0, R, Rt;
    double bond, option;
    double sum = 0;
    random_generator rg;
    for (int i = 0; i != path_count; ++i){
        x0 = 0;
        y0 = 0;
        r = r0;
        R = 0;
        Rt = 0;
        vector<double> bm = rg.brownian_motion(2 * step, delta);
        for (int j = 0; j != step; ++j){
            x0 += -a * x0 * delta + sigma * bm[j];
            y0 += -b * y0 * delta + eta * (rho * bm[j] + (1 - rho) * bm[step + j]);
            r = x0 + y0 + phi;
            if (j * delta < T){
                R += r;
            }
            else{
                Rt += r;
            }
        }
        bond = face * exp(-delta * Rt);
        option = strike - bond > 0 ? strike - bond : 0;
        sum += option * exp(-delta * R);
    }
    return sum / path_count;
}

double Bond::chi_square(double x, double p, double q){
    double temp1 = exp(-q / 2);
    double temp2 = exp(-x / 2);
    double a = temp1 * pow(0.5, p / 2);
    return 0;
}
