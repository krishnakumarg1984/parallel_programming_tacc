#!/usr/bin/env python
################################################################
####
#### This makefile is part of the tutorial
#### `Introduction to the PETSc library'
#### by Victor Eijkhout eijkhout@tacc.utexas.edu
####
#### copyright Victor Eijkhout 2012-6
####
################################################################

import sys

from petsc4py import PETSc

petsc_init_success = PETSc.Sys.isInitialized()
# if petsc_init_success:
#     PETSc.Sys.Print("PETSc is successfully initialized")
# else:
if not petsc_init_success:
    PETSc.Sys.Print("PETSc is not initialized")
    sys.exit(1)

petsc_major_ver, petsc_minor_ver, petsc_patch_ver = PETSc.Sys.getVersion()
print(f"PetSc version is: v{petsc_major_ver}.{petsc_minor_ver}.{petsc_patch_ver}")
# print(f"PetSc version info is: {PETSc.Sys.getVersionInfo()}")


# from mpi4py import MPI

comm = PETSc.COMM_WORLD


nprocs = comm.Get_size()
procno = comm.Get_rank()

####
#### Exercise 1:
#### - print out the number of processes from process zero
####
#### your code here ####
PETSc.Sys.Print(f"Number of processes: {nprocs}", comm=comm)


####
#### Exercise 2:
#### - Let all processes print out their number in sequence
####
#### your code here ####
PETSc.Sys.syncPrint(f"Hello from process {procno}", comm=comm)
PETSc.Sys.syncFlush(comm=comm)
