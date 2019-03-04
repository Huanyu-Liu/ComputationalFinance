//
//  main.cpp
//  Project6
//
//  Created by Huanyu Liu on 2/20/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "option.hpp"
#include "Proj6_2function.hpp"

using std::cout;
using std::endl;


std::ofstream file;

int main(int argc, const char * argv[]) {
    // insert code here...
    
    std::string path = "/Users/huanyu/Desktop/ComputationalFinance/data/Project6/";
    file.open(path + "project6_1.csv");
    // Problem 1
    double r = 0.03;
    double s0 = 98;
    double x = 100;
    double t = 1;
    bool is_call = true;
    int size = 100;
    int path_count = 10000;
    option call_op(s0,r,0.12,x,t,is_call);
    option put_op(s0,r,0.12,x,t,!is_call);
    double call_price, put_price;
    cout << "Problem 1" << endl << endl;
    for (int i = 1; i < 11; ++i){
        
        file << i * 0.04 + 0.08 << ",";
        call_price = call_op.look_back(size, path_count);
        put_price = put_op.look_back(size, path_count);
        file << call_price << "," << put_price << endl;
        cout << "sigma = " << i * 0.04 + 0.08 << endl;
        cout << "call price: " << call_price << endl;
        cout << "put price: " << put_price << endl << endl;
        call_op.set_sigma(0.12 + i * 0.04);
        put_op.set_sigma(0.12 + i * 0.04);
    }
    file.close();
    
    std::ofstream file[6];
    // Problem 2

    for (int i = 0; i < 6; ++i){
        char character = 'a' + i;
        file[i].open(path + "project6_2" + character + ".csv");
    }
    double * result1;
    
    double lambda1 = 0.2;
    double lambda2 = 0.4;
    double T = 5;
    cout << endl << "Problem 2" << endl;
    for (int i = 1; i * 0.05 <0.45; ++i){
        result1 = Proj6_2function(i * 0.05,lambda2,T);
        cout << "lambda1 = " << i * 0.05 << endl;
        cout << "value: " << result1[0] << endl;
        cout << "default prob: " << result1[1] << endl;
        cout << "expected exercise: " << result1[2] << endl << endl;
    }
    
    for (int i = 0; i * 0.1 <0.9; ++i){
        result1 = Proj6_2function(lambda1,i * 0.1,T);
        cout << "lambda2 = " << i * 0.1 << endl;
        cout << "value: " << result1[0] << endl;
        cout << "default prob: " << result1[1] << endl;
        cout << "expected exercise: " << result1[2] << endl << endl;
    }

    for (int i = 3; i < 9; ++i){
        result1 = Proj6_2function(lambda1,lambda2,i * 1.0);
        cout << "T = " << i << endl;
        cout << "value: " << result1[0] << endl;
        cout << "default prob: " << result1[1] << endl;
        cout << "expected exercise: " << result1[2] << endl << endl;
    }
    for (int i = 0; i < 6; ++i){
        if (i < 3){
            for (int j = 1; j * 0.05 < 0.45; ++j){
                file[i] << "," << j * 0.05;
            }
        }
        else{
            for (int j = 0; j * 0.1 < 0.9; ++j){
                file[i] << "," << j * 0.1;
            }
        }
        file[i] << endl;
    }
    

    for (int i = 3; i < 9; ++i){
        
        for (int j = 0; j < 6; ++j){
            file[j] << i << ",";
        }
        for (int j = 1; j * 0.05 < 0.45; ++j){
            result1 = Proj6_2function(j * 0.05,lambda2, i);
            for (int k = 0; k < 3; ++k){
                file[k] << result1[k];
            }
            if (j < 8){
                for (int k = 0; k < 3; ++k){
                    file[k] << ",";
                }
            }
        }
        
        for (int j = 0; j * 0.1 < 0.9; ++j){
            result1 = Proj6_2function(lambda1, j * 0.1, i);
            for (int k = 0; k < 3; ++k){
                file[k + 3] << result1[k];
            }
            if (j < 8){
                for (int k = 3; k < 6; ++k){
                    file[k] << ",";
                }
            }
        }
        for (int k = 0; k < 6; ++k){
            file[k] << endl;
        }
    }
    for (int i = 0; i < 6; ++i){
        file[i].close();
    }
    return 0;
}
