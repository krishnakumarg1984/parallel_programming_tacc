
################################################################
####
#### This makefile is part of the tutorial
#### `Introduction to the PETSc library'
#### by Victor Eijkhout eijkhout@tacc.utexas.edu
####
#### copyright Victor Eijkhout 2012-2021
####
#### Makefile for petsc C exercises
####
################################################################

info ::
	@echo && echo "================================" && echo "Makefile for PETSc exercises" && echo "================================" && echo
	@echo "Available rules:"
	@echo "  make EXERCISE"
	@echo "    where EXERCISE is one of ${EXERCISES}"

include ${PETSC_DIR}/lib/petsc/conf/variables
LANGUAGE = C
MODE = petsc
include ../course-support/Make.compile
LOCDIR = csolutions

EXERCISE = hello
EXERCISES = hello root vec matvec ksp shell oddeven grid plex
#grid mat ksp shell ex46 ex46a

include ../course-support/Make.petscrun

##skip
info ::
	@echo "make regression"
.PHONY: regression
regression :
	@for c in ${SOURCES} ; do \
	  echo ".. compiling $$c" ; \
	  make $$c >/dev/null 2>&1 ; \
	done
	@for c in ${SOURCES} ; do \
	  echo ".. running $$c" ; \
	  mpirun -np 4 $$c ; \
	done
##endskip

include ../course-support/Make.clean
clean ::
	@rm -f mat.data*
