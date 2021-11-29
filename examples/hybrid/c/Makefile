################################################################
################################################################
####
#### This makefile is part of the source of 
#### "Parallel Computing for Science and Engineering"
#### by Victor Eijkhout, copyright 2013-6
####
#### This is the makefile for the C examples
####     in examples/mpi/c
####
################################################################
################################################################

info ::
	@echo "================================================================"
	@echo " make examples for system=${MODE}, language=${LANGUAGE}"
	@echo "================================================================"
	@echo "available rules:"

APPS = thread procthread

MODE = hybrid
LANGUAGE = C
include ../../../makefiles/Make.compile

.PHONY: run_procthread
run_procthread : procthread
	@if [ ${SLURM_NNODES} -ne 1 ] ; then \
	    echo "Run this only on one node" && exit 1 \
	    ; \
	fi
	@echo "==== NNODES: ${SLURM_NNODES}"
	@for np in `seq 1 ${SLURM_NPROCS}` ; do \
	    echo "---- nprocs: $${np}" \
	     && OMP_NUM_THREADS=17 mpiexec -n $${np} procthread \
	    ; \
	done

include  ../../../makefiles/Make.run
include  ../../../makefiles/Make.clean
