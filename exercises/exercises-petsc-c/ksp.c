/****************************************************************
 ****
 **** This program file is part of the tutorial
 **** `Introduction to the PETSc library'
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** copyright Victor Eijkhout 2012-2020
 ****
 ****************************************************************/

#include <petscksp.h>
#include <petscmacros.h>
#include <petscmat.h>
#include <petscpctypes.h>
#include <petscsys.h>
#include <petscsystypes.h>
#include <petscvec.h>

PetscErrorCode FivePointMatrix(MPI_Comm, int, int, PetscScalar, Mat*);

#undef __FUNCT__
#define __FUNCT__ "main"
int main(int argc, char** argv)
{
    PetscErrorCode ierr;
    ierr = PetscInitialize(&argc, &argv, PETSC_NULLPTR, PETSC_NULLPTR);
    CHKERRQ(ierr);

    /*
     * Read the domain size, and square it to get the matrix size
     */
    PetscInt domain_size = 100;
    PetscBool flag;
    ierr = PetscOptionsGetInt(NULL, PETSC_NULLPTR, "-n", &domain_size, &flag);
    CHKERRQ(ierr);

    MPI_Comm comm = PETSC_COMM_WORLD;
    PetscPrintf(comm, "Using domain size %d\n", domain_size);

    /*
     * Read the amount of umsymmetry to be added to the matrix
     */
    PetscScalar unsymmetry = 0.;
    ierr                   = PetscOptionsGetReal(NULL, PETSC_NULLPTR, "-unsymmetry", &unsymmetry, &flag);
    CHKERRQ(ierr);

    /*
     * Create the five-point laplacian matrix, with unsymmetry.
     */
    Mat A;
    ierr = FivePointMatrix(comm, domain_size, domain_size, unsymmetry, &A);
    CHKERRQ(ierr);
    // MatView(A, PETSC_VIEWER_STDOUT_WORLD);

    /*
     * Create right hand side and solution vectors
     */
    PetscInt localsize;
    ierr = MatGetLocalSize(A, &localsize, PETSC_NULLPTR);
    CHKERRQ(ierr);

    Vec Rhs;
    ierr = VecCreateMPI(comm, localsize, PETSC_DECIDE, &Rhs);
    CHKERRQ(ierr);

    Vec Sol;
    ierr = VecDuplicate(Rhs, &Sol);
    CHKERRQ(ierr);

    PetscScalar one = 1.0;

    ierr = VecSet(Rhs, one);
    CHKERRQ(ierr);

    /*
     * Create iterative method and preconditioner
     */
    KSP Solver;
    ierr = KSPCreate(comm, &Solver);
    CHKERRQ(ierr);

    ierr = KSPSetOperators(Solver, A, A);
    CHKERRQ(ierr);

    ierr = KSPSetType(Solver, KSPCG);
    CHKERRQ(ierr);
    {
        PC Prec;

        ierr = KSPGetPC(Solver, &Prec);
        CHKERRQ(ierr);

        ierr = PCSetType(Prec, PCJACOBI);
        CHKERRQ(ierr);
    }

    /*
     * Incorporate any commandline options for the KSP
     */
    ierr = KSPSetFromOptions(Solver);
    CHKERRQ(ierr);

    /*
     * Solve the system and analyze the outcome
     */
    ierr = KSPSolve(Solver, Rhs, Sol);
    CHKERRQ(ierr);
    {
        KSPConvergedReason reason;
        ierr = KSPGetConvergedReason(Solver, &reason);
        CHKERRQ(ierr);

        PetscInt its;
        ierr = KSPGetIterationNumber(Solver, &its);
        CHKERRQ(ierr);

        if (reason < 0)
        {
            PetscPrintf(comm, "Failure to converge after %d iterations; reason %s\n", its, KSPConvergedReasons[reason]);
        }
        else
        {
            PetscPrintf(comm, "Number of iterations to convergence: %d\n", its);
        }
    }

    /*
     * Exercise: Investigate the convergence behaviour with different KSP/PC values.
     * You can find the possible values in $PETSC_DIR/include/: petscksp.h and petscpctypes.h
     *
     *    To get feedback on your choices use the following options:
     *    -ksp_monitor : print the progress of the iterative method
     *    -ksp_view    : show the details of the solver
     *    -mat_view    : ascii display of the coefficient matrix.
     *
     * Now do the following experiments:
     * -- try a range of problem sizes with "-ksp_type cg" vs "bcgs" or "gmres"
     * -- set the unsymmetry parameter to something nonzero: "-unsymmetry 1"; higher/lower?
     *    (if you know what convection/diffusion is, how should n/unsymmetry relate?)
     * -- both for the symmetric and unsymmetric case, how does convergence vary with
     *    the number of processes by given problem size?
     * -- with unsymmetry, the iterative methods may fail.
     *    Add a non-trivial precondition: "-pc_type bjacobi" or "asm"
     *    these preconditioners have a sub-pc: "-sub_pc_type ilu" vs "lu"
     *
     * Analyze the cost of various operation by running with "-log_summary".
     * -- what is the time in PCSetUp for "jacobi" vs "bjacobi" with "ilu" or "asm" with "lu"?
     * -- how many matrix-vector products per iteration in cg? bicg? bcgs?
     * -- what mega/gigafloppage are you getting? are you happy with the number?
     */

    /*
     * Clean up allocated objects.
     */
    ierr = MatDestroy(&A);
    CHKERRQ(ierr);

    ierr = VecDestroy(&Rhs);
    CHKERRQ(ierr);

    ierr = VecDestroy(&Sol);
    CHKERRQ(ierr);

    ierr = KSPDestroy(&Solver);
    CHKERRQ(ierr);

    PetscFunctionReturn(PetscFinalize());
}

#undef __FUNCT__
#define __FUNCT__ "FivePointMatrix"
/*
 * Create the five point central difference matrix
 * on a domain of mxn points, that is: the matrix is of size mn.
 *
 * We have an `unsymmetry' parameter: higher values are harder on the iterative method.
 */
PetscErrorCode FivePointMatrix(MPI_Comm comm, int domain_m, int domain_n, double unsymmetry, Mat* rA)
{
    PetscFunctionBeginUser;
    /*
     * Do the basic creation of the matrix
     */
    Mat A;
    int ierr;

    ierr = MatCreate(comm, &A);
    CHKERRQ(ierr);

    ierr = MatSetType(A, MATMPIAIJ);
    CHKERRQ(ierr);

    int matrix_size = domain_m * domain_n;
    ierr            = MatSetSizes(A, PETSC_DECIDE, PETSC_DECIDE, matrix_size, matrix_size);
    CHKERRQ(ierr);

    ierr = MatMPIAIJSetPreallocation(A, 5, PETSC_NULLPTR, 2, PETSC_NULLPTR);
    CHKERRQ(ierr);

    ierr = MatSetOption(A, MAT_NEW_NONZERO_ALLOCATION_ERR, PETSC_FALSE);
    CHKERRQ(ierr);

    ierr = MatSetFromOptions(A);
    CHKERRQ(ierr);

    ierr = MatAssemblyBegin(A, MAT_FLUSH_ASSEMBLY);
    CHKERRQ(ierr);

    ierr = MatAssemblyEnd(A, MAT_FLUSH_ASSEMBLY);
    CHKERRQ(ierr);

    /*
     * Fill in the matrix elements
     */
    PetscInt first, last;
    ierr = MatGetOwnershipRange(A, &first, &last);
    CHKERRQ(ierr);

    int i, j;
    for (i = 0; i < domain_m; ++i)
    {
        for (j = 0; j < domain_n; ++j)
        {
            int iglobal = j + domain_m * i, jglobal;
            if (iglobal < first || iglobal >= last)
                continue;

            // diagonal element
            PetscScalar v = 4.0;
            ierr          = MatSetValues(A, 1, &iglobal, 1, &iglobal, &v, INSERT_VALUES);
            CHKERRQ(ierr);

            // previous row; we set an amount of unsymmetry if this is a periodic point
            jglobal = iglobal - domain_n;
            v       = -1.0;
            if (i > 0)
            {
                ierr = MatSetValues(A, 1, &iglobal, 1, &jglobal, &v, INSERT_VALUES);
                CHKERRQ(ierr);
            }
            else
            {
                jglobal += matrix_size;
                v    = -unsymmetry;
                ierr = MatSetValues(A, 1, &iglobal, 1, &jglobal, &v, INSERT_VALUES);
                CHKERRQ(ierr);
            }

            // next row; we set an amount of unsymmetry if this is a periodic point
            jglobal = iglobal + domain_n;
            v       = -1.0;
            if (i < domain_m - 1)
            {
                ierr = MatSetValues(A, 1, &iglobal, 1, &jglobal, &v, INSERT_VALUES);
                CHKERRQ(ierr);
            }
            else
            {
                jglobal -= matrix_size;
                v    = +unsymmetry;
                ierr = MatSetValues(A, 1, &iglobal, 1, &jglobal, &v, INSERT_VALUES);
                CHKERRQ(ierr);
            }

            // previous point; we set an amount of unsymmetry if this is a periodic point
            jglobal = iglobal - 1;
            v       = -1.0;
            if (j > 0)
            {
                ierr = MatSetValues(A, 1, &iglobal, 1, &jglobal, &v, INSERT_VALUES);
                CHKERRQ(ierr);
            }
            else
            {
                jglobal += domain_n;
                v    = -unsymmetry;
                ierr = MatSetValues(A, 1, &iglobal, 1, &jglobal, &v, INSERT_VALUES);
                CHKERRQ(ierr);
            }

            // next point; we set an amount of unsymmetry if this is a periodic point
            jglobal = iglobal + 1;
            v       = -1.0;
            if (j < domain_n - 1)
            {
                ierr = MatSetValues(A, 1, &iglobal, 1, &jglobal, &v, INSERT_VALUES);
                CHKERRQ(ierr);
            }
            else
            {
                jglobal -= domain_n;
                v    = +unsymmetry;
                ierr = MatSetValues(A, 1, &iglobal, 1, &jglobal, &v, INSERT_VALUES);
                CHKERRQ(ierr);
            }
        }
    }

    ierr = MatAssemblyBegin(A, MAT_FINAL_ASSEMBLY);
    CHKERRQ(ierr);

    ierr = MatAssemblyEnd(A, MAT_FINAL_ASSEMBLY);
    CHKERRQ(ierr);

    *rA = A;
    PetscFunctionReturn(0);
}
