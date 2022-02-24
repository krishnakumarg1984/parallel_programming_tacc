################################################################
################################################################
####
#### This makefile is part of the source of 
#### "Parallel Computing in MPI and OpenMP"
#### by Victor Eijkhout, copyright 2013-2022
####
#### Makefile for OpenMP C example programs
####
################################################################
################################################################

info ::
	@echo "================================================================"
	@echo " make examples for system=${MODE}, language=${LANGUAGE}"
	@echo "================================================================"
	@echo "available rules:"

info ::
	@echo
	@echo "make app (where app=${APPS})"
APPS = hello hellocount reducttype threadprivate
LANGUAGE = F
MODE = omp
include ../../../makefiles/Make.compile

EXEC = hello
NP = 4
info ::
	@echo
	@echo "make testrun [EXEC=app (where app in ${APPS})] [NP=nnn (default: ${NP})]"
testrun:
	make clean; rm -f ${EXEC}; make ${EXEC}
	OMP_NUM_THREADS=${NP} ./${EXEC}

RUNS = 

RUNS += run_priv
run_priv : threadprivate
	@./threadprivate

include ../../../makefiles/Make.run

include  ../../../makefiles/Make.clean
