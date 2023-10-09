/****************************************************************
 ****
 **** This program file is part of the tutorial
 **** `Introduction to the PETSc library'
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** copyright Victor Eijkhout 2012-2020
 ****
 **** backtrace.c : demonstrate backtracing error messages
 ****
 ****************************************************************/

#include <petsc.h>
#include <stdio.h>
#include <stdlib.h>

static PetscErrorCode this_function_bombs(void)
{
    PetscFunctionBegin;
    SETERRQ(PETSC_COMM_SELF, 1, "We cannot go on like this");
    PetscFunctionReturn(0);
}

int main(int argc, char** argv)
{
    char help[] = "\nInit example.\n\n";

    PetscErrorCode ierr = PetscInitialize(&argc, &argv, (char*)0, help);
    CHKERRQ(ierr);

    ierr = this_function_bombs();
    CHKERRQ(ierr);

    return PetscFinalize();
}
