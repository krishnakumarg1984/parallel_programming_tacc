# -*- makefile -*-
################################################################
####
#### This makefile is part of `Parallel Programming in MPI and OpenMP'
#### by Victor Eijkhout, copyright 2013-2021
#### eijkhout@tacc.utexas.edu
####
#### Makefile for  MPI course exercises in Fortran2008
####
################################################################

info ::

COURSE = mpi

info ::
	@echo "make EXERCISE (where EXERCISE=${CEXERCISES} ${FEXERCISES})"
EXERCISES = hello \
    commrank prime randommax jordan \
    pingpong sendrecv sumsquares scangather \
    rightsend rightput rightgraph \
    bucketblock bucketpipenonblock setdiff \
    isendirecv isendirecvarray status \
    stridesend cubegather onenorm procgrid \
    randomput onesidedbuild countdown lockfetch lockfetchshared \
    blockwrite shareddata ibarrierupdate
OTHERPROGRAMS = write

MODE = mpi
LANGUAGE = F
include ../course-support/Make.compile

shareddata : contents.o

####
#### Regression tests
####

include ../course-support/Make.mpi_run
include ../course-support/Make.mpi_regress
run_hello : hello

include ../course-support/Make.clean
