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
#include "qsort-sequential.h"
#include <assert.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>

/* local function declarations */
int  test( int *a, int n);
void init( int *a, int n);
void print(int *a, int n);
int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

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
  double qsort_time;
  double seq_time;
  double par_time;
  
  /* variable to check sorting*/
  int pass; 
  
  /* variables defined by the user*/
  int q,p;
  char string_num_of_workers[10];
  int num_of_workers;
  
  /* user enters parameters*/
  printf("2^q will be the number of elements (integers), 12<=q<=24\n");
  printf("Enter q: ");
  scanf("%d", &q);
  printf("2^p will be the number of threads, 0<=p<=8\n");
  printf("Enter p: ");
  scanf("%d", &p );
  
  /* initiate vector of random integers */
  int n  = 1<<q;
  int *a = (int *) malloc(n * sizeof(int));
  
  
  /*------------------------------INBUILT QSORT()------------------------------------------------------*/
 
  printf("\n\t\tINBUILT QSORT() EXECUTION...\n");
  
  /* initialize vector */
  init(a, n);

  /* print vector */
  /* print(a, n); */
  
  /* sort elements in original order */
  gettimeofday (&startwtime, NULL);
  qsort(a, n, sizeof(int), cmpfunc);
  gettimeofday (&endwtime, NULL);
  
  /* get time in seconds */
  qsort_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
                      + endwtime.tv_sec - startwtime.tv_sec);

  /* validate result */
  pass = test(a, n);
  printf(" TEST %s\n",(pass) ? "PASSed" : "FAILed");
  assert( pass != 0 );
  
  /* print sorted vector */
  /* print(a, n); */
  
  /* print execution time */
  printf("Inbuilt qsort() wall clock time: %f sec\n", qsort_time);
  
  /*------------------------------SEQUENTIAL RECURSIVE EXECUTION--------------------------------------*/ 
  
  printf("\n\t\tSEQUENTIAL RECURSIVE EXECUTION...\n");
  
  /* initialize vector */
  init(a, n);

  /* print vector */
  /* print(a, n); */
  
  /* sort elements in original order */
  gettimeofday (&startwtime, NULL);
  qsort_seq(a, n);
  gettimeofday (&endwtime, NULL);
  
  
  /* get time in seconds */
  
  seq_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
                      + endwtime.tv_sec - startwtime.tv_sec);

  /* validate result */
  pass = test(a, n);
  printf(" TEST %s\n",(pass) ? "PASSed" : "FAILed");
  assert( pass != 0 );
  
    /* print sorted vector */
  /* print(a, n); */
  
  /* print execution time */
  printf("Sequential wall clock time: %f sec\n", seq_time);
  
  /*---------------------------------PARALLEL RECURSIVE EXECUTION------------------------------------*/
  
  printf("\n\t\tPARALLEL RECURSIVE EXECUTION...\n");
  
  /* initiate number of threads*/
  int num_of_threads=1<<p;

  printf("\nThe number of threads requested by the user is: %d\n",num_of_threads);

  snprintf (string_num_of_workers, 10, "%d", num_of_threads); 
  __cilkrts_set_param("nworkers", string_num_of_workers);

  num_of_workers = __cilkrts_get_nworkers();
  
  //!!!!!!!!!!!!!!!De dexetai p>6, to kanei p=2 (sto diko mou pc toulaxiston...)
  printf("The number of threads(workers) used: %d\n\n",num_of_workers);	
  
  /* initialize vector */
  init(a, n);

  /* print vector */
  /* print(a, n); */
  
  /* sort elements in original order */
  gettimeofday (&startwtime, NULL);
  qsort_par(a, n);
  gettimeofday (&endwtime, NULL);

  /* get time in seconds */
  par_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
                      + endwtime.tv_sec - startwtime.tv_sec);

  /* validate result */
  pass = test(a, n);
  printf(" TEST %s\n",(pass) ? "PASSed" : "FAILed");
  assert( pass != 0 );
  
   /* print sorted vector */
   /*print(a, n);*/
  
  /* print execution time */
  printf("Parallel wall clock time: %f sec\n", par_time);
  
  /******************************************************************************************************/
  
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
