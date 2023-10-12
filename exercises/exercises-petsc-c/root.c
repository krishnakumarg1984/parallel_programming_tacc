/****************************************************************
 ****
 **** This program file is part of the tutorial
 **** `Introduction to the PETSc library'
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** copyright Victor Eijkhout 2012-2020
 ****
 **** root.c : exercise for backtracing error messages
 ****
 ****************************************************************/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <petsc.h>

PetscErrorCode square_root(PetscReal x, PetscReal* rootx)
{
    PetscFunctionBegin;
    /*
     * Exercise:
     * set the `rootx' variable for nonnegative input,
     * or return an error for negative input.
     */
    /**** your code here ****/
    if (x >= 0)
    {
        *rootx = sqrt(x);
    }
    else
    {
        SETERRQ(PETSC_COMM_SELF, 1, "Cannot compute the square root of %f", x);
    }
    PetscFunctionReturn(0);
}

int main(int argc, char** argv)
{
    const char help[] = "\nInit example.\n\n";

    PetscErrorCode ierr;
    ierr = PetscInitialize(&argc, &argv, PETSC_NULLPTR, help);
    CHKERRQ(ierr);

    PetscReal x, rootx;

    x    = 1.5;
    ierr = square_root(x, &rootx);
    CHKERRQ(ierr);
    PetscPrintf(PETSC_COMM_WORLD, "Root of %f is %f\n", x, rootx);

    x    = -2.6;
    ierr = square_root(x, &rootx);
    CHKERRQ(ierr);
    PetscPrintf(PETSC_COMM_WORLD, "Root of %f is %f\n", x, rootx);

    ierr = PetscFinalize();
    CHKERRQ(ierr);

    return 0;
}
