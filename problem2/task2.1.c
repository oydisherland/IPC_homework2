#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


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


float** matT(float** matrix, int dimention){
    clock_t t1,t2;
    int i, j;
    float** matrixTransposed; 
    matrixTransposed = (float**)calloc(dimention, sizeof(float*));
    for (i = 0; i < dimention; i++) {
        matrixTransposed[i] = (float*)calloc(dimention, sizeof(float));
    }

//SEQUENTIAL SECTION - TRANSPOSE MATRIX
    t1 = clock();
    for(i = 0; i < dimention; i++){
        for(j = 0; j < dimention; j++){
            matrixTransposed[i][j] = matrix[j][i];
        }
    }
    t2 = clock();
    printf( "Calculation time (transpose) serial = %12.4g sec\n", (t2-t1)/1000000.0 );
    return matrixTransposed;
}

float** matBlockT(float** matrix, int dimention, int blockSize){

    clock_t t1, t2;
    int i, j, i_block, j_block;
    int numOfBlocks = dimention/blockSize;

    //INITILAZE
    float** matrixTransposed;
    matrixTransposed = (float**)calloc(dimention, sizeof(float*));
    for (i = 0; i < dimention; i++) {
        matrixTransposed[i] = (float*)calloc(dimention, sizeof(float));
    }
    float block[blockSize][blockSize];

//SEQUALTIAL SECTION - BLOCK TRANSFORMATION 
    float** matrixBlockTrans;
    t1 = clock();
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
    t2 = clock();
    printf( "Calculation time (transpose) serial = %12.4g sec\n", (t2-t1)/1000000.0 );
    return matrixTransposed;
}


int main(){
    srand(time(NULL));
    int dimention = 5000;
    int blockSize = 50;

    float** A = matrixGenerater(dimention);

// UNCOMMENT THIS LINE TO USE THE matT() FUNCTION
    float** At = matT(A,dimention);

// UNCOMMENT THIS LINE TO USE THE matBlockT() FUNCTION
    //float** At = matBlockT(A,dimention, blockSize);
    
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