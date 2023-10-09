/****************************************************************
 ****
 **** This program file is part of the tutorial
 **** `Introduction to the PETSc library'
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** copyright Victor Eijkhout 2012-2021
 ****
 **** size.c : size of petsc quantities
 ****
 ****************************************************************/

#include <petscsys.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    char help[] = "\nSizse measurements.\n\n";

    PetscErrorCode ierr = PetscInitialize(&argc, &argv, (char*)0, help);
    CHKERRQ(ierr);

    printf("size of PetscInt : %zu\n", sizeof(PetscInt));
    printf("size of MPI Int  : %zu\n", sizeof(PetscMPIInt));
    printf("size of PetscReal: %zu\n", sizeof(PetscReal));

    return PetscFinalize();
}
