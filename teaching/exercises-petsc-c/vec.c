/****************************************************************
 ****
 **** This program file is part of the tutorial
 **** `Introduction to the PETSc library'
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** copyright Victor Eijkhout 2012-2020
 ****
 ****************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static char help[] = "\nVector exercise. Commandline option: \"-n 123\" for problem size.\n\n";

#include <petscvec.h>

#undef __FUNCT__
#define __FUNCT__ "main"
int main(int argc,char **argv)
{
  Vec            x,y;               /* vectors */
  PetscInt       n = 200;
  PetscErrorCode ierr;

  PetscInitialize(&argc,&argv,(char*)0,help);
  MPI_Comm comm = PETSC_COMM_WORLD;

  /*
   * Get a commandline argument for the size of the problem
   */
  ierr = PetscOptionsGetInt
    (NULL,NULL,"-n",&n,NULL); CHKERRQ(ierr);

  /*
   * Create vector `x' with a default layout
   */
  ierr = VecCreate(comm,&x);CHKERRQ(ierr);
  ierr = VecSetSizes(x,PETSC_DECIDE,n);CHKERRQ(ierr);
  ierr = VecSetFromOptions(x);CHKERRQ(ierr);

  /*
   * Duplicate some work vectors (of the same format and
   * partitioning as the initial vector).
  */
  ierr = VecDuplicate(x,&y);CHKERRQ(ierr);

  /*
   * Set x,y to constant values
  */
  PetscScalar    one = 1.0,two = 2.0;
  ierr = VecSet(x,one);CHKERRQ(ierr);
  ierr = VecSet(y,two);CHKERRQ(ierr);

  /*
   * Exercise 1:
   * - compute inner product of x and y
   */
  PetscScalar inprod;
/**** your code here ****/
  ierr = PetscPrintf(comm,"Computed inner product as %f, should be %f\n",
		     inprod,2.*n); CHKERRQ(ierr);

  /* 
   * Exercise 2:
   * - scale x by that inner product,
   * - take the 2-norm of the result.
   */
  PetscScalar scaling = 1./inprod;
  PetscReal norm;
/**** your code here ****/
  PetscPrintf(comm,"Norm of scaled vector is %f, should be %f\n",
	      norm,sqrt(n/(inprod*inprod)));

  /*
     Free work space.  All PETSc objects should be destroyed when they
     are no longer needed.
  */
  ierr = VecDestroy(&x);CHKERRQ(ierr);
  ierr = VecDestroy(&y);CHKERRQ(ierr);

  ierr = PetscFinalize();
  return 0;
}
