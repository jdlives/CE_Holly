#include <stdio.h>
#include <math.h>
#include<stdbool.h>
#include<string.h>

void Cholesky(float A[10][10], int n, float L[10][10]) {
    for (int i = 0; i < n; i++){
        for (int j = 0; j < (i+1); j++) {
            double s = 0;
            for (int k = 0; k < j; k++){
                s += L[i * n + k] * L[j * n + k];
            }
            L[i * n + j] = (i == j) ?
                           sqrt(A[i * n + i] - s) :
                           (1.0 / L[j * n + j] * (A[i * n + j] - s));
        }
    }
}