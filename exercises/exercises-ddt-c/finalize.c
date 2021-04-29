/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   %%%%
   %%%% This program file is part of the book and course
   %%%% "Parallel Computing"
   %%%% by Victor Eijkhout, copyright 2013-2020
   %%%%
   %%%% finalize.c : code with a parallelism bug
   %%%%
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"

void loop_for_awhile(MPI_Comm comm,double *return_random) {
  int mytid,ntids;

  MPI_Comm_size(comm,&ntids);
  MPI_Comm_rank(comm,&mytid);

  /*
   * This loop as given will terminate correctly
   */
  for (int it=0; ; it++) {
    double randomnumber = ntids * ( rand() / (double)RAND_MAX );
    /*
     * Bonus exercise:
     * -- uncomment the next line. 
     *    Can you figure out a way to not get a mess on your screen?
     */
    //printf("[%d] iteration %d, random %e\n",mytid,it,randomnumber);
    if (randomnumber>mytid && randomnumber<mytid+1./(ntids+1)) {
      *return_random = randomnumber;
      return;
    }
    /*
     * Exercise:
     * -- the problem will show if you uncomment the next line
     *    do so, then run and observe that it hangs
     * -- analyze the deadlock in DDT
     */
    //MPI_Barrier(comm);
  }
}

int main(int argc,char **argv) {
  MPI_Comm comm;
  MPI_Init(&argc,&argv);
  comm = MPI_COMM_WORLD;

  int mytid;
  MPI_Comm_rank(comm,&mytid);
  // Initialize the random number generator
  srand(mytid);
  
  double returned_number;
  loop_for_awhile(comm,&returned_number);
  printf("[%d] returned %e\n",mytid,returned_number);

  MPI_Finalize();
  return 0;
}
