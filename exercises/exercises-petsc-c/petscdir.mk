PETSC_DIR_TMP := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
export PETSC_DIR ?= $(PETSC_DIR_TMP)
