//
//  main.cpp
//  Project5
//
//  Created by Huanyu Liu on 2/15/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include <iostream>
#include <cmath>
#include "option.hpp"


using std::cout;
using std::endl;
using std::cin;

inline double hermite_k3(double x){return 4 * x * x - 2;}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    //random_generator rg;
    int size = 100;
    int path_count = 100000;
    double r = 0.06;
    double s0 = 36;
    double sigma = 0.2;
    double t = 0.5;
    int k;
    int method = 0;
    double x = 40;
    
    // Problem 1
    // (a)
    
    cout << "Problem1" << endl << endl;

    option op1(s0,r,sigma,x,t,size,path_count);
    cout << "Laguerre polynomial:" << endl;
    k = 2;
    cout << "s0 = 36, t = 0.5, k = 2: " << op1.price(k, method) << endl;
    k = 3;
    cout << "s0 = 36, t = 0.5, k = 3: " << op1.price(k, method) << endl;
    k = 4;
    cout << "s0 = 36, t = 0.5, k = 4: " << op1.price(k, method) << endl;
    cout << endl << "Hermite polynomial: " << endl;
    method = 1;
    k = 2;
    cout << "s0 = 36, t = 0.5, k = 2: " << op1.price(k, method) << endl;
    k = 3;
    cout << "s0 = 36, t = 0.5, k = 3: " << op1.price(k, method) << endl;
    k = 4;
    cout << "s0 = 36, t = 0.5, k = 4: " << op1.price(k, method) << endl;
    cout << endl << "Simple Monomials: " << endl;
    method = 2;
    k = 2;
    cout << "s0 = 36, t = 0.5, k = 2: " << op1.price(k, method) << endl;
    k = 3;
    cout << "s0 = 36, t = 0.5, k = 3: " << op1.price(k, method) << endl;
    k = 4;
    cout << "s0 = 36, t = 0.5, k = 4: " << op1.price(k, method) << endl;

    s0 = 40;
    t = 1;
    option op2(s0,r,sigma,x,t,size,path_count);
    k = 2;
    
    cout << endl << "Laguerre polynomial:" << endl;
    method = 0;
    cout << "s0 = 40, t = 1, k = 2: " << op2.price(k, method) << endl;
    k = 3;
    cout << "s0 = 40, t = 1, k = 3: " << op2.price(k, method) << endl;
    k = 4;
    cout << "s0 = 40, t = 1, k = 4: " << op2.price(k, method) << endl;
    cout << endl << "Hermite polynomial: " << endl;
    method = 1;
    k = 2;
    cout << "s0 = 40, t = 1, k = 2: " << op2.price(k, method) << endl;
    k = 3;
    cout << "s0 = 40, t = 1, k = 3: " << op2.price(k, method) << endl;
    k = 4;
    cout << "s0 = 40, t = 1, k = 4: " << op2.price(k, method) << endl;
    cout << endl << "Simple Monomials: " << endl;
    method = 2;
    k = 2;
    cout << "s0 = 40, t = 1, k = 2: " << op2.price(k, method) << endl;
    k = 3;
    cout << "s0 = 40, t = 1, k = 3: " << op2.price(k, method) << endl;
    k = 4;
    cout << "s0 = 40, t = 1, k = 4: " << op2.price(k, method) << endl;

    s0 = 44;
    t = 2;
    option op3(s0,r,sigma,x,t,size,path_count);
    k = 2;
    op1.set(44,2);
//    cout << op1.get_s0() << endl;
//    cout << op1.get_t() << endl;
//    cout << op1.get_sigma() << endl;
    cout << endl << "Laguerre polynomial:" << endl;
    method = 0;
    cout << "s0 = 44, t = 2, k = 2: " << op3.price(k, method) << endl;
    k = 3;
    cout << "s0 = 44, t = 2, k = 3: " << op3.price(k, method) << endl;
    k = 4;
    cout << "s0 = 44, t = 2, k = 4: " << op3.price(k, method) << endl;
    cout << endl << "Hermite polynomial: " << endl;
    method = 1;
    k = 2;
    cout << "s0 = 44, t = 2, k = 2: " << op3.price(k, method) << endl;
    k = 3;
    cout << "s0 = 44, t = 2, k = 3: " << op1.price(k, method) << endl;
    k = 4;
    cout << "s0 = 44, t = 2, k = 4: " << op1.price(k, method) << endl;
    cout << endl << "Simple Monomials: " << endl;
    method = 2;
    k = 2;
    cout << "s0 = 44, t = 2, k = 2: " << op1.price(k, method) << endl;
    k = 3;
    cout << "s0 = 44, t = 2, k = 3: " << op1.price(k, method) << endl;
    k = 4;
    cout << "s0 = 44, t = 2, k = 4: " << op1.price(k, method) << endl;
    // Problem 2
    // (a)
    cout << endl << "Problem 2" << endl << endl;
    double s02 = 65;
    x = 60;
    double forward_date = 0.2;
    
    double T = 1;
    option op2a(s02,r,sigma,x,T,size,path_count);
    cout << "European Forward start: " << op2a.forward_option(forward_date) << endl;
    cout << "American Forward start: " << op2a.forward_american_option(forward_date) << endl;
    
    return 0;
}
