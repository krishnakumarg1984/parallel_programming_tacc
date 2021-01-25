################################################################
####
#### This makefile is part of the tutorial
#### `Introduction to the PETSc library'
#### by Victor Eijkhout eijkhout@tacc.utexas.edu
####
#### copyright Victor Eijkhout 2012-2020
####
#### Makefile for Fortran90 exercises
####
################################################################

info ::
	@echo "do:"
	@echo "  make exercise"
	@echo "    where exercise is one of ${EXERCISES}"

ifdef PETSC_DIR
include ${PETSC_DIR}/lib/petsc/conf/variables
endif
LOCDIR = fsolutions

EXERCISE = hello
EXERCISES = hello root vec matvec ksp oddeven grid

FFLAGS = ${PETSC_FC_INCLUDES} -D__SDIR__='"${LOCDIR}"'

LANGUAGE = f
EXTRA_FLAGS = ${PETSC_FC_INCLUDES}
include ../course-support/Make.compile
EXTRA_LIBS = ${PETSC_LIB}
shell : fivepoint.o

include ../course-support/Make.petscrun

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
