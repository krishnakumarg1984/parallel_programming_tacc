# -*- makefile -*-
################################################################
####
#### This makefile is part of `Parallel Programming in MPI and OpenMP'
#### by Victor Eijkhout, copyright 2013-2021
#### eijkhout@tacc.utexas.edu
####
#### Makefile for MPI course exercises in C++ through MPL
####
################################################################

info ::

COURSE = mpi

info ::
	@echo "make EXERCISE (where EXERCISE=${EXERCISES})"
EXERCISES = hello \
    commrank prime randommax onenorm sumsquares \
    pingpong pingpongbuffer sendrecv jordan \
    isendirecv isendirecvarray setdiff \
    bucketblock scangather \
    stridesend cubegather procgrid procgridnonblock transposeblock \
    rightsend rightgraph \
    ibarrierupdate
info ::
	@echo "    [ OPTS=... ] (for instance: OPTS=\"-DN 100\")"
	@echo "    support options:"
	@echo "      bucketblock : N"

MODE = mpl
LANGUAGE = CXX
include ../course-support/Make.compile
CPPSTANDARD = 17
EXTRA_OPTIONS = -I${TACC_MPL_INC}
EXTRA_LIBS = -lstdc++


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
