/**********************************************************************
 *
 * qsort-parallel.c -- Parallel implementation of QuickSort
 *
 * Nikos Pitsianis <nikos.pitsianis@eng.auth.gr>
 * Dimitris Floros <fcdimitr@auth.gr>
 * Time-stamp: <2018-10-10>
 *
 **********************************************************************/

#include <stdio.h>
#include <cilk/cilk.h>
//#include <cilk/cilk_api.h>

/* swap -- swap elements k and l of vector v */
void swap(int *v, int k, int l) {
  int temp = v[k];
  v[k] = v[l];
  v[l] = temp;
}

/* partition -- in-place update of elements */
int partition(int *v, int n) {
  
  /*Check for thread's id*/
  //int num;
  //num=__cilkrts_get_worker_number();
  //printf("\nThread's id is = %d\n", num);
    
  int pivot = v[n-1];
  //printf("\nThe pivot is: %d\n", pivot);
  int i = 0;
  
  for (int j = 0; j < n - 1; j++) 
    if (v[j] < pivot) 
      swap(v,i++,j);

  swap(v, i, n - 1);
  return (i);
}

/* qsort_par -- Entry point for QuickSort */
void qsort_par(int *v, int n) {

  if (n > 1) {
	
	int p = partition(v, n);
	
    cilk_spawn qsort_par(v,p);

    qsort_par(&v[p+1],n-p-1);	
	
  }
  
}


