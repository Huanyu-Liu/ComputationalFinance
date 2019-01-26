/*
    Created by Huanyu Liu, 1/15/2019
*/
#include <iostream>
#include <numeric>
#include <cmath>
#include <stdlib.h>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

// Generate 1 uniform distributed number on [0,1],
// by ax+b % m, a = 7^5 = 16807, m = 2^31 - 1

ofstream output;

class UniformGenerator{   
    unsigned long m;      
    unsigned long a;
    unsigned long seed;
public:
    UniformGenerator(unsigned long x = (1 << 10) + 1){
        m = (1 << 31) - (unsigned long)1;
        a = 16807;
        seed = x;
    }
    double generator(){
        seed = (a * seed) % m;
        return seed / (double)m;
    }
};

// Combination function to calculate choose k from N
int combination(int N, int k){
    if (k > N) return 0;
    else if (k == N) return 1;
    else if (k * 2 > N) k = N - k;
    else if (k == 1) return N;
    else if (k == 0) return 1;

    int result = N;
    for (int i = 2; i <= k; i++ ){
        result *= (N - i + 1);
        result /= i;
    }
    return result;
}

// Get the mean of an array of either doubles or integers
template <class T>
double mean_func(T* v, int size){  
    T sum = 0;
    for (int i = 0; i < size; i++){
        sum += v[i];
    }
    double mean = sum / (double)size;
    return mean;
}

// Get the mean of an array of either doubles or integers
template <class T>
double standard_deviation(T* v, double mean, int size){
    double sum = 0;
    for (int i = 0; i < size; i++){
        sum += pow((v[i] - mean),2);
    }
    return sqrt(sum / (size - 1));
}


int main(){
    output.open("Project1_Output.txt");
// Problem 1
    UniformGenerator ug;
    int size = 10000;
    double random_nums[size];
    double builtin_rand[size];
// 1(a) Generate 10,000 Uniformly distributed numbers on [0,1] by LGM method
    for (int i = 0; i < size; i++){
        random_nums[i] = ug.generator();
    }
//The mean and standard deviation of the random numbers
    double mean = mean_func<double>(random_nums,size);
    double sd = standard_deviation<double>(random_nums, mean,size);
    output << "Problem 1: " << endl;
    output << "The empirical mean = " << mean << endl;
    output << "The empirical standard deviation = " << sd << endl;
//1(b) Generate 10,000 Uniformly distributed numbers by built-in random function
    for (int i = 0; i < size; i++){
        builtin_rand[i] = rand()/(double)RAND_MAX;
    }
    double builtin_mean = mean_func<double>(builtin_rand, size);
    double builtin_sd = standard_deviation<double>(builtin_rand, builtin_mean,size);
    output << "Built-in random function mean = " << builtin_mean << endl;
    output << "Built-in random function standard deviation = " << builtin_sd << endl;

// Problem 2
    int multi_Bern[size];
    ofstream problem_stream;
    problem_stream.open("Problem2_data.csv");
// 2(a) Generate 10,000 random numbers with general discretely distributed random numbers
    for (int i = 0; i < size; i++){
        if (random_nums[i] <= 0.3){
            multi_Bern[i] = -1;
        }
        else if (random_nums[i] <= 0.65){
            multi_Bern[i] = 0;
        }
        else if (random_nums[i] <= 0.85){
            multi_Bern[i] = 1;
        }
        else{
            multi_Bern[i] = 2;
        }
        problem_stream << multi_Bern[i] << endl;
    }
    problem_stream.close(); // output arrary to R script for ploting

// 2(b) The mean and standard deviation of the random numbers
    double multi_Bern_mean = mean_func<int>(multi_Bern, size);
    double multi_Bern_sd = standard_deviation<int>(multi_Bern,multi_Bern_mean, size);
    output << endl << "Problem 2: " << endl;
    output << "The empirical mean = " << multi_Bern_mean << endl;
    output << "The standard deviation = " << multi_Bern_sd << endl;

// Problem 3
    int binomial[1000];
    int count_40larger = 0;
    problem_stream.open("Problem3_data.csv");
// 3(a) Generate 1000 random numbers with Binomial distribution with m = 44, p = 0.64
    for (int i = 0; i < 1000; i++){
        int sum = 0;
        for (int j = 0; j < 44; j++){
            double uniform_temp = ug.generator();
            if (uniform_temp <= 0.64){
                sum += 1;
            }
        }
        binomial[i] = sum;
        problem_stream << sum << endl; // Output Binomial array to a data file and use R to plot
        if (sum >= 40){
            count_40larger++;  // 3(b) Count the number of X >= 40;
        }
    }
    output << endl << "Problem 3: " << endl;
    problem_stream.close(); 
    output << "The empirical probability of X >= 40 is around " << count_40larger/(double)1000 << endl; // 3(b) the probability of X >= 40
// exact probability of X >= 40
    double p = 0.64;
    double probability = 0;
    for (int i = 40; i <= 44; i++){
        probability += combination(44, i) * pow(p,i) * pow(1-p,44-i);
    }
    output << "The exact probability, P(X>=40) = "<< probability << endl;

// Problem 4
    double exponential[size];
    double lambda = 1.5;
    int x_larger1 = 0;
    int x_larger4 = 0;
    problem_stream.open("Problem4_data.csv");
// 4(a) Generate 10,000 Exponentially distributed random numbers with lambda = 1.5
    for (int i = 0; i < size; i++){
        double exp = -lambda * log(random_nums[i]);
        exponential[i] = exp;
        problem_stream << exp << endl;  // Output Exponential array to a data file and use R to plot
        if (exp >= 1){
            x_larger1 ++;   // 4(b) Count the number of X >= 1
            if (exp >= 4){
                x_larger4++;  // 4(b) Count the number of X >= 4
            }
        }
    }
    problem_stream.close();
    double prob_larger_1 = x_larger1 / double(size); // 4(b) The probability of X >= 1
    double prob_larger_4 = x_larger4 / double(size); // 4(b) The probability of X >= 4
    output << endl << "Problem 4: " << endl;
    output << "P(X>=1) = " << prob_larger_1 << endl;
    output << "P(X>=4) = " << prob_larger_4 << endl;
// 4(c) The mean and standard deviation of the random numbers
    double exp_mean = mean_func<double>(exponential,size);
    double exp_sd = standard_deviation<double>(exponential,exp_mean,size);
    output << "The empirical mean of exponential distribution = " << exp_mean << endl;
    output << "The empirical standard deviation = " << exp_sd << endl;

// Problem 5
    size = 5000;
    double uniform_rv[size];
// 5(a) Generate 5,000 Uniformly distributed random numbers on [0,1]   
    for (int i = 0; i < size; i++){
        uniform_rv[i] = ug.generator();
    }
// 5(b) Generate 5,000 Normally distributed numbers by using Box Muller Method
//      By taking the odd position of uniform random variables as U1 and even position as U2
//      Z1 and Z2 will be updated to the result array by turns
    high_resolution_clock::time_point t1 = high_resolution_clock::now(); // Box Muller Method start time
    double box_muller_norm[size];
    for (int i = 0; i < size; i+=2){
        box_muller_norm[i] = sqrt(-2 * log(uniform_rv[i])) * cos(2 * M_PI * uniform_rv[i + 1]);
        box_muller_norm[i+1] = sqrt(-2 * log(uniform_rv[i])) * sin(2 * M_PI * uniform_rv[i + 1]);
    }

    high_resolution_clock::time_point t2 = high_resolution_clock::now(); // Box Muller Method end time
    int duration1 = duration_cast<microseconds>(t2 - t1).count();  // Box Muller Method runtime
    output << endl << "Problem 5: " << endl;
// 5(c) The mean and standard deviation of the random numbers
    double box_muller_mean = mean_func<double>(box_muller_norm,size);
    double box_muller_sd = standard_deviation<double>(box_muller_norm,box_muller_mean,size);
    output << "Box Muller: empirical mean = " << box_muller_mean <<endl;
    output << "Box Muller: empirical standard deviation = " << box_muller_sd << endl;
// 5(d) Generate Normally distributed numbers by using Polar-Marsaglia Method
//      By taking odd position of uniform random variables as U1 and even position as U2
//      Z1 will be the even index of random numbers and Z2 will be the odd index of random numbers
//      Z1 and Z2 will be updated into the result arrary by turns.
    double polar_mars_norm[size];
    int length = 0;
    for (int i = 0; i < size; i+=2){
        double v1 = 2 * uniform_rv[i] - 1;
        double v2 = 2 * uniform_rv[i + 1] - 1;
        double w = v1 * v1 + v2 * v2;
        if (w <= 1){
            polar_mars_norm[length++] = v1 * sqrt(-2 * log(w) / w);
            polar_mars_norm[length++] = v2 * sqrt(-2 * log(w) / w);
        }

    }
    
// 5(e) The mean and standard deviation of the random numbers
    double polar_mars_mean = mean_func<double>(polar_mars_norm,length);
    double polar_mars_sd = standard_deviation<double>(polar_mars_norm, polar_mars_mean,length);
    output << "Polar-Marsaglia: empirical mean = " << polar_mars_mean << endl;
    output << "Polar-Marsaglia: empirical standard deviation =" << polar_mars_sd << endl << endl;

// 5(f) Compare the execution time of Box-Muller Method and Polar-Marsaglia Method 
//      with both generating 5,000 normal random numbers
//      Polar-Marsaglia Method is faster

    t1 = high_resolution_clock::now(); // Polar-Marsaglia start time
    int count_normal = 0;
    double polar_mars_norm2[size]; // An empty arrary of size 5,000
    for (int i = 0; count_normal < 5000; i+=2){
        double v1 = 2 * random_nums[i] - 1;   // use the uniform random numbers with size 10,000 in Problem 1
        double v2 = 2 * random_nums[i+1] - 1;
        double w = v1 * v1 + v2 * v2;
        if (w <= 1){
            polar_mars_norm2[count_normal++] = v1 * sqrt(-2 * log(w) / w);
            polar_mars_norm2[count_normal++] = v2 * sqrt(-2 * log(w) / w);
        }
    }
    t2 = high_resolution_clock::now(); // Polar-Marsaglia end time
    int duration2 = duration_cast<microseconds>(t2 - t1).count(); // Polar-Marsaglia rumtime
    output << "Box Muller runtime: " << duration1 <<  " microseconds" << endl;
    output << "Polar-Marsaglia runtime with 5,000 normal numbers: " << duration2 << " microseconds" << endl;

// With the runtime of uniform random numbers generation included in both method,
// the result may be different, the following codes will test the result.
    t1 = high_resolution_clock::now();
    double box_muller_norm2[size];
    for (int i = 0; i < size; i+=2){
        double u1 = ug.generator();
        double u2 = ug.generator();
        box_muller_norm2[i] = sqrt(-2 * log(u1)) * cos(2 * M_PI * u2);
        box_muller_norm2[i+1] = sqrt(-2 * log(u1)) * sin(2 * M_PI * u2);
    }
    t2 = high_resolution_clock::now();
    int duration3 = duration_cast<microseconds>(t2 - t1).count();
    
    t1 = high_resolution_clock::now();
    double polar_mars_norm3[size];
    count_normal = 0;
    for (int i = 0; count_normal < size; i+=2){
        double u1 = ug.generator();
        double u2 = ug.generator();
        double v1 = 2 * u1- 1;   // use the uniform random numbers with size 10,000 in Problem 1
        double v2 = 2 * u2- 1;
        double w = v1 * v1 + v2 * v2;
        if (w <= 1){
            polar_mars_norm3[count_normal++] = v1 * sqrt(-2 * log(w) / w);
            polar_mars_norm3[count_normal++] = v2 * sqrt(-2 * log(w) / w);
        }
    }
    t2 = high_resolution_clock::now();
    int duration4= duration_cast<microseconds>(t2 - t1).count();

//  With the runtime of uniform random numbers generation included in both method,
//  Box-Muller Method is slightly faster
    output << endl << "With the runtime of uniform random numbers generation included in both method: " << endl;
    output << "Box Muller runtime: " << duration3 << " microseconds" << endl;
    output << "Polar-Marsaglia runtime: " << duration4 << " microseconds" << endl;
    output.close();
    cout << "Please check the result file \"Project1_Output.txt\"" << endl;
    return 0;
}