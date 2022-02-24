################################################################
################################################################
####
#### This makefile is part of the source of 
#### "Parallel Computing for Science and Engineering"
#### by Victor Eijkhout, copyright 2013-2022
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
    sendandrecv isendandirecv bufring pingpongbig count \
    irecvsource irecvnonblock \
    probe testhang findbarrier ibarriertest ibarrierprobe backintime reductpositive \
    putfence putfencealloc getfence windynamic anysource \
    cancel scan exscan fft itranspose progress interleavegather \
    postwaitwin passive numa \
    reduce reduceinplace reducecount \
    allreduce allreduceinplace gather gatherv allgatherv \
    randomupdatefence randomupdatelock randomupdateshared \
    reducescatter trueextent typesize typematch countx tags \
    contiguous vector vectorx vectorpadsend getx stridestretch interleave indexed struct pack subarray \
    typefloat \
    itransposeblock \
    commdupwrong commdupright commdupall commcompare \
    commsplit commsplittype intercomm \
    lockall sharedshared sharedbulk \
    cart cartdims cartcoord \
    graph rightgraphtwo persist persistbcast partition \
    spawnmanager spawnworker spawnapp portapp publishapp \
    session sessionmix sessionmulti \
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

RUNS =
include ../../../makefiles/Make.mpi_run

RUNS += run_abort
.PHONY: run_abort
run_abort : abort
	-@${MPIRUN} -n ${NP} ./abort ; \
	  echo "Return code from ${MPIRUN} is <<$$?>>"

## RUNS += run_backintime
.PHONY: run_backintime
run_backintime : backintime
	for i in `seq 1 150` ; do \
	  ${MPIRUN} -n ${NP} ./backintime ; \
	done | grep back

RUNS += run_struct
run_struct : struct
	${MPIRUN} -n ${NP} ./struct

RUNS += run_progress
.PHONY: run_progress
run_progress : progress
	@if [ "${TACC_FAMILY_MPI}" != "intel" ] ; then \
	    echo "This code only works with Intel MPI" && exit 1 \
	    ; fi
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

RUNS += run_cartdims
run_cartdims : cartdims
	@for np in 3 4 12 ; do \
	    make --no-print-directory mpirun \
	        ECHO=${ECHO} \
	        PROGRAM=cartdims NP=$$np \
	    | awk '/cartdims/ {p=0} p==1 {print} /CartDims/ {p=1}' \
	    ; \
	done

RUNS += run_cartshift
.PHONY: run_cartshift
run_cartshift : cartcoord
	@${MPIRUN} -n 6 ./cartcoord \
	| awk '/cartshift/ {p=0} p==1 {print} /CartShift/ {p=1}'


RUNS += run_cartsub
.PHONY: run_cartsub
run_cartsub : cartcoord
	@${MPIRUN} -n 6 ./cartcoord \
	| awk '/hyperplane13p/ {p=0} p==1 {print} /Hyperplane13p/ {p=1}'

RUNS += run_commcompare
.PHONY: run_commcompare
run_commcompare : commcompare
	@${MPIRUN} -n 1 ./commcompare

RUNS += run_pack
.PHONY: run_pack
run_pack : pack
	@${MPIRUN} -n 6 ./pack 6

RUNS += run_sessionmix
.PHONY: run_sessionmix
run_sessionmix : sessionmix
	@${MPIRUN} -n 4 ./sessionmix

####
#### generic runs
####
GENERICS = run_irecvsource run_commsplittype run_gatherv run_persist \
    run_pingpongbig run_procname run_scan 
info ::
	@echo "generics: ${GENERICS}"
RUNS += ${GENERICS}
.PHONY: ${GENERICS}
${GENERICS} :
	@r=$@ && runname=$${r##run_} \
	 && echo "generic run for $$runname" \
	 && make --no-print-directory run_generic \
	            ECHO=${ECHO} MPIRUN=${MPIRUN} OPTIONS=${OPTIONS} \
	            NP=${SLURM_NPROCS} \
	        PROGRAM=$$runname \
	    2>&1 | tee tmp.out \
	 && if [ "${RUNOUT}" = "1" ] ; then \
	        mv tmp.out $$runname.runout \
	         && git add $$runname.runout \
	        ; \
	    fi

MODE = mpi
include ../../../makefiles/Make.clean
#include ../../../makefiles/Make.mpi_run
#include ../../../teaching/course-support/Make.mpi_regress
CATCHER = ../../../teaching/course-support/catchout

clean ::
	@rm -f *.dat *.out[0-9]*
