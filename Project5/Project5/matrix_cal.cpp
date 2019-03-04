//
//  matrix_cal.cpp
//  Project5
//
//  Created by Huanyu Liu on 2/18/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include "matrix_cal.hpp"

double * matrix_cal::matrix(double ** a, double * b, int k){
    double * result;
    result = matrix_multi(matrix_inv(a, k), b, k);
    return result;
    
}

double * matrix_cal::matrix_multi(double ** a, double * b, int k){
    double * result = new double[k];
    for (int i = 0; i < k; ++i){
        for (int j = 0; j < k; ++j){
            result[i] += a[i][j] * b[j];
        }
    }
    return result;
}
double ** matrix_cal::matrix_inv(double ** a, int N){
    double det = matrix_det(a, N);
    // Find adjoint
    double ** adj = adjoint(a,N);
    
    double ** inverse = new double*[N];
    for (int i = 0; i < N; ++i){
        inverse[i] = new double[N];
    }
    
    // Find Inverse using formula "inverse(A) = adj(A)/det(A)"
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            inverse[i][j] = adj[i][j]/float(det);
    
    return inverse;
}
double matrix_cal::matrix_det(double ** a, int k){
    double result = 0;
    //  Base case : if matrix contains single element
    if (k == 1)
        return a[0][0];
    
    double ** temp;
    int sign = 1;  // To store sign multiplier
    
    // Iterate for each element of first row
    for (int f = 0; f < k; ++f)
    {
        // Getting Cofactor of mat[0][f]
        temp = matrix_cal::getCofactor(a, 0, f, k);
        result += sign * a[0][f] * matrix_cal::matrix_det(temp, k - 1);
        
        // terms are to be added with alternate sign
        sign = -sign;
    }
    
    return result;
}


double ** matrix_cal::getCofactor(double ** m, int p, int q, int n)
{
    double ** temp = new double*[n];
    for (int i = 0; i < n; ++i){
        temp[i] = new double[n];
    }
    int i = 0, j = 0;
    
    // Looping for each element of the matrix
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            //  Copying into temporary matrix only those element
            //  which are not in given row and column
            if (row != p && col != q)
            {
                temp[i][j++] = m[row][col];
                
                // Row is filled, so increase row index and
                // reset col index
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
    return temp;
}


double ** matrix_cal::adjoint(double ** a, int N)
{
    double ** adj = new double*[N];
    for (int i = 0; i < N; ++i){
        adj[i] = new double[N];
    }
    
    if (N == 1)
    {
        adj[0][0] = 1;
        return adj;
    }
    
    // temp is used to store cofactors of A[][]
    int sign = 1;
    double ** temp;
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
        {
            // Get cofactor of A[i][j]
            temp = getCofactor(a, i, j, N);
            
            // sign of adj[j][i] positive if sum of row
            // and column indexes is even.
            sign = ((i+j)%2==0)? 1: -1;
            
            // Interchanging rows and columns to get the
            // transpose of the cofactor matrix
            adj[j][i] = (sign)*(matrix_det(temp, N-1));
        }
    }
    return adj;
}

