//
//  main.cpp
//  Project4
//
//  Created by Huanyu Liu on 1/31/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include <iostream>
#include "option.hpp"
#include "greeks.hpp"

using std::cout;
using std::endl;
int main(int argc, const char * argv[]) {
    // Problem 1
    double t = 0.5, r = 0.05, sigma = 0.24, s0 = 32, k = 30;
    int n[7] = {10,20,40,80,100,200,500};
    double price_a[7], price_b[7], price_c[7], price_d[7];
    bool is_call = true;
    bool is_european= true;
    option european_option1(s0,k,r,sigma,t,is_call,is_european);

    for (int i = 0; i < 7; i++){
        price_a[i] = european_option1.binomial_method1(n[i]);
        price_b[i] = european_option1.binomial_method2(n[i]);
        price_c[i] = european_option1.binomial_method3(n[i]);
        price_d[i] = european_option1.binomial_method4(n[i]);
        cout << price_a[i] << ", " << price_b[i] << ", " << price_c[i] << ", " << price_d[i] << endl;
    }
    // Problem 2
    k = 1240;
    t = 1;
    r = 0.02;
    s0 = 1125.89;
    sigma = 0.234; // By using last 60 month daily price, and calculated the volatility in R
    option european_option2(s0, k, r, sigma, t, is_call, is_european);
    double option_price = european_option2.binomial_method1(252);
    double yahoo_price = 72.91;
    cout << option_price << endl;
    cout << "Google Option Price on Yahoo Finance: " << yahoo_price << endl;

    // Problem 3
    s0 = 49;
    k = 50;
    r = 0.03;
    sigma = 0.2;
    t = 0.3846;
    int period = 100;
    double delta_s;
    double theta;
    double gamma;
    double vega;
    double rho;
    option european_option3(s0, k, r, sigma, t, is_call, is_european);
    for (int i = 20; i < 81; i+=2){
        european_option3.set_s0(i);
        delta_s = greeks::delta(european_option3, period);
        theta = greeks::theta(european_option3, period);
        gamma = greeks::gamma(european_option3, period);
        vega = greeks::vega(european_option3, period);
        rho = greeks::rho(european_option3, period);

        cout << delta_s << endl;
        cout << "Theta: " << theta << endl;
        cout << "Gamma: " << gamma << endl;
        cout << "Vega: " << vega << endl;
        cout << "Rho: " << rho << endl;
    }
    european_option3.set_s0(s0);
    for (int i = 1; i < 39; i++){
        european_option3.set_t(i * 0.01);
        
        cout << greeks::delta(european_option3, period) << endl;
    }

    // Problem 4
    t = 1;
    r = 0.05;
    sigma = 0.3;
    k = 100;
    period = 252;
    s0 = 80;
    option european_put(120,k,r,sigma,t,!is_call,is_european);
    double european_put_price = european_put.binomial_method1(period);
    option american_put(120,k,r,sigma,t,!is_call,!is_european);
    double american_put_price = american_put.binomial_method1(period);
    cout << european_put_price << endl;
    cout << american_put_price << endl;
    return 0;
}
