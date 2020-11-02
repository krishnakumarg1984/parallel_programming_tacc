
################################################################
####
#### This makefile is part of the tutorial
#### `Introduction to the PETSc library'
#### by Victor Eijkhout eijkhout@tacc.utexas.edu
####
#### copyright Victor Eijkhout 2012-2020
####
#### Makefile for petsc C exercises
####
################################################################

info ::
	@echo "do:"
	@echo "  make SOURCE"
	@echo "    where SOURCE is one of ${SOURCES}"

LANGUAGE = c
include ${PETSC_DIR}/lib/petsc/conf/variables
LOCDIR = csolutions

SOURCE = hello
SOURCES = hello root vec matvec ksp shell oddeven grid plex
#grid mat ksp shell ex46 ex46a
# CFLAGS = ${PETSC_CC_INCLUDES} -std=gnu99

.SECONDEXPANSION:
${SOURCES} : $$@.o
	${CLINKER} -o $@ $@.o ${PETSC_LIB}

include ../course-support/Make.compile
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
