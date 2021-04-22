# -*- makefile
################################################################
####
#### This makefile is part of the tutorial
#### `Introduction to the PETSc library'
#### by Victor Eijkhout eijkhout@tacc.utexas.edu
####
#### copyright Victor Eijkhout 2012-2021
####
#### Makefile for Fortran90 exercises
####
################################################################

info ::
	@echo && echo "================================" && echo "Makefile for PETSc exercises in ${LANGUAGE}" && echo "================================" && echo
	@echo "Available rules:"
	@echo "  make EXERCISE"
	@echo "    where EXERCISE is one of ${EXERCISES}"

include ${PETSC_DIR}/lib/petsc/conf/variables
LOCDIR = fsolutions

EXERCISE = hello
EXERCISES = hello root vec matvec ksp oddeven grid
LANGUAGE = F
MODE = petsc
include ../course-support/Make.compile
#EXTRA_LIBS = ${PETSC_LIB}
#EXTRA_FLAGS = ${PETSC_FC_INCLUDES}
include ../course-support/Make.petscrun

shell : fivepoint.o

##skip
info ::
	@echo "make regression"
.PHONY: regression
regression :
	@for c in ${EXERCISES} ; do \
	  echo ".. compiling $$c" ; \
	  make $$c >/dev/null 2>&1 ; \
	done
	@for c in ${EXERCISES} ; do \
	  echo ".. running $$c" ; \
	  mpirun -np 4 $$c ; \
	done
##endskip

include ../course-support/Make.clean
clean ::
	@rm -f mat.data*
