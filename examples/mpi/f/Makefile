################################################################
################################################################
####
#### This makefile is part of the source of 
#### "Parallel Computing for Science and Engineering"
#### by Victor Eijkhout, copyright 2013-9
####
#### This is the makefile for the examples/mpi/f
####
################################################################
################################################################

info ::
	@echo "================================================================"
	@echo " make examples for system=${MODE}, language=${LANGUAGE}"
	@echo "================================================================"
	@echo "available rules:"

APPS = init local sendrecv anysource \
    putfence getfence exscan \
    irecvsource reduce reduceinplace reduceinplaceptr allreduce gather gatherv \
    contiguous vector struct indexed pack matchkind \
    persist typematch
WRONGS = sendblock ssendblock

listsources :
	@for a in ${APPS} ; do \
	  for e in F F90 ; do \
	    if [ -e $$a.$$e ] ; then echo $$a.$$e ; fi ; \
	  done ; \
	done | awk 'BEGIN { v="" } {v = v " " $$0} END {print v}'

LANGUAGE = F
MODE = mpi
include ../../../makefiles/Make.compile
${patsubst %,%.o,${APPS}} tools.o : globalinit.F90

#include ../../../makefiles/Make.mpi_run
include ../../../makefiles/Make.clean
