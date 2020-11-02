! -*- f90 -*-
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!!!
!!!! This program file is part of the tutorial
!!!! `Introduction to the PETSc library'
!!!! by Victor Eijkhout eijkhout@tacc.utexas.edu
!!!!
!!!! copyright Victor Eijkhout 2012-8
!!!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

program Vector
#include <petsc/finclude/petsc.h>
  use petsc
  implicit none
  
  MPI_Comm       :: comm
  Vec            :: x,y
  PetscInt       :: n=200, procno
  PetscScalar    :: one=1.0, two=2.0, inprod,scaling,norm
  PetscBool      :: flag
  PetscErrorCode :: ierr
  
  call PetscInitialize(PETSC_NULL_CHARACTER,ierr)
  CHKERRA(ierr)
  comm = PETSC_COMM_WORLD
  call MPI_Comm_rank(comm,procno,ierr)

  !!
  !! Get a commandline argument for the size of the problem
  !!
  call PetscOptionsGetInt( &
       PETSC_NULL_OPTIONS,PETSC_NULL_CHARACTER, &
       "-n",n,flag,ierr)
  CHKERRA(ierr)

  !!
  !! Create vector `x' with a default layout
  !!
  call VecCreate(comm,x,ierr)
  CHKERRA(ierr)
  call VecSetSizes(x,PETSC_DECIDE,n,ierr)
  call VecSetFromOptions(x,ierr)

  !!
  !! Make another vector, just like x
  !!
  call VecDuplicate(x,y,ierr)

  !!
  !! Set x,y to constant values
  !!
  call VecSet(x,one,ierr)
  call VecSet(y,two,ierr)

  !!
  !! Compute inner product of x,y
  !!
!!!! your code here !!!!
  if (procno==0) &
       print *,"Inner product computed as",inprod,"; should be",2.*n

  !!
  !! Scale x down by that inner product,
  !! take the 2-norm of the result.
  !!
  scaling = 1./inprod
!!!! your code here !!!!
  if (procno==0) &
       print *,"Norm of scaled vector is",norm,"; should be",sqrt(n/(inprod**2))

  !!
  !! Free work space. All PETSc objects should be destroyed when they
  !! are no longer needed
  !!
  call VecDestroy(x,ierr)
  call VecDestroy(y,ierr)

  call PetscFinalize(ierr);
  CHKERRA(ierr)
  
END program Vector
