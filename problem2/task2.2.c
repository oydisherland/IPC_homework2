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
            matrix[i][j] = rand()%10;
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


float** matTpar(float** matrix, int dimention){
    int i, j;
    double wt1,wt2;
    float** matrixTransposed; 
    matrixTransposed = (float**)calloc(dimention, sizeof(float*));
    for (i = 0; i < dimention; i++) {
        matrixTransposed[i] = (float*)calloc(dimention, sizeof(float));
    }

//PARALLEL SECTION - TRANSPOSE MATRIX
    wt1 = omp_get_wtime();
    #pragma omp parallel 
    {
    #pragma omp for collapse(2)
    for(i = 0; i < dimention; i++){
        for(j = 0; j < dimention; j++){
            matrixTransposed[i][j] = matrix[j][i];
        }
    }
    }
    wt2=omp_get_wtime();
    printf( "Calculation time matT() parallel = %12.4g sec\n", wt2-wt1 );

    return matrixTransposed;
}

float** matBlockTpar(float** matrix, int dimention, int blockSize){

    double wt1,wt2;
    int i, j, i_block, j_block;
    int numOfBlocks = dimention/blockSize;

    //INITILAZE
    float** matrixTransposed;
    matrixTransposed = (float**)calloc(dimention, sizeof(float*));
    for (i = 0; i < dimention; i++) {
        matrixTransposed[i] = (float*)calloc(dimention, sizeof(float));
    }
    float block[blockSize][blockSize];

//PARALLEL SECTION - BLOCK TRANSFORMATION 
    float** matrixBlockTrans;
    wt1 = omp_get_wtime();
    #pragma omp parallel 
    {
    #pragma omp for collapse(2) private(i, j, block)
    for(i_block = 0; i_block < numOfBlocks; i_block++){
        for(j_block = 0; j_block < numOfBlocks; j_block++){

            for(i = 0; i < blockSize; i++){
                for(j = 0; j < blockSize; j++){
                    block[j][i] = matrix[i + (i_block * blockSize)][j + (j_block * blockSize)];
                }
            }

            for(i = 0; i < blockSize; i++){
                for(j = 0; j < blockSize; j++){
                    matrixTransposed[i + (j_block * blockSize)][j + (i_block * blockSize)] = block[i][j];
                }
            }
        }
    }
    }
    wt2=omp_get_wtime();
    printf( "wall clock time (omp_get_wtime) = %12.4g sec\n", wt2-wt1 );
    return matrixTransposed;
}


int main(){
    srand(time(NULL));
    int dimention = 50;
    int blockSize = 5;
    printf("dimention= %d, blocksize= %d   ", dimention, blockSize);
    float** A = matrixGenerater(dimention);

// UNCOMMENT THIS LINE TO USE THE matT() FUNCTION
    float** At = matTpar(A,dimention);

// UNCOMMENT THIS LINE TO USE THE matBlockT() FUNCTION
    //float** At = matBlockTpar(A,dimention, blockSize);
   

 // UNCOMMENT THIS SECTION TO PRINT
/*
    printMatrix(dimention, A);
    printf("\n ________\n");
    printMatrix(dimention, At);
    printf("\n ________\n");
*/

    freeMatrix(A, dimention);
    freeMatrix(At, dimention);

}