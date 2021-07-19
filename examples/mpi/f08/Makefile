################################################################
################################################################
####
#### This makefile is part of the source of 
#### "Parallel Computing for Science and Engineering"
#### by Victor Eijkhout, copyright 2013-2020
####
#### This is the makefile for the examples/mpi/f08
####
################################################################
################################################################

info ::
	@echo "================================================================"
	@echo " make examples for system=${MODE}, language=${LANGUAGE}"
	@echo "================================================================"
	@echo "available rules:"

APPS = reduceinplace reduceinplaceptr section anysource putfence waitnull vector vectorx \
    typecheck

LANGUAGE = F
MODE = mpi

listsources :
	@for a in ${APPS} ; do \
	  for e in F F90 ; do \
	    if [ -e $$a.$$e ] ; then echo $$a.$$e ; fi ; \
	  done ; \
	done | awk 'BEGIN { v="" } {v = v " " $$0} END {print v}'

info ::
	@echo "make putfence0"
.PHONY: putfence0
putfence0 :
	@make putfence0.o EXTRA_FLAGS=-DZERO

include ../../../makefiles/Make.compile

app_dependencies =
.SECONDEXPANSION:

info ::
	@echo "make run_PROGRAM (in: ${RUNS})"
	@echo "    [ NPSPEC=\"-np 4\" or so; default=<<${NPSPEC}>> ]"
RUNS =
include ../../../makefiles/Make.mpirun
.PHONY: run_waitnull
RUNS += run_waitnull
run_waitnull : waitnull
	${MPIEXEC} ${NP} waitnull

include  ../../../makefiles/Make.clean
