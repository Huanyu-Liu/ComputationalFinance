//
//  halton_sequence.cpp
//  Project3
//
//  Created by Huanyu Liu on 1/30/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include "halton_sequence.hpp"

double* halton::halton_sequence(int length, int base){
    double* seq = new double[length];
    int numbits;
    double* vetbase = new double[length];
    double* workset = new double[length];
    for (int i = 0; i < length; i++){
        seq[i] = 0;
        vetbase[i] = 0;
        workset[i] = 0;
    }
    numbits = 1 + log(length) / log(base);
    for (int i = 0; i < numbits; i++){
        vetbase[i] = 1 / pow(base, i+1);
    }
    for (int i = 0; i < length; i++){
        int j = 0, ok = 0;
        while (ok == 0) {
            workset[j] ++;
            if (workset[j] < base){
                ok = 1;
            }
            else{
                workset[j] = 0;
                j++;
            }
        }
        for (int k = 0; k <= i; k++){
            seq[i] += workset[k] * vetbase[k];
        }
    }
    return seq;
}

double halton::integral_function(double x, double y){
    double cos_term = cos(2 * M_PI * y);
    cos_term = cos_term > 0 ? pow(cos_term, 1.0/3) : - pow(-cos_term, 1.0/3);
    return exp(-x * y) * (sin(6 * M_PI * x) + cos_term);
}

double halton::integral(int base1, int base2, int length){
    double* seq1 = halton_sequence(length, base1);
    double* seq2 = halton_sequence(length, base2);
    double sum = 0;
    for (int i = 0; i < length; i++){
        sum += integral_function(seq1[i], seq2[i]);
    }
    return sum / length;
}
