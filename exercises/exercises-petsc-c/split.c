/****************************************************************
 ****
 **** This program file is part of the tutorial
 **** `Introduction to the PETSc library'
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** copyright Victor Eijkhout 2012-2020
 ****
 **** split.c : demonstrate PetscSplitOwnership
 ****
 ****************************************************************/

#include <math.h>
#include <petscsys.h>
#include <petscsystypes.h>
// #include <petscmacros.h>
// #include <petscvec.h>
#include <stdio.h>
#include <stdlib.h>

static const char help[] = "\nOwership example.\n\n";

int main(int argc, char** argv)
{
    PetscErrorCode ierr;
    ierr = PetscInitialize(&argc, &argv, PETSC_NULLPTR, help);
    CHKERRQ(ierr);

    MPI_Comm comm = PETSC_COMM_WORLD;

    int nprocs, procid;
    MPI_Comm_size(comm, &nprocs);
    MPI_Comm_rank(comm, &procid);

    PetscInt N, n;
    N = 100;
    n = PETSC_DECIDE;
    PetscSplitOwnership(comm, &n, &N);
    PetscPrintf(comm, "Global %d, local %d\n", N, n);

    N = PETSC_DECIDE;
    n = 10;
    PetscSplitOwnership(comm, &n, &N);
    PetscPrintf(comm, "Global %d, local %d\n", N, n);

    // PetscPrintf(comm, "Size of PetscInt is %zu\n", sizeof(PetscInt));

    return PetscFinalize();
}
