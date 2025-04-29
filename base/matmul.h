//Author: Jayson Boubin -- Fall 2022
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/time.h>
#include <pthread.h>

//#define SMALL
//#define MED
#define BIG

#ifdef SMALL
    #define M 4
    #define N 4
    #define K 4

    #define MAT_A "./matrices/a_small.csv"
    #define MAT_B "./matrices/b_small.csv"
    #define MAT_C "./matrices/c_small.csv"
#endif 

#ifdef MED
    #define M 10
    #define N 12
    #define K 15

    #define MAT_A "./matrices/a_med.csv"
    #define MAT_B "./matrices/b_med.csv"
    #define MAT_C "./matrices/c_med.csv"
#endif 

#ifdef BIG
    #define M 1200
    #define N 1000
    #define K 500

    #define MAT_A "./matrices/a_big.csv"
    #define MAT_B "./matrices/b_big.csv"
    #define MAT_C "./matrices/c_big.csv"
#endif 

extern int* mat1;   //Matrix of size MxN
extern int* mat2;   //Matrix of size NxK
extern int* matRes; //Matrix of size MxK
extern int* matSol; //Matrix of size MxK

typedef struct {
    int tid;
    int totalThreads;
} threadargs;

void printMats();

int* initialize(int rows, int cols, char* fname);

bool compare();

void multiply();

void multiplyWithThreads(int nThreads);

double getTotalTime(struct timeval start, struct timeval end);
