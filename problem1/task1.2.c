#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#ifdef _OPENMP
#include <omp.h>
#endif


void printMatrix(int size, float** m) {
    int i, j;
    int row = size; int col = size;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%f ", m[i][j]);
        }
        printf("\n");
    }
}

float** matrixGenerater(int dimention){
    int i, j;
    float** matrix; 
    matrix = (float**)calloc(dimention, sizeof(float*));
    for (i = 0; i < dimention; i++) {
        matrix[i] = (float*)calloc(dimention, sizeof(float));
    }
    for (i = 0; i < dimention; i++){
        for (j = 0; j < dimention; j++){ 
            matrix[i][j] = rand();
        }
    }
    return matrix;
}

void freeMatrix(float** matrix, int dimention){
    int i;
    for (i = 0; i < dimention; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

float** matMulpar(float** A, float** B,  int dimention){
    int i, j, k;
    double wt1,wt2;

    //ALLOCATING THE MATRIX C
    float** C; 
    C = (float**)calloc(dimention, sizeof(float*));
    for (i = 0; i < dimention; i++) {
        C[i] = (float*)calloc(dimention, sizeof(float));
    }

    //INITIALIZE THE MATRIX C
    for (i = 0; i < dimention; i++){
        for (j = 0; j < dimention; j++){ 
            C[i][j] = 0;
        }
    }

    //CALCULATION IN PARALLEL
    float sum = 0;
    wt1=omp_get_wtime();
    #pragma omp parallel 
    {
    #pragma omp for collapse(2) private(k,sum)
    for (i = 0; i < dimention; i++){
        for (j = 0; j < dimention; j++){
            for (k = 0; k < dimention; k++){
                 sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }   
    }
    }
    wt2=omp_get_wtime();
    printf( "wall clock time (omp_get_wtime) = %12.4g sec\n", wt2-wt1 );
    return C;
}


int main(){
    srand(time(NULL));
    int dimention = 50;
    printf("dimention: %d \n", dimention);
    float** A = matrixGenerater(dimention);
    float** B = matrixGenerater(dimention);
    float** C = matMulpar(A, B, dimention);

    freeMatrix(A, dimention);
    freeMatrix(B, dimention);
    freeMatrix(C, dimention);
   
// UNCOMMENT THIS SECTION TO PRINT
/*
    printMatrix(dimention, A);
    printf("\n ________\n");
    printMatrix(dimention, B);
    printf("\n ________\n");
    printMatrix(dimention, C);
    printf("\n ________\n");
*/
}