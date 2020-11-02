# -*- makefile -*-
################################################################
####
#### This makefile is part of `Parallel Programming in MPI and OpenMP'
#### Victor Eijkhout
#### eijkhout@tacc.utexas.edu
####
#### Makefile for short course OpenMP templates in Fortran
####
################################################################

info ::

COURSE = omp
MODE = omp
LANGUAGE = f

info ::
	@echo "make EXERCISE (where EXERCISE=${EXERCISES})"
EXERCISES = parallel pi piadapt taskfactor

include ../course-support/Make.compile

.SECONDEXPANSION:
${EXERCISES} : $$@.F90
	${F_COMPILER} ${FFLAGS} -o $@ $^

include ../course-support/Make.clean
include ../course-support/Make.omp_regress

