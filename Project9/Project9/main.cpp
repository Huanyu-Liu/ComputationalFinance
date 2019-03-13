//
//  main.cpp
//  Project9
//
//  Created by Huanyu Liu on 3/3/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "mbs.hpp"
using std::cout;
using std::endl;
using std::ofstream;

ofstream file;
std::string path = "/Users/huanyu/Desktop/ComputationalFinance/data/Project9/";

int main(int argc, const char * argv[]) {
    // Problem 1
    // (a)
    
    cout << "Problem 1: " << endl;
    cout << "(a)" << endl;
    double T = 30;
    double wac = 0.08;
    double loan = 100000;
    double r0 = 0.078;
    double k = 0.6;
    double r_bar = 0.08;
    double sigma = 0.12;
    int month = 1;
    int simulation_count = 1000;
    double price;
    MBS mbs(r0, k, r_bar,sigma,T,wac,loan);
//    cout << mbs.price(month, 0, simulation_count) << endl;
//
//    // (b)
//    cout << "(b)" << endl;
//    file.open(path + "problem1b.csv");
//    k = 0.3;
//    while (k < 1) {
//        mbs.set_k(k);
//        price = mbs.price(month, 0, simulation_count);
//        cout << "k: " << k << ", price: " << price << endl;
//        file << k << "," << price << endl;
//        k += 0.1;
//    }
//    mbs.set_k(0.6);
//    file.close();
//    // (c)
//    file.open(path + "problem1c.csv");
//    r_bar = 0.03;
//    while (r_bar < 0.1){
//        mbs.set_r_bar(r_bar);
//        price = mbs.price(month, 0, simulation_count);
//        cout << "r bar: " << r_bar << ", price: " << price << endl;
//        file << r_bar << "," << price << endl;
//        r_bar += 0.01;
//    }
//    mbs.set_r_bar(0.08);
//    file.close();
//    // (d)
//    sigma = 0.1;
//    file.open(path + "problem1d.csv");
//    while (sigma < 0.21) {
//        mbs.set_sigma(sigma);
//        price = mbs.price(month, 0, simulation_count);
//        cout << "sigma: " << sigma << ", price: " << price << endl;
//        file << sigma << "," << price << endl;
//        sigma += 0.01;
//    }
//    mbs.set_sigma(0.12);
//    file.close();
    // Problem 2
    cout << endl << "Problem 2" << endl;
    double market_price = 110000;
    auto [oas, duration, convexity] = mbs.oas(month, market_price, simulation_count);
    cout << "OAS: " << oas << endl;
    cout << "Duration: " << duration << endl;
    cout << "Convexity: " << convexity << endl;
    return 0;
}
