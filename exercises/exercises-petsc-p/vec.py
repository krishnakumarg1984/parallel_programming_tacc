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

import math
import sys

from petsc4py import init

init(sys.argv)
from petsc4py import PETSc  # noqa: E402

has_nlocal = PETSc.Options().hasName("nlocal")
if has_nlocal:
    PETSc.Sys.Print("Detected command line option '-nlocal'")

n_local = 200  # default number of local vector elements
# second argument is default, which is NOT optional
n_local = PETSc.Options().getInt("nlocal", n_local)
PETSc.Sys.Print(f"Local vector size (within each MPI rank) is to be set to: {n_local}")

comm = PETSc.COMM_WORLD
nprocs = comm.Get_size()
procno = comm.Get_rank()
PETSc.Sys.Print(f"Total number of processes is: {nprocs}")

# Create vector `x' with a default layout
x = PETSc.Vec().create(comm=comm)
x.setType(PETSc.Vec.Type.MPI)
x.setSizes([n_local, PETSc.DECIDE])
x.setFromOptions()

y = x.duplicate()

x.set(1)

# v = PETSc.Viewer()
# v(x)
# # x.view()

global_size_y = y.getSize()
PETSc.Sys.Print(f"Global size of y is: {global_size_y}")

local_size_y = y.getLocalSize()
PETSc.Sys.syncPrint(
    f"Local size of y on rank {procno} (of {nprocs}) is: {local_size_y}",
    comm=comm,
)
PETSc.Sys.syncFlush(comm=comm)

y.set(2)
# # y.view()

local_first_idx_y, local_last_idx_y = y.getOwnershipRange()
PETSc.Sys.syncPrint(
    f"On rank {procno} (of {nprocs}), first index is: {local_first_idx_y}, last index is: {local_last_idx_y}",
    comm=comm,
)
PETSc.Sys.syncFlush(comm=comm)

local_index_y = 0
while local_index_y < local_last_idx_y:
    value = math.sin(local_index_y * 2.0 * math.pi / global_size_y)
    # y.setValue(local_index_y, value, addv=PETSc.InsertMode.INSERT_VALUES)
    y.setValue(local_index_y, 1.0, addv=PETSc.InsertMode.INSERT_VALUES)
    local_index_y += 1

y.assemblyBegin()
y.assemblyEnd()

####
#### Exercise 1:
#### - compute the inner product of x and y
#### - print the result, only from process zero
####
#### your code here ####
inprod = x.dot(y)
PETSc.Sys.Print(f"The inner product y^H x is: {inprod:4.3e}", comm=comm)

####
#### Exercise 2:
#### - scale x down by the just computed inner product
#### - take the 2-norm of the scaled vector x, print the result
####
norm_x = x.norm(PETSc.NormType.NORM_2)
PETSc.Sys.Print(f"The 2-norm of x is: {norm_x:4.2f}", comm=comm)

x.scale(1.0 / norm_x)
norm_x = x.norm(PETSc.NormType.NORM_2)
PETSc.Sys.Print(f"The 2-norm of unit-scaled x is: {norm_x:4.2f}", comm=comm)
#### your code here ####
