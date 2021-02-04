# -*- makefile -*-
################################################################
####
#### This makefile is part of `Parallel Programming in MPI and OpenMP'
#### by Victor Eijkhout, copyright 2013-2021
#### eijkhout@tacc.utexas.edu
####
#### Makefile for MPI course exercises in C++
####
################################################################

info ::

COURSE = mpi

info ::
	@echo "make EXERCISE (where EXERCISE=${EXERCISES})"
EXERCISES = hello \
    commrank prime randommax jordan sumsquares onenorm \
    pingpong sendrecv stridesend transposeblock scangather \
    rightsend bucketblock bucketpipenonblock \
    isendirecv isendirecvarray procgrid procgridnonblock \
    rightput randomput onesidedbuild countdown lockfetch \
    blockwrite viewwrite scatterwrite cubegather \
    ibarrierupdate rightgraph shareddata
info ::
	@echo "    [ OPTS=... ] (for instance: OPTS=\"-DN 100\")"
	@echo "    support options:"
	@echo "      bucketblock : N"

MODE = mpi
LANGUAGE = CXX
include ../course-support/Make.compile


####
#### Regression tests
####

include ../course-support/Make.mpi_run
include ../course-support/Make.mpi_regress

include ../course-support/Make.clean