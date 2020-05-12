/**********************************************************************
 *
 * qsort.c -- Parallel implementation of QuickSort
 *
 * Nikos Pitsianis <nikos.pitsianis@eng.auth.gr>
 * Dimitris Floros <fcdimitr@auth.gr>
 * Time-stamp: <2018-10-10>
 *
 **********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "qsort-parallel.h"
#include <assert.h>
#include <omp.h>

/* local function declarations */
int  test( int *a, int n);
void init( int *a, int n);
void print(int *a, int n);

/* --- Entry POINT --- */
int main(int argc, char **argv) {

  /* parse input */
  /*if (argc != 2) {
    printf("Usage: %s q\n  where n=2^q is problem size (power of two)\n", 
	   argv[0]);
    exit(1);
  }*/
  
  /* variables to hold execution time */
  struct timeval startwtime, endwtime;
  double par_time;
  
  /* variables defined by the user*/
  int q,p;
  
  printf("2^q will be the number of elements (integers), 12<=q<=24\n");
  printf("Enter q: ");
  scanf("%d", &q);
  printf("2^p will be the number of threads, 0<=p<=8\n");
  printf("Enter p: ");
  scanf("%d", &p );
 
  /* initiate number of threads*/
  int num_of_threads=1<<p;
  
  /* initiate vector of random integers */
  int n  = 1<<q;
  int *a = (int *) malloc(n * sizeof(int));
  
  /* initialize vector */
  init(a, n);

  /* print vector */
  /* print(a, n); */
  
  printf("\nThe number of threads requested by the user is: %d\n",num_of_threads);
  
  /* call omp to pass the number of threads (max)*/
  omp_set_num_threads(num_of_threads);
  
  /* sort elements in original order */
  gettimeofday (&startwtime, NULL);
  	
  #pragma omp parallel 
  {	
	#pragma omp single
	{
		int number=omp_get_num_threads();
		printf("The number of threads used the in parallel region is: %d\n\n",number);
		qsort_par(a, n);
	}
		
  }
  
  gettimeofday (&endwtime, NULL);

  /* get time in seconds */
  par_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
                      + endwtime.tv_sec - startwtime.tv_sec);

  /* validate result */
  int pass = test(a, n);
  printf(" TEST %s\n",(pass) ? "PASSed" : "FAILed");
  assert( pass != 0 );
  
  /* print sorted vector */
  /* print(a, n); */
  
  /* print execution time */
  printf("\nParallel wall clock time: %f sec\n", par_time);

  /* exit */
  return 0;
  
}

/** -------------- SUB-PROCEDURES  ----------------- **/ 

/** procedure test() : verify sort results **/
int test(int *a, int n) {

  // TODO: implement
  int i;
  
  for(i=0 ; i<n-1 ;i++){
	  assert(a[i]<=a[i+1]);
  }
  
  int pass = 1;
  return pass;
  
}

/** procedure init() : initialize array "a" with data **/
void init(int *a, int n) {
  int i;
  for (i = 0; i < n; i++) {
    a[i] = rand() % n; // (N - i);
  }
}

/** procedure  print() : print array elements **/
void print(int *a, int n) {
  int i;
  for (i = 0; i < n; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}
