################################################################
################################################################
####
#### This makefile is part of the source of 
#### "Parallel Computing for Science and Engineering"
#### by Victor Eijkhout, copyright 2013-2021
####
#### This is the makefile for the C examples
####     in examples/mpi/c
####
################################################################
################################################################

MAKEFLAGS += --no-builtin-rules

info ::
	@echo "================================================================"
	@echo " make examples for system=${MODE}, language=${LANGUAGE}"
	@echo "================================================================"
	@echo "available rules:"

APPS = init thread env outerr abort procname \
    sendandrecv isendandirecv recvblock bufring sendblock ssendblock \
    irecvsource irecvnonblock \
    probe testhang findbarrier ibarriertest ibarrierprobe backintime reductpositive \
    putfence putfencealloc getfence windynamic anysource \
    cancel scan exscan fft itranspose progress interleavegather \
    postwaitwin passive numa \
    reduce reduceinplace allreduce allreduceinplace gather gatherv allgatherv \
    reducescatter trueextent typesize typematch countx tags \
    contiguous vector vectorx vectorpadsend getx stridestretch interleave indexed struct pack subarray \
    typefloat \
    itransposeblock \
    commdupwrong commdupright commdupall commcompare \
    commsplit commsplittype intercomm \
    lockall sharedshared sharedbulk \
    cart graph rightgraphtwo persist \
    spawnmanager spawnworker spawnapp portapp publishapp \
    centraldiff blockwrite 
# not ready for prime time: mvp2d
WRONGS = sendblock ssendblock recvblock

MODE = mpi
LANGUAGE = C
.SECONDEXPANSION:
ifeq "${TACC_SYSTEM}" "macbookair"
#  EXTRA_LIBS = -L/opt/local/lib -lefence
endif
include ../../../makefiles/Make.compile

##
## aux files
##
EXTRA_OBJS_countdown_put = gather_sort_print.o
EXTRA_OBJS_countdown_acc = gather_sort_print.o
EXTRA_OBJS_countdown_op  = gather_sort_print.o
countdown_put.o countdown_acc.o countdown_op.o : gather_sort_print.o
countdown_put.o countdown_acc.o countdown_op.o \
    gather_sort_print.o : gather_sort_print.h

#### VLE ${patsubst %,%.o,${APPS}} tools.o : tools.h globalinit.c
#### maybe we need to use $< instead of $^ in the compile rule

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
RUNS += run_abort
.PHONY: run_abort
run_abort : abort
	-@${MPIRUN} -np ${NP} ./abort ; \
	  echo "Return code from ${MPIRUN} is <<$$?>>"

RUNS += run_backintime
.PHONY: run_backintime
run_backintime : backintime
	for i in `seq 1 150` ; do \
	  mpirun -np 3 ./backintime ; \
	done | grep back

RUNS += run_struct
run_struct : struct
	${MPIRUN} -np ${NP} ./struct

RUNS += run_progress
.PHONY: run_progress
run_progress : progress
	@echo "Running with progress thread"
	@export I_MPI_ASYNC_PROGRESS=off \
	&& ${MPIRUN} -np ${NP} progress
	@echo "Running without progress thread"
	@export I_MPI_ASYNC_PROGRESS=on \
	&& ${MPIRUN} -np ${NP} progress

.PHONY: run_spawnapp
info ::
	@echo "make run_spawnapp [ USIZE=123, default: NP ]"
USIZE = ${NP}
MPIEXEC = mpiexec
run_spawnapp : spawnapp
	@\
	if [ ! -z "${USIZE}" ] ; then \
	        usize=${USIZE} \
	    ; elif [ -z "${SLURM_NPROCS}" ] ; then \
	        echo "Can not figure out universe size: use USIZE or SLRUM_NPROCS" \
	         && exit 1 \
	    ; else \
	        usize=${SLRUM_NPROCS} \
	    ; fi \
	 && if [ "${TACC_SYSTEM}" = "frontera" ] ; then \
	        wsize=${NP} \
	         && echo "Running spawnapp with usize=$$usize, wsize=$$wsize" \
	         && MY_MPIRUN_OPTIONS="-usize $$usize" ibrun -np $$wsize spawnapp \
	    ; else \
	        ${MPIEXEC} -n ${NP} -usize ${USIZE} spawnapp \
	    ; fi

MODE = mpi
include ../../../makefiles/Make.clean
#include ../../../makefiles/Make.mpi_run
#include ../../../teaching/course-support/Make.mpi_regress
CATCHER = ../../../teaching/course-support/catchout

clean ::
	@rm -f *.dat *.out[0-9]*
