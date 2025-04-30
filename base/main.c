//Author: Jayson Boubin -- Fall 2022
#include "matmul.h"

int* mat1 = NULL;
int* mat2 = NULL;
int* matRes = NULL;
int* matSol = NULL;


// M x N = mat1 
// N x K = mat2
// M x K = matSol/matRes

// nThreads == 1
void multiply() {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < K; j++) {
			matRes[i*K + j] = 0;
			for (int k = 0; k < N; k++) {
				matRes[i*K + j] += mat1[i*N + k] * mat2[k*K + j];
	
			}	
		}
	}
}


void* task(void* args) {
	int* arg = (int*) args;
	int start = arg[0];
	int end = arg[1];

	for (int i = start; i < end; i++) {
		for (int j = 0; j < K; j++) {
			matRes[i*K + j] = 0;
			for (int k = 0; k < N; k++) {
				matRes[i*K + j] += mat1[i*N + k] * mat2[k*K + j];
	
			}	
		}
	}

	free(args);
}


// nThreads > 1 && nThread <= min(M, N, K)
void multiplyWithThreads(int nThreads){

	if (nThreads > M || nThreads > N || nThreads > K) {
		printf("nThreads must be less than any size of matricies!\n");
		exit(1);
	}
    
	// create p_threads and divide total task into rows of the final matrix
	pthread_t threads[nThreads];
	int rows_per_thread = M / nThreads;
	int extra = M - rows_per_thread * nThreads;

	int start = 0;
	int end = start + rows_per_thread;

	for (int i = 0; i < nThreads; i++) {
		int* args = malloc(sizeof(int)*2);
		args[0] = start;
		if (extra-- > 0) end++;
		args[1] = end;
		//if (args[1] > M) args[1] = M;
		if (i == nThreads-1) args[1] = M;	
		pthread_create(&threads[i], NULL, task, (void*)args);
		start = end;
		end += rows_per_thread;
	}

	for (int i = 0; i < nThreads; i++) {
		pthread_join(threads[i], NULL);
	}

	// printMats();
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
