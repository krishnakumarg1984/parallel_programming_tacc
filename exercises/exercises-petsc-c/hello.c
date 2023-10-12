/****************************************************************
 ****
 **** This program file is part of the tutorial
 **** `Introduction to the PETSc library'
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** copyright Victor Eijkhout 2012-9
 ****
 ****************************************************************/

#include "petsc.h"
#include "petscerror.h"
#include "petscsys.h"
#include <stdio.h>

int main(int argc, char** argv)
{
    int ierr = PetscInitialize(&argc, &argv, PETSC_NULLPTR, PETSC_NULLPTR);
    CHKERRQ(ierr);

    MPI_Comm comm = PETSC_COMM_WORLD;
    int procno, nprocs;
    MPI_Comm_rank(comm, &procno);
    MPI_Comm_size(comm, &nprocs);

    /*
     * Exercise 1:
     * -- use PetscPrintf to print only from process zero
     *    make sure to remove the original printf!
     */
    // printf("Hello, I'm processor %d and %d processors have just initialized\n", procno, nprocs);
    /**** your code here ****/
    ierr = PetscPrintf(comm, "This program runs from %d processors\n", nprocs);
    CHKERRQ(ierr);

    /*
     * Exercise 2:
     * -- use PetscSynchronizedPrintf to let each processor print in sequence
     */
    // #if 0
    ierr = PetscSynchronizedPrintf(comm, "I'm processor %d and there are %d processes in total\n", procno, nprocs);
    CHKERRQ(ierr);
    ierr = PetscSynchronizedFlush(comm, stdout);
    CHKERRQ(ierr);
    // #endif

    ierr = PetscFinalize();
    CHKERRQ(ierr);

    return 0;
}
