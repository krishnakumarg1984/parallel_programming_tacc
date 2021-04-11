/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   %%%%
   %%%% This program file is part of the book and course
   %%%% "Parallel Computing"
   %%%% by Victor Eijkhout, copyright 2013-2021
   %%%%
   %%%% spawnapp.c : spawning processes
   %%%%
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <mpi.h>

int main(int argc,char **argv) {

  MPI_Init(&argc,&argv);
  MPI_Comm
    comm_world = MPI_COMM_WORLD,
    comm_self = MPI_COMM_SELF,
    comm_inter;
  int world_p,world_n;
  MPI_Comm_size(comm_world,&world_n);
  MPI_Comm_rank(comm_world,&world_p);

  printf("Spawnapp started...\n");
  MPI_Comm comm_parent;
  MPI_Comm_get_parent(&comm_parent);
  int is_child = (comm_parent!=MPI_COMM_NULL);
  if (is_child) {
    char procname[MPI_MAX_PROCESSOR_NAME]; int len = MPI_MAX_PROCESSOR_NAME;
    MPI_Get_processor_name(procname,&len);
    printf("I detect I am a child running on %s\n",procname);
  } else {
    int universe_size, *universe_size_attr,uflag;
    MPI_Comm_get_attr(comm_world,MPI_UNIVERSE_SIZE,&universe_size_attr,&uflag);
    universe_size = *universe_size_attr;
    if (!uflag) universe_size = world_n;
    int work_n = universe_size - world_n;
    printf("A universe of size %d leaves room for %d workers\n",universe_size,work_n);
    if (work_n<=0) 
      MPI_Abort(comm_world,1);
    const char *workerprogram = "./publishapp";
    MPI_Comm_spawn(workerprogram,MPI_ARGV_NULL,
                   work_n,MPI_INFO_NULL,
    		   0,comm_world,&comm_inter,NULL);
  }

  MPI_Finalize();

  return 0;
}

