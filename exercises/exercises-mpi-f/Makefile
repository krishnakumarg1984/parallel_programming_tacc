# -*- makefile -*-
################################################################
####
#### This makefile is part of `Parallel Programming in MPI and OpenMP'
#### by Victor Eijkhout, copyright 2013-2021
#### eijkhout@tacc.utexas.edu
####
#### Makefile for  MPI course exercises in Fortran
####
################################################################

info ::

COURSE = mpi
info ::
	@echo "make EXERCISE (where EXERCISE=${EXERCISES}"
EXERCISES = hello \
    commrank prime randommax jordan \
    pingpong sendrecv sumsquares \
    rightsend bucketblock bucketpipenonblock lockfetch lockfetchshared \
    isendirecv isendirecvarray setdiff \
    cubegather onenorm procgrid \
    rightput randomput countdown onesidedbuild \
    blockwrite shareddata ibarrierupdate
OTHERPROGRAMS = write

MODE = mpi
LANGUAGE = F
include ../course-support/Make.compile

####
#### Regression tests
####

include ../course-support/Make.mpi_run
include ../course-support/Make.mpi_regress
run_hello : hello

include ../course-support/Make.clean
