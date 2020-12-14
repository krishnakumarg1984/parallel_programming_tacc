################################################################
################################################################
####
#### This makefile is part of the source of 
#### "Parallel Programming in MPI and OpenMP"
#### by Victor Eijkhout, copyright 2013-2020
####
#### Makefile for MPI course slides
####
################################################################
################################################################

info::

COURSE = mpi
COURSES  = mpi mpl mpithree
EXTRATEXINPUTS = :${HOME}/Software/TeX/LaTeX//:${HOME}/Current/istc/scientific-computing-private/graphics//
include ../course-support/Make.course

jordan.pdf :
	@TEXINPUTS=../graphics:${TEXINPUTS} ${ENGINE} jordan.tex

exercisecheck :
	exercises=` grep exerciseframe *.tex | grep '\[' | cut -d [ -f 2 | cut -d ] -f 1 \
	            | grep -v serialsend | sort -u ` \
	&& for l in c cxx f f08 p ; do \
	     echo "%%%%%%%%%%%%%%%% $${l} %%%%%%%%%%%%%%%%" \
	     && for e in $${exercises} ; do \
	          h=` ls ../solutions-mpi-$${l}/$${e}* 2>/dev/null \
	              | wc -l ` ; \
	          if [ $${h} -eq 0 ] ; then \
	            echo "Exercise $${e} not present for $${l}" ; \
	          fi ; \
	        done ; \
	   done

include ../instructor-support/Make.course
include ../../makefiles/Make.clean

total_clean ::
	@for f in ${FILES} ; do \
	  rm -f $${f}.pdf ; \
	done
info ::
	@echo "make clean [ PDFEXCLUDE=... ]"
clean ::
	@for f in ${FILES} ; do \
	  if [ "$${f}" != "${PDFEXCLUDE}" ] ; then \
	    /bin/rm -f $${f}.pdf ; \
	  fi ; \
	done
