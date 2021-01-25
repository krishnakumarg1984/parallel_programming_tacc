################################################################
################################################################
####
#### This makefile is part of the source of 
#### "Parallel Computing for Science and Engineering"
#### by Victor Eijkhout, copyright 2013-2021
####
#### This is the makefile for the MPL examples
####     in examples/mpi/mpl
####
################################################################
################################################################

MAKEFLAGS += --no-builtin-rules

info ::
	@echo "Do: make app (where app=${APPS})"

APPS = commrank \
    sendscalar  recvstatus sendbuffer sendarray sendrange sendlong sendtemplate \
    isendandirecv irecvsource ireducescalar bufring \
    collectscalar collectbuffer reduceuser \
    contiguous vector struct structscalar indexed indexedblock \
    commcompare commpass commsplit
WRONGS = collectarray sendobject

MODE = mpi
LANGUAGE = CXX
.SECONDEXPANSION:
include ../../../makefiles/Make.compile
CPPSTANDARD = 17
EXTRA_OPTIONS = -I${TACC_MPL_INC}

info ::
	@echo "make listsources : list of source files"
.PHONY: listsources
listsources :
	@for a in ${APPS} ; do \
	  if [ -e $$a.c ] ; then echo $$a.c ; fi ; \
	  if [ -e $$a.cxx ] ; then echo $$a.cxx ; fi ; \
	done | awk 'BEGIN { v="" } {v = v " " $$0} END {print v}'
	@echo tools.{c,h}


RUNS =
info ::
	@echo "make run_XXX (in ${RUNS})"

include  ../../../makefiles/Make.clean
include ../../../teaching/course-support/Make.mpi_run
include ../../../teaching/course-support/Make.mpi_regress
CATCHER = ../../../teaching/course-support/catchout

clean ::
	@rm -f *.dat *.out[0-9]*
