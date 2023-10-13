/****************************************************************
 ****
 **** This program file is part of the tutorial
 **** `Introduction to the PETSc library'
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** copyright Victor Eijkhout 2012-2020
 ****
 **** init.c : petsc initialization
 ****
 ****************************************************************/

#include <petscsys.h>
#include <petscsystypes.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    PetscErrorCode ierr;
    const char help[] = "\nInit example.\n\n";

    ierr = PetscInitialize(&argc, &argv, (char*)0, help);
    CHKERRQ(ierr);

    int flag;
    MPI_Initialized(&flag);
    MPI_Comm comm = PETSC_COMM_WORLD;
    if (flag)
        PetscPrintf(comm, "MPI was initialized by PETSc\n");
    else
        PetscPrintf(comm, "MPI not yet initialized\n");

    return PetscFinalize();
}
