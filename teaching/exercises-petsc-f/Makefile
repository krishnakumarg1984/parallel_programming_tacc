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
	@echo "  make source"
	@echo "    where source is one of ${SOURCES}"

LANGUAGE = f
ifdef PETSC_DIR
include ${PETSC_DIR}/lib/petsc/conf/variables
endif
LOCDIR = fsolutions

SOURCE = hello
SOURCES = hello root vec matvec ksp oddeven grid

FFLAGS = ${PETSC_FC_INCLUDES} -D__SDIR__='"${LOCDIR}"'

.SECONDEXPANSION:
%.o : %.F90
	${FC} -g -O2 -c ${PETSC_FC_INCLUDES} $^
${SOURCES} : $$@.o
	${FLINKER} -o $@ $@.o ${PETSC_LIB}
shell : fivepoint.o

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
