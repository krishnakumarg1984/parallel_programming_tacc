/****************************************************************
 ****
 **** This program file is part of the tutorial
 **** `Introduction to the PETSc library'
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** copyright Victor Eijkhout 2012-2020
 ****
 ****************************************************************/

#include <petscsys.h>
#include <petscvec.h>
#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#define _USE_MATH_DEFINES // required usually for some Win32 targets :(
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static char help[] = "\nVector exercise. Pass option: \"-nlocal 123\" for local vector size in each MPI rank.\n\n";

#undef __FUNCT__
#define __FUNCT__ "main"
int main(int argc, char** argv)
{
    PetscErrorCode ierr;
    ierr = PetscInitialize(&argc, &argv, PETSC_NULLPTR, help);
    CHKERRQ(ierr);

    /*
     * Get a commandline argument for the size of the problem
     */
    PetscInt n_local = 200;
    ierr             = PetscOptionsGetInt(NULL, NULL, "-nlocal", &n_local, NULL);
    CHKERRQ(ierr);

    MPI_Comm comm = PETSC_COMM_WORLD;
    PetscPrintf(comm, "Local vector size (within each MPI rank) is to be set to: %d\n", n_local);

    int nprocs, procno;
    MPI_Comm_rank(comm, &procno);
    MPI_Comm_size(comm, &nprocs);
    PetscPrintf(comm, "Number of MPI ranks: %d\n", nprocs);

    /*
     * Create vector `x' with a default layout
     */
    Vec x;
    ierr = VecCreate(comm, &x);
    CHKERRQ(ierr);
    ierr = VecSetType(x, VECMPI);
    CHKERRQ(ierr);
    ierr = VecSetSizes(x, n_local, PETSC_DECIDE); // parameter ordering is: local, then global
    CHKERRQ(ierr);
    ierr = VecSetFromOptions(x);
    CHKERRQ(ierr);

    /*
     * Duplicate some work vectors (of the same format and
     * partitioning as the initial vector).
     */
    Vec y;
    ierr = VecDuplicate(x, &y);
    CHKERRQ(ierr);

    /*
     * Set x,y values
     */
    PetscScalar one = 1.0;

    ierr = VecSet(x, one);
    CHKERRQ(ierr);

    PetscScalar two = 2.0;

    ierr = VecSet(y, two);
    CHKERRQ(ierr);

    PetscScalar sum_y;
    ierr = VecSum(y, &sum_y);
    CHKERRQ(ierr);
    ierr = PetscPrintf(comm, "Sum of entries of y with uniform value of %4.2f is %4.2f\n", two, sum_y);
    CHKERRQ(ierr);

    {
        /*
         * Exercise 1:
         * -- Set y to a sine wave
         *    --------------------
         *    Find the correct bounds on the loop
         *    so that each process sets only local elements
         *    Set the correct index
         */
        PetscInt myfirst, mylast, localsize, globalsize;

        ierr = VecGetSize(y, &globalsize);
        CHKERRQ(ierr);
        PetscPrintf(comm, "Global size of y is: %d\n", globalsize);

        ierr = VecGetLocalSize(y, &localsize);
        CHKERRQ(ierr);
        ierr = PetscSynchronizedPrintf(comm, "Local size of y on rank %d (of %d) is: %d\n", procno, nprocs, localsize);
        CHKERRQ(ierr);
        ierr = PetscSynchronizedFlush(comm, stdout);
        CHKERRQ(ierr);

        ierr = VecGetOwnershipRange(y, &myfirst, &mylast);
        CHKERRQ(ierr);
        ierr = PetscSynchronizedPrintf(comm, "On rank %d (of %d), first local index: %d; last local index: %d\n",
                                       procno, nprocs, myfirst, mylast);
        CHKERRQ(ierr);
        ierr = PetscSynchronizedFlush(comm, stdout);
        CHKERRQ(ierr);

        /**** your code here ****/
        for (PetscInt index = myfirst; index < mylast; ++index)
        {
            PetscScalar value = sin(index * 2.0 * M_PI / globalsize);
            // PetscScalar value = 1.0;
            /**** your code here ****/
            ierr = VecSetValue(y, index, value, INSERT_VALUES);
            CHKERRQ(ierr);
        }
        ierr = VecAssemblyBegin(y);
        CHKERRQ(ierr);
        ierr = VecAssemblyEnd(y);
        CHKERRQ(ierr);
        ierr = VecSum(y, &sum_y);
        CHKERRQ(ierr);
        ierr = PetscPrintf(comm, "Sum of entries of y with uniform value of %4.2f is %4.2f\n", two, sum_y);
        CHKERRQ(ierr);
    }

    /*
     * Exercise 2:
     * - compute inner product of x and y
     */
    PetscScalar inprod;
    /**** your code here ****/
    ierr = VecDot(x, y, &inprod);
    CHKERRQ(ierr);
    ierr = PetscPrintf(comm, "Computed inner product as %f, should be about zero\n", inprod);
    CHKERRQ(ierr);

    /*
     * Exercise 3:
     * -- compute the norm of x
     * -- scale x down by that norm
     * -- check that the norm of the result is 1
     */
    /**** your code here ****/
    PetscReal norm_x;
    ierr = VecNorm(x, NORM_2, &norm_x);
    CHKERRQ(ierr);
    ierr = PetscPrintf(comm, "Norm of vector x is %4.2f\n", norm_x);
    CHKERRQ(ierr);

    ierr = VecScale(x, 1.0 / norm_x);
    CHKERRQ(ierr);
    ierr = VecNorm(x, NORM_2, &norm_x);
    CHKERRQ(ierr);
    PetscPrintf(comm, "Norm of scaled vector is %4.2f, should be 1\n", norm_x);

    /*
       Free work space.  All PETSc objects should be destroyed when they
       are no longer needed.
    */
    ierr = VecDestroy(&x);
    CHKERRQ(ierr);
    ierr = VecDestroy(&y);
    CHKERRQ(ierr);

    ierr = PetscFinalize();
    CHKERRQ(ierr);
    return 0;
}
