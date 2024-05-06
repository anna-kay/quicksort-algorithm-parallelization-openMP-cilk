## Overview

This repo contains two versions of parallelization of the Quicksort algorithm:
1. Using Cilk
2. Using OpenMp


**Cilk version:**

The parallelization of the recursive implementation of quicksort is done using the branching structure that is implemented through the `cilk_spawn` command, in the recursive function `qsort_parallel`

The definition of the threads is done according to the choice of the use inside `main`, using the function `__cilkrts_set_param("nworkers", string_num_of_workers)`

cilk/cilk.h & cilk/cilk_api.h were inclued


**OpenMP version:**

The parallelization is done using:
- the structure `#pragma omp parallel{#pragma omp single{}}` inside of the `main` function and
- the structure `#pragma omp task{}` in `qsort_parallel` to make the branches of each recursion run in parallel.

The definition of the number of the threads is done in `main`, using the function `omp_set_num_threads(num_of_threads)`.

omp.h was included
