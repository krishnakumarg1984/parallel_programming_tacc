# -*- makefile -*-
################################################################
####
#### This makefile is part of `Parallel Programming in MPI and OpenMP'
#### by Victor Eijkhout, copyright 2013-2020
#### eijkhout@tacc.utexas.edu
####
#### Makefile for MPI course exercises in C++ through MPL
####
################################################################

info ::

COURSE = mpi
MODE = mpi
LANGUAGE = mpl

info ::
	@echo "make EXERCISE (where EXERCISE=${EXERCISES})"
EXERCISES = hello \
    commrank prime randommax onenorm sumsquares \
    pingpong pingpongbuffer sendrecv \
    isendirecv isendirecvarray \
    bucketblock bucketpipenonblock \
    stridesend cubegather procgrid procgridnonblock \
    randomput countdown onesidedbuild \
    blockwrite blockadvance blockseek blockall viewwrite scatterwrite \
    jordan rightsend rightput rightgraph \
    ibarrierupdate shareddata
info ::
	@echo "    [ OPTS=... ] (for instance: OPTS=\"-DN 100\")"
	@echo "    support options:"
	@echo "      bucketblock : N"

include ../course-support/Make.compile
EXTRA_OPTIONS = -I${TACC_MPL_INC}

.SECONDEXPANSION:
${EXERCISES} : $$@.o
	${C_LINKER} -o $@ $^ -lstdc++


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
# simgrid junk
clean ::
	@/bin/rm -f *.err *.dat
