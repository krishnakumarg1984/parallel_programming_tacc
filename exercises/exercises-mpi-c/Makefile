# -*- makefile -*-
################################################################
####
#### This makefile is part of `Parallel Programming in MPI and OpenMP'
#### by Victor Eijkhout, copyright 2013-2020
#### eijkhout@tacc.utexas.edu
####
#### Makefile for MPI course exercises in C
####
################################################################

info ::

COURSE = mpi
MODE = mpi
LANGUAGE = c

info ::
	@echo "make EXERCISE (where EXERCISE=${EXERCISES})"
EXERCISES = hello \
    commrank prime randommax onenorm sumsquares \
    pingpong sendrecv transposeblock \
    isendirecv isendirecvarray \
    bucketblock bucketpipenonblock \
    stridesend cubegather procgrid procgridnonblock \
    randomput countdown onesidedbuild lockall lockfetch lockfetchshared \
    blockwrite blockadvance blockseek blockall viewwrite scatterwrite \
    jordan rightsend rightput rightgraph \
    ibarrierupdate shareddata
info ::
	@echo "    [ OPTS=... ] (for instance: OPTS=\"-DN 100\")"
	@echo "    support options:"
	@echo "      bucketblock : N"

include ../course-support/Make.compile

.SECONDEXPANSION:
${EXERCISES} : $$@.o
	${C_LINKER} -o $@ $^


include ../course-support/Make.simgrid
ifdef TACC_TAU_DIR
include ../course-support/Make.tau
endif

####
#### Regression tests
####

include ../course-support/Make.mpi_regress
CATCHER = ../course-support/catchout
MPIRUN = mpiexec
NP = 4

include ../course-support/Make.clean
# simgrid and regression junk
clean ::
	@/bin/rm -f *.err *.dat *.out[0-9]*
