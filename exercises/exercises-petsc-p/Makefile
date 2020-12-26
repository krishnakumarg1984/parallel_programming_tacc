################################################################
####
#### This makefile is part of the tutorial
#### `Introduction to the PETSc library'
#### by Victor Eijkhout eijkhout@tacc.utexas.edu
####
#### copyright Victor Eijkhout 2012-9
####
#### Makefile for Python exercises
####
################################################################

info ::
	@echo "do:"
	@echo "  make SOURCE"
	@echo "    where SOURCE is one of ${SOURCES}"

LANGUAGE = python
ifdef PETSC_DIR
include ${PETSC_DIR}/lib/petsc/conf/variables
include ${PETSC_DIR}/lib/petsc/conf/rules
endif
LOCDIR = csolutions

SOURCE = hello
SOURCES = hello vec matvec ksp grid
#matvec grid
#grid mat ksp shell ex46 ex46a

# no need to make the examples, so:
.PHONY: ${SOURCES}

PROGRAMEXT = .py
include ../course-support/Make.petscrun

.SECONDEXPANSION:

info ::
	@echo "make run [PROGRAM=prog (default=${PROGRAM})]"
	@echo "         [NP=nn (default=${NP})]"
	@echo "         [PYTHON=... (default=${PYTHON})]"
	@echo "         [OPTIONS=programoptions]"
NP = 4
PYTHON = 

##skip
info ::
	@echo "make regression"
.PHONY: regression
regression :
	@if [ ! -z "${PYTHON}" ] ; then \
	    export mypython=${PYTHON} ; \
	 else \
	    export mypython=python3 ; \
	 fi \
	 && for p in ${SOURCES} ; do \
	      echo ".. running $${p}.py" ; \
	      mpirun -np 4 $$mypython $${p}.py ${OPTIONS} ; \
	    done
##endskip

include ../course-support/Make.clean
clean ::
	@/bin/rm -f ${SOURCES}

