//
//  main.cpp
//  Project4
//
//  Created by Huanyu Liu on 1/31/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "option.hpp"
#include "greeks.hpp"

#define SMALL_ENOUGH 0.000001

using std::cout;
using std::cin;
using std::endl;

std::ofstream data;
std::string file_path = "/Users/huanyu/Desktop/ComputationalFinance/data/Project4/";

int main(int argc, const char * argv[]) {
    // Problem 1
    double t = 0.5, r = 0.05, sigma = 0.24, s0 = 32, k = 30;
    int n[7] = {10,20,40,80,100,200,500};
    double price_a[7], price_b[7], price_c[7], price_d[7];
    bool is_call = true;
    bool is_european= true;
    option european_option1(s0,k,r,sigma,t,is_call,is_european);
    data.open(file_path + "problem1.csv");
    cout << "Problem 1: " << endl;
    for (int i = 0; i < 7; i++){
        price_a[i] = european_option1.binomial_method1(n[i]);
        price_b[i] = european_option1.binomial_method2(n[i]);
        price_c[i] = european_option1.binomial_method3(n[i]);
        price_d[i] = european_option1.binomial_method4(n[i]);
        cout << "N = " << n[i] << ", ";
        cout << "Method (a): "<< price_a[i] << ", "  << "Method (b): " << price_b[i] << ", " << "Method (c): " << price_c[i] << ", " << "Method (d): " << price_d[i] << endl;
        data << n[i] << "," << price_a[i] << ", " << price_b[i] << ", " << price_c[i] << ", " << price_d[i] << endl;
    }
    data.close();
    // Problem 2
    // (a)
    k = 1240;
    t = 1;
    r = 0.02;
    s0 = 1125.89;
    sigma = 0.234; // By using last 60 month daily price, and calculated the volatility in R
    option european_option2(s0, k, r, sigma, t, is_call, is_european);
    double option_price = european_option2.binomial_method1(252);
    double yahoo_price = 72.91;
    cout << endl << "Problem 2: " << endl;
    cout << "My estimated option price: " << option_price << endl;
    cout << "Google Option Price on Yahoo Finance: " << yahoo_price << endl;
    // (b)
    double counter = 0.01;
    double difference = yahoo_price - option_price;
    while (difference > SMALL_ENOUGH){
        sigma += counter;
        european_option2.set_sigma(sigma);
        difference = yahoo_price - european_option2.binomial_method1(252);
    }
    cout << "Volatility: " << sigma << endl;
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
    double delta_t;
    option european_option3(s0, k, r, sigma, t, is_call, is_european);
    data.open(file_path + "problem3.csv");
    cout << endl << "Problem 3: " << endl;
    for (int i = 20; i < 81; i+=2){
        european_option3.set_s0(i);
        delta_s = greeks::delta(european_option3, period);
        theta = greeks::theta(european_option3, period);
        gamma = greeks::gamma(european_option3, period);
        vega = greeks::vega(european_option3, period);
        rho = greeks::rho(european_option3, period);
        cout << "S_0 = " << i << ", ";
        cout << "Delta1: "<< delta_s << ", ";
        cout << "Theta: " << theta << ", ";
        cout << "Gamma: " << gamma << ", ";
        cout << "Vega: " << vega << ", ";
        cout << "Rho: " << rho << endl;
        data << i << "," << delta_s << "," << theta << "," << gamma << "," << vega << "," << rho << endl;
    }
    data.close();
    european_option3.set_s0(s0);
    data.open(file_path + "problem3b.csv");
    for (int i = 1; i < 39; i++){
        double t = i * 0.01;
        european_option3.set_t(t);
        delta_t = greeks::delta(european_option3, period);
        cout << "T = " << t << ", "<< "Delta2: " << delta_t << endl;
        data << t << "," << delta_t << endl;
    }
    data.close();
    // Problem 4
    t = 1;
    r = 0.05;
    sigma = 0.3;
    k = 100;
    period = 252;
    s0 = 80;
    double european_put_price;
    double american_put_price;
    option european_put(s0,k,r,sigma,t,!is_call,is_european);
    option american_put(s0,k,r,sigma,t,!is_call,!is_european);
    data.open(file_path + "problem4.csv");
    cout << endl << "Problem 4: " << endl;
    for (int i = 80; i < 121; i += 4){
        european_put.set_s0(i);
        american_put.set_s0(i);
        european_put_price = european_put.binomial_method1(period);
        american_put_price = american_put.binomial_method1(period);
        cout << "S_0 = " << i << ", ";
        cout << "European: " << european_put_price << ",  ";
        cout << "American: " << american_put_price << endl;
        data << i << "," << european_put_price << "," << american_put_price << endl;
    }
    data.close();
    
    // Problem 5
    t = 0.5;
    r = 0.05;
    s0 = 32;
    sigma = 0.24;
    k = 30;
    int parts[9] = {10, 15, 20, 40, 70, 80, 100, 200, 500};
    double european_trinomial, european_trinomial_log;
    option european_call5(s0,k,r,sigma,t,is_call,is_european);
    data.open(file_path + "problem5.csv");
    cout << endl << "Problem 5:" << endl;
    for (int i = 0; i < 9; i++){
        european_trinomial = european_call5.trinomial(parts[i]);
        european_trinomial_log = european_call5.trinomial_log(parts[i]);
        cout << "N = " << parts[i] << ", ";
        cout << "Trinomial: " << european_trinomial << ",   ";
        cout << "Log Trinomial: " << european_trinomial_log << endl;
        data << parts[i] << "," << european_trinomial << "," << european_trinomial_log << endl;
    }
    
    // Problem 6
    int b1, b2;
    cout << endl << "Problem 6: " << endl;
    cout << "Please enter the price for S_0: ";
    cin >> s0;
    cout << "Please enter the price for K: ";
    cin >> k;
    cout << "Please enter the price for T: ";
    cin >> t;
    cout << "Please enter the price for r: ";
    cin >> r;
    cout << "Please enter the price for Sigma: ";
    cin >> sigma;
    cout << "Please enter the price for N: ";
    cin >> period;
    cout << "Please enter the price for b1: ";
    cin >> b1;
    cout << "Please enter the price for b2: ";
    cin >> b2;
    option european_call6(s0,k,r,sigma,t,is_call,is_european);
    cout << endl << "Problem 6:" << endl;
    cout << "The price of the european call option is: " << european_call6.halton_option_price(period, b1, b2) << endl;
    return 0;
}
