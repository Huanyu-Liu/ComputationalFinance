//
//  matrix_cal.cpp
//  Project5
//
//  Created by Huanyu Liu on 2/18/19.
//  Copyright © 2019 Huanyu Liu. All rights reserved.
//

#include "matrix_cal.hpp"

//double * matrix_cal::matrix(double ** a, double * b, int k){
//    double * result;
//    result = matrix_multi(matrix_inv(a, k), b, k);
//    return result;
//    
//}

void matrix_cal::matrix(double **a, double *b, double * result, int k){
    matrix_inv(a, k);
    matrix_multi(a, b, result, k);
}

void matrix_cal::addition(double * a, double * b, double * result, int k){
    for (int i = 0; i < k; ++i){
        result[i] = a[i] + b[i];
    }
}

void matrix_cal::matrix_multi(double **a, double *b, double * result, int k){
    
    for (int i = 0; i < k; ++i){
        result[i] = 0;
        for (int j = 0; j < k; ++j){
            result[i] += a[i][j] * b[j];
        }
    }
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

void matrix_cal::matrix_inv(double **a, int N){
    double det = matrix_det(a, N);
    double ** adj = new double * [N];
    for (int i = 0; i < N; ++i){
        adj[i] = new double[N];
    }
    adjoint(a, adj, N);
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            a[i][j] = adj[i][j]/float(det);
        }
    }
    for (int i = 0; i < N; ++i){
        delete adj[i];
    }
    delete [] adj;
    
}

double matrix_cal::matrix_det(double ** a, int N){
    double result = 0;
    //  Base case : if matrix contains single element
    if (N == 1)
        return a[0][0];
    
    double ** temp = new double * [N];
    for (int i = 0; i < N; ++i){
        temp[i] = new double[N];
    }
    int sign = 1;  // To store sign multiplier
    
    // Iterate for each element of first row
    for (int f = 0; f < N; ++f)
    {
        // Getting Cofactor of mat[0][f]
        // temp = matrix_cal::getCofactor(a, 0, f, k);
        getCofactor(a, temp, 0, f, N);
        result += sign * a[0][f] * matrix_det(temp, N - 1);
        
        // terms are to be added with alternate sign
        sign = -sign;
    }
    for (int i = 0; i < N; ++i){
        delete [] temp[i];
    }
    delete [] temp;
    return result;
}

void matrix_cal::getCofactor(double **m, double ** temp, int p, int q, int n){
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

void matrix_cal::adjoint(double ** a, double ** adj, int N){
    if (N == 1)
    {
        adj[0][0] = 1;
        return;
    }
    
    // temp is used to store cofactors of A[][]
    int sign = 1;
    double ** temp = new double * [N];
    for (int i = 0; i < N; ++i){
        temp[i] = new double[N];
    }
    for (int i=0; i<N; ++i)
    {
        for (int j=0; j<N; ++j)
        {
            // Get cofactor of A[i][j]
            // temp = getCofactor(a, i, j, N);
            getCofactor(a, temp, i, j, N);
            
            // sign of adj[j][i] positive if sum of row
            // and column indexes is even.
            sign = ((i+j)%2==0)? 1: -1;
            
            // Interchanging rows and columns to get the
            // transpose of the cofactor matrix
            adj[j][i] = (sign)*(matrix_det(temp, N-1));
        }
    }
    for (int i = 0; i < N; ++i){
        delete temp[i];
    }
    delete [] temp;
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

void matrix_cal::LUPDecompose(double **A, int * P, int N, double Tol) {
    
    int i, j, k, imax;
    double maxA, *ptr, absA;
    
    for (i = 0; i <= N; i++)
        P[i] = i; //Unit permutation matrix, P[N] initialized with N
    
    for (i = 0; i < N; i++) {
        maxA = 0.0;
        imax = i;
        
        for (k = i; k < N; k++)
            if ((absA = std::abs(A[k][i])) > maxA) {
                maxA = absA;
                imax = k;
            }
        
        if (maxA < Tol) return; //failure, matrix is degenerate
        
        if (imax != i) {
            //pivoting P
            j = P[i];
            P[i] = P[imax];
            P[imax] = j;
            
            //pivoting rows of A
            ptr = A[i];
            A[i] = A[imax];
            A[imax] = ptr;
            
            //counting pivots starting from N (for determinant)
            P[N]++;
        }
        
        for (j = i + 1; j < N; j++) {
            A[j][i] /= A[i][i];
            
            for (k = i + 1; k < N; k++)
                A[j][k] -= A[j][i] * A[i][k];
        }
    }
    //decomposition done
}

void matrix_cal::LUPDecompose(double **A, double ** updated_A,int * P, int N, double Tol) {
    
    int i, j, k, imax;
    double maxA, *ptr, absA;
    
    for (i = 0; i <= N; i++)
        P[i] = i; //Unit permutation matrix, P[N] initialized with N
    
    for (i = 0; i < N; i++) {
        maxA = 0.0;
        imax = i;
        
        for (k = i; k < N; k++)
            if ((absA = std::abs(A[k][i])) > maxA) {
                maxA = absA;
                imax = k;
            }
        
        if (maxA < Tol) return; //failure, matrix is degenerate
        
        if (imax != i) {
            //pivoting P
            j = P[i];
            P[i] = P[imax];
            P[imax] = j;
            
            //pivoting rows of A
            ptr = A[i];
            updated_A[i] = A[imax];
            updated_A[imax] = ptr;
            
            //counting pivots starting from N (for determinant)
            P[N]++;
        }
        
        for (j = i + 1; j < N; j++) {
            updated_A[j][i] = A[j][i] / A[i][i];
            
            for (k = i + 1; k < N; k++)
                updated_A[j][k] = A[j][k] - A[j][i] * A[i][k];
        }
    }
    //decomposition done
}
/* INPUT: A,P filled in LUPDecompose; b - rhs vector; N - dimension
 * OUTPUT: x - solution vector of A*x=b
 */
void matrix_cal::LUPSolve(double **A, int *P, double *b, double * result, int N) {
    for (int i = 0; i < N; i++) {
        result[i] = b[P[i]];
        
        for (int k = 0; k < i; k++)
            result[i] -= A[i][k] * result[k];
    }
    
    for (int i = N - 1; i >= 0; i--) {
        for (int k = i + 1; k < N; k++)
            result[i] -= A[i][k] * result[k];
        
        result[i] /= A[i][i];
    }
}

void matrix_cal::linear_equation(double ** A, double * b, double * result, int N){
    int * p = new int[N];
    double ** updated_A = new double * [N];
    for (int i = 0; i < N; ++i){
        updated_A[i] = new double[N];
        for (int j = 0; j < N; ++j){
            updated_A[i][j] = A[i][j];
        }
    }
    LUPDecompose(updated_A, p, N, SMALL);
    LUPSolve(updated_A, p, b, result, N);
    delete [] p;
    for (int i = 0; i < N; ++i){
        delete [] updated_A[i];
    }
    delete [] updated_A;
}
