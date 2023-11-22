#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>



void printMatrix(int size, float** m) {
    int i, j;
    int row = size; int col = size;
    for (i = 0; i < row; i++) {
        //printf("%d-line: ", i + 1);
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
    for ( i = 0; i < dimention; i++) {
        matrix[i] = (float*)calloc(dimention, sizeof(float));
    }
    for ( i = 0; i < dimention; i++){
        for ( j = 0; j < dimention; j++){ 
            matrix[i][j] = rand();
//UNCOMMENT THIS SECTION IN ORDER TO GET A SPARCE MATRIX
/*
            if((j+i)%2 == 1){
                matrix[i][j] = 0;
            }
*/
        }
    }
    return matrix;
}

void freeMatrix(float** matrix, int dimention){
    int i;
    for ( i = 0; i < dimention; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

float** matMul(float** A, float** B,  int dimention){
    int i, j, k;
    clock_t t1, t2;

    //ALLOCATING THE MATRIX C
    float** C; 
    C = (float**)calloc(dimention, sizeof(float*));
    for ( i = 0; i < dimention; i++) {
        C[i] = (float*)calloc(dimention, sizeof(float));
    }

    //INITIALIZE THE MATRIX C
    for ( i = 0; i < dimention; i++){
        for ( j = 0; j < dimention; j++){ 
            C[i][j] = 0;
        }
    }

    //CALCULATION IN SERIAL
    t1 = clock();
    for ( i = 0; i < dimention; i++){
        for ( j = 0; j < dimention; j++){
            for ( k = 0; k < dimention; k++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    t2 = clock();
    printf("\nTime used: %12.4g \n", (t2-t1)/1000000.0);
    return C;
}


int main(){
    srand(time(NULL)); 
    int dimention = 500;

    float** A = matrixGenerater(dimention);
    float** B = matrixGenerater(dimention);
    float** C = matMul(A, B, dimention);

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