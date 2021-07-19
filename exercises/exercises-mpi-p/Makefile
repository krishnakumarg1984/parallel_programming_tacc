# -*- makefile -*-
################################################################
####
#### This makefile is part of `Parallel Programming in MPI and OpenMP'
#### Victor Eijkhout
#### eijkhout@tacc.utexas.edu
####
#### Makefile for course exercises in Python
####
################################################################

info ::

COURSE = mpi
MODE = mpi
LANGUAGE = p

info ::
	@echo "================================================================"
	@echo " make exercises for system=${MODE}, language=${LANGUAGE}"
	@echo "================================================================"
	@echo "available rules:"

EXERCISES = \
    hello commrank prime randommax pingpong setdiff \
    rightsend isendirecv ibarrierupdate \
    onenorm bucketblock stridesend cubegather \
    randomput rightput countdown onesidedbuild \
    lockfetch \
    procgrid blockwrite scatterwrite viewwrite

info ::
	@echo "make run [PROGRAM=prog (default=${PROGRAM})]"
	@echo "         [NP=nn (default=${NP})] [PYTHON=... (default=${PYTHON})]"
	@echo "         [OPTIONS=programoptions]"
.PHONY: run
NP = 4
# PYTHON_clang = /opt/local/bin/python
# PYTHON_gcc  = /opt/local/bin/python2.7
# PYTHON_intel = python3
# PYTHON = ${PYTHON_${TACC_FAMILY_COMPILER}}

PYTHON = python3
PROGRAM = hello
OPTIONS =
include ../course-support/Make.compile

PROGRAM_EXTENSION = .py

####
#### Regression tests
####
.PHONY: ${EXERCISES} 

include ../course-support/Make.mpi_run
include ../course-support/Make.mpi_regress
CATCHER = ../course-support/catchout -p ${PYTHON}
include ../course-support/Make.clean
