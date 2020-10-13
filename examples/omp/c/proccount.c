/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   %%%%
   %%%% This program file is part of the book and course
   %%%% "Parallel Computing"
   %%%% by Victor Eijkhout, copyright 2013-2020
   %%%%
   %%%% proccount.c : counting procs and threads
   %%%%
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

#include <stdlib.h>
#include <stdio.h>

#include "omp.h"

int main(int argc,char **argv) {

  int nprocs,nthreads;
#pragma omp parallel
#pragma omp master
  nthreads = omp_get_num_threads();
  nprocs   = omp_get_num_procs();
  printf("Count %d cores and %d threads\n",nprocs,nthreads);

  return 0;
}
