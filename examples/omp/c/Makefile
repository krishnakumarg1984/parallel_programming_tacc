################################################################
################################################################
####
#### This makefile is part of the source of 
#### "Parallel Computing in MPI and OpenMP"
#### by Victor Eijkhout, copyright 2013-2021
####
#### Makefile for OpenMP C example programs
####
################################################################
################################################################

info ::
	@echo "================================================================"
	@echo " make examples for system=${MODE}, language=${LANGUAGE}"
	@echo "================================================================"
	@echo "available rules:"

info ::
	@echo
	@echo "make app (where app=${APPS})"
APPS = hello hello3 proccount pi speedup \
    parfor critfun reductpar \
    alloc1 alloc2 sharing race \
    threadprivate ireduct ireductinit ureduct reductpositive \
    taskgroup0 taskgroup1 taskgroup2 taskgroup3 taskgroup4 taskgroup5

listsources :
	@for a in ${APPS} ; do \
	  for e in c cxx ; do \
	    if [ -e $$a.$$e ] ; then echo $$a.$$e ; fi ; \
	  done ; \
	done | awk 'BEGIN { v="" } {v = v " " $$0} END {print v}'

MODE = omp
LANGUAGE = C
include ../../../makefiles/Make.compile

EXEC = hello
NP = 4
info ::
	@echo
	@echo "make testrun [EXEC=app (where app in ${APPS})]"
testrun:
	make clean; rm -f ${EXEC}; make ${EXEC}
	OMP_NUM_THREADS=${NP} ./${EXEC}

include ../Make.omp

info ::
	@echo "make run_xyz (in: ${RUNS})"
	@echo "    [NP=nnn (default: ${NP})]"
include  ../../../makefiles/Make.omp_run
RUNS =
RUNS += run_speedup
.PHONY: run_speedup
run_speedup : speedup
	@make --no-print-directory omp_scaling PROGRAM=speedup

.PHONY: run_race
RUNS += run_race
run_race : race
	( \
	for t in 1 2 4 8 ; do \
	    echo "On $${t} threads:" \
	    && OMP_NUM_THREADS=$${t} ./race \
	    ; \
	done \
	) 2>&1 | tee ../../../output/racecounter.out
info ::
	@echo "make output : regenerate all output"
.PHONY: output
output :
	@for r in ${RUNS} ; do \
	  make $${r} \
	  ; \
	done

include  ../../../makefiles/Make.clean
