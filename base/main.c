//Author: Jayson Boubin -- Fall 2022
#include "matmul.h"

int* mat1 = NULL;
int* mat2 = NULL;
int* matRes = NULL;
int* matSol = NULL;

void multiply() {
    //TODO
}

void multiplyWithThreads(int nThreads){
    //TODO
    printMats();
}

//--- DO NOT MODIFY BELOW HERE ---
int main(int argc, char* argv[])
{
    
    struct timeval start, end;
    double mult_time;

    if(argc != 2) {
        printf("Please provide 1 argument: #threads (int)\n");
        exit(-1);
    }

    int nthreads = atoi(argv[1]);
    
    if(nthreads <= 0){
        printf("Please enter a correct value for #threads\n");
        exit(-1);
    }
    printf("--- Reading in Matrices ---\n");

    mat1 = initialize(M, N, MAT_A);
    mat2 = initialize(N, K, MAT_B);
    matSol = initialize(M, K, MAT_C);
    matRes = malloc(M * K * sizeof(int)); 

    printf("--- Matrices Successfully Read, Multiplying Now ---\n");

    gettimeofday(&start, NULL);
    if(nthreads > 1){
        printf("--- Multiplying with %d threads ---\n", nthreads);
        multiplyWithThreads(nthreads);
    } else {
        printf("--- Multiplying with a single thread ---\n");
        multiply();
    }
    
    gettimeofday(&end, NULL); 
    mult_time = getTotalTime(start, end);

    if(compare()){
        printf("Correct! Your matrices multiplied properly\n");
    } else {
        printf("Incorrect! Your matrices did not multiply properly. Check your solution and try again.\n");
    }
    
    printf("This operation took %f seconds\n", mult_time);

    //Don't forget to free allocated heap memory!
    
    free(mat1);
    free(mat2);
    free(matRes);
    free(matSol);
    
    return 0;
}
