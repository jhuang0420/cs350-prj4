//Author: Jayson Boubin -- Fall 2022
#include "matmul.h"

void printMats(){
    for(int i = 0; i<M; i++){
        for(int j = 0; j<N; j++){
            printf("%d ", mat1[i*N+j]);
        }
        printf("\n");
    }
    printf("\n\n");
    for(int i = 0; i<N; i++){
        for(int j = 0; j<K; j++){
            printf("%d ", mat2[i*K+j]);
        }
        printf("\n");
    }
    printf("\n\n");
    for(int i = 0; i<M; i++){
        for(int j = 0; j<K; j++){
            printf("%d ", matRes[i*K+j]);
        }
        printf("\n");
    }
}

int* initialize(int rows, int cols, char* fname){

    int* mat = malloc(rows *cols *sizeof(int)); 
    
    FILE* stream = fopen(fname, "r");
    char line[4096];
   
    int i = 0;
    while(fgets(line, 4096, stream)){
        char* tmp = strdup(line);
        char* pt = strtok(line,",");
        while(pt != NULL){
            int a = atoi(pt);
            mat[i] = a;
            ++i;
            pt = strtok(NULL,",");
        }
    }
    return mat;
}

bool compare() {
    for(int i = 0; i<M; i++){
        for(int j = 0; j<K; j++){
            if(matRes[i*K + j] != matSol[i*K+j])
                return false;
        }
    }

    return true;
}

//Returns the total time 
double getTotalTime(struct timeval start, struct timeval end){
    double time;

    time = ((end.tv_sec*1000000 + end.tv_usec) - 
           (start.tv_sec * 1000000 + start.tv_usec))/1000000.0;

    return time;
}
