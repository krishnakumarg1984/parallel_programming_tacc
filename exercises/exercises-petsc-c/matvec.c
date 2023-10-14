/****************************************************************
 ****
 **** This program file is part of the tutorial
 **** `Introduction to the PETSc library'
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** copyright Victor Eijkhout 2012-2020
 ****
 ****************************************************************/

static char help[] = "\nMatrix exercise. Commandline option: \"-nlocal 123\" for local block size.\n\n";

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <petscmat.h>
/*
 * Function to create the matrix.
 * Let's pretend that you do not know what happens here,
 * so you have no information about the matrix size and such.
 */
PetscErrorCode CreateMatrix(MPI_Comm comm, int nlocal, Mat* rA)
{

    Mat A;
    PetscInt first, last;
    PetscErrorCode ierr;
    int procno, nglobal;

    ierr = MatCreate(comm, &A);
    CHKERRQ(ierr);
    ierr = MatSetType(A, MATMPIAIJ);
    CHKERRQ(ierr);

    MPI_Comm_rank(comm, &procno);
    if (procno == 0)
        nlocal = 1;
    ierr = MatSetSizes(A, nlocal, nlocal, PETSC_DECIDE, PETSC_DECIDE);
    CHKERRQ(ierr);
    /*
     * Exercise
     * - what happens if you preallocate insufficient space?
     */
    ierr = MatMPIAIJSetPreallocation(A, 3, NULL, 1, NULL);
    CHKERRQ(ierr);

    ierr = MatAssemblyBegin(A, MAT_FLUSH_ASSEMBLY);
    CHKERRQ(ierr);
    ierr = MatAssemblyEnd(A, MAT_FLUSH_ASSEMBLY);
    CHKERRQ(ierr);

    ierr = MatGetSize(A, &nglobal, PETSC_NULLPTR);
    CHKERRQ(ierr);
    ierr = MatGetOwnershipRange(A, &first, &last);
    CHKERRQ(ierr);
    for (int row = first; row < last; row++)
    {
        PetscInt col  = row;
        PetscScalar v = 2.;
        ierr          = MatSetValue(A, row, col, v, INSERT_VALUES);
        CHKERRQ(ierr);
        col = row - 1;
        v   = -1.;
        if (col >= 0)
        {
            ierr = MatSetValue(A, row, col, v, INSERT_VALUES);
            CHKERRQ(ierr);
        }
        col = row + 1;
        v   = -1.;
        if (col < nglobal)
        {
            ierr = MatSetValue(A, row, col, v, INSERT_VALUES);
            CHKERRQ(ierr);
        }
    }
    ierr = MatAssemblyBegin(A, MAT_FINAL_ASSEMBLY);
    CHKERRQ(ierr);
    ierr = MatAssemblyEnd(A, MAT_FINAL_ASSEMBLY);
    CHKERRQ(ierr);

    *rA = A;
    return 0;
}

#undef __FUNCT__
#define __FUNCT__ "main"
int main(int argc, char** argv)
{
    PetscErrorCode ierr;
    ierr = PetscInitialize(&argc, &argv, PETSC_NULLPTR, help);
    CHKERRQ(ierr);

    MPI_Comm comm = PETSC_COMM_WORLD;
    int procno, nprocs;
    MPI_Comm_rank(comm, &procno);
    MPI_Comm_size(comm, &nprocs);

    /*
     * Get a commandline argument for the local block size of the problem
     */
    PetscInt nlocal = 20; // default local block size

    ierr = PetscOptionsGetInt(NULL, NULL, "-nlocal", &nlocal, NULL);
    CHKERRQ(ierr);

    /*
     * Call the matrix creation routine.
     * (Note the way we are treating the pointer to the matrix object.)
     */
    Mat A;
    ierr = CreateMatrix(comm, nlocal, &A);
    CHKERRQ(ierr);

    // ierr = MatView(A, PETSC_VIEWER_STDOUT_WORLD); // just checking : screen output
    // CHKERRQ(ierr);

    /*
     * Start creating a vector
     */
    Vec x;
    ierr = VecCreate(comm, &x);
    CHKERRQ(ierr);
    ierr = VecSetType(x, VECMPI);
    CHKERRQ(ierr);

    /*
     * Exercise:
     * -- find the local size of the matrix, and use that to set the vector size
     */
    {
        PetscInt rowsize;
        /**** your code here ****/
        ierr = MatGetLocalSize(A, &rowsize, PETSC_NULLPTR);
        CHKERRQ(ierr);
        /**** your code here ****/
        // ierr = VecSetSizes(x, rowsize, PETSC_DECIDE);
        ierr = VecSetSizes(x, rowsize, PETSC_DETERMINE);
        CHKERRQ(ierr);

        ierr = VecSetFromOptions(x);
        CHKERRQ(ierr);
    }

    /*
     * Duplicate some work vectors (of the same format and
     * partitioning as the initial vector).
     */
    Vec y;
    ierr = VecDuplicate(x, &y);
    CHKERRQ(ierr);

    /*
     * Set x to constant one
     */
    PetscScalar one = 1.0;

    ierr = VecSet(x, one);
    CHKERRQ(ierr);

    /*
     * Exercise:
     * -- fill in the correct parameters to compute
     *    the matrix vector product y = Ax
     */
    /**** your code here ****/
    ierr = MatMult(A, x, y);
    CHKERRQ(ierr);

    /*
     * First check on the product
     */
    double norm;
    ierr = VecNorm(y, NORM_1, &norm);
    CHKERRQ(ierr);

    if (fabs(2. - norm) > 1.e-14)
    {
        ierr = PetscPrintf(comm, "Wrong norm: %e should be 2.\n", norm);
        CHKERRQ(ierr);
    }
    else
    {
        ierr = PetscPrintf(comm, "Global norm test succeeds on all %d processes\n", nprocs);
        CHKERRQ(ierr);
    }

    // #if 0
    /*
     * Second, more funky test
     */
    // {
    //     PetscScalar* localdata;
    //     Vec localvec;
    //     int localsize;
    //     double norm, norm_shouldbe;
    //     /*
    //      * Create a single-process vector with the size of the local part of y
    //      */
    //     ierr = VecCreate(PETSC_COMM_SELF, &localvec);
    //     CHKERRQ(ierr);
    //     ierr = VecSetType(localvec, VECSEQ);
    //     CHKERRQ(ierr);
    //     ierr = VecGetLocalSize(y, &localsize);
    //     CHKERRQ(ierr);
    //     ierr = VecSetSizes(localvec, localsize, PETSC_DECIDE);
    //     CHKERRQ(ierr);
    //     /*
    //      * Exercise:
    //      * -- put y's data into the local vector,
    //      *    and compute the local norm
    //      * -- hint: use VecGetArray to get the y data
    //      * --       use VecPlaceArray to set that in localvec
    //      */
    //     /**** your code here ****/
    //     /*
    //      * Compute the norm: it should be 1 on the first & last process,
    //      * zero elsewhere
    //      */
    //     ierr = VecNorm(localvec, NORM_1, &norm);
    //     CHKERRQ(ierr);
    //     if (procno == 0 || procno == nprocs - 1)
    //         norm_shouldbe = 1.;
    //     else
    //         norm_shouldbe = 0.;
    //     if (fabs(norm - norm_shouldbe) > 1.e-14)
    //         printf("Wrong local norm %e on proc %d\n", norm, procno);
    //     else
    //         printf("Local norm succeeded\n");
    //
    //     /*
    //      * Let's clean up
    //      */
    //     /*
    //      * Optional exercise:
    //      * -- what are the mirror routines of VecGetArray & VecPlaceArray above?
    //      *    (this mostly serves to prevent memory leaks)
    //      */
    //     /**** your code here ****/
    //     ierr = VecDestroy(&localvec);
    //     CHKERRQ(ierr);
    // }
    // #endif

    /*
       Free work space.  All PETSc objects should be destroyed when they
       are no longer needed.
    */
    ierr = MatDestroy(&A);
    CHKERRQ(ierr);

    ierr = VecDestroy(&x);
    CHKERRQ(ierr);

    ierr = VecDestroy(&y);
    CHKERRQ(ierr);

    return PetscFinalize();
}
