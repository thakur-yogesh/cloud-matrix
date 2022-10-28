#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
//#include <pthread.h>
#include <omp.h>
#include <math.h>
#define MAX_VAL 500
#define MIN_VAL 50
typedef double TYPE;
TYPE** randomSquareMatrix(int dimension){
	/*
		Generate 2 dimensional random TYPE matrix.
	*/

	TYPE** matrix = malloc(dimension * sizeof(TYPE*));

	for(int i=0; i<dimension; i++){
		matrix[i] = malloc(dimension * sizeof(TYPE));
	}

	//Random seed
	srand(time(0)+clock()+rand());

	#pragma omp parallel for
	for(int i=0; i<dimension; i++){
		for(int j=0; j<dimension; j++){
			matrix[i][j] = rand() % MAX_VAL + MIN_VAL;
		}
	}

	return matrix;
}

TYPE** zeroSquareMatrix(int dimension){
	/*
		Generate 2 dimensional zero TYPE matrix.
	*/

	TYPE** matrix = malloc(dimension * sizeof(TYPE*));

	for(int i=0; i<dimension; i++){
		matrix[i] = malloc(dimension * sizeof(TYPE));
	}

	//Random seed
	srand(time(0)+clock()+rand());
	for(int i=0; i<dimension; i++){
		for(int j=0; j<dimension; j++){
			matrix[i][j] = 0;
		}
	}

	return matrix;
}
void parallelMultiply(TYPE** matrixA, TYPE** matrixB, TYPE** matrixC, int dimension){
	/*
		Parallel multiply given input matrices and return resultant matrix
	*/

	//struct timeval t0, t1;
	//gettimeofday(&t0, 0);

	/* Head */
	#pragma omp parallel for
	for(int i=0; i<dimension; i++){
		for(int j=0; j<dimension; j++){
			for(int k=0; k<dimension; k++){
				matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
			}
		}
	}
	/* Tail */

	//gettimeofday(&t1, 0);
	//double elapsed = (t1.tv_sec-t0.tv_sec) * 1.0f + (t1.tv_usec - t0.tv_usec) / 1000000.0f;

	//return elapsed;
}
void displaySquareMatrix(TYPE** matrix, int dimension){
	for(int i=0; i<dimension; i++){
		for(int j=0; j<dimension; j++){
			printf("%f\t", matrix[i][j]);
		}
		printf("\n");
	}
}
void optimizedParallelMultiplyTest(int dimension){
TYPE** matrixA = randomSquareMatrix(dimension);
TYPE** matrixB = randomSquareMatrix(dimension);
TYPE** matrixResult = zeroSquareMatrix(dimension);
parallelMultiply(matrixA,matrixB,matrixResult,dimension);
printf("matrix A generated at random\n");
displaySquareMatrix(matrixA,dimension);
printf("matrix B generated at random\n");
displaySquareMatrix(matrixB,dimension);
printf("resultant matrix is\n");
displaySquareMatrix(matrixResult,dimension);



}
int main(int argc, char* argv[]){
int dim;
  clock_t t;
    t = clock();
printf("we will be multiplying two square matrix of order above 1000\n");
printf("enter matrix order above 1000\n");
scanf("%d",&dim);
optimizedParallelMultiplyTest(dim);
	
	 t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds

   printf("time taken  = %f",time_taken);




return 0;
}
