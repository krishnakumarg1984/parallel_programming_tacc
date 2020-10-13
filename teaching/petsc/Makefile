################################################################
####
#### This makefile is part of the tutorial
#### `Introduction to the PETSc library'
#### by Victor Eijkhout eijkhout@tacc.utexas.edu
####
#### copyright Victor Eijkhout 2012-2020
####
#### makefile for PETSc course slides
####
################################################################

info ::

COURSE = petsc
FILE = petsc_course
FILES = petsc_course petsc-handout
INEX = tacc-full

info ::
	@echo "make upload"
.PHONY: upload
include ../Makefile.student
upload ::
	@echo "Copying file <<${FILE}.pdf>>:"
	@echo ".. to Dropbox" \
	&& cp ${FILE}.pdf ${HOME}/DropBox/Scicomp/ISTC
	@echo ".. to public repo" \
	&& cp ${FILE}.pdf ${HOME}/Current/istc/hpc-book-and-course/slides/
	@make student_upload FILE=petsc_course.pdf TARGETDIR=lectures

include ../course-support/Make.course
include ../../makefiles/Make.clean
