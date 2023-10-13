#!/usr/bin/env python

import sys

from petsc4py import PETSc

petsc_init_success = PETSc.Sys.isInitialized()
if not petsc_init_success:
    PETSc.Sys.Print("PETSc is not initialized")
    sys.exit(1)

comm = PETSc.COMM_WORLD

n, N = PETSc.Sys.splitOwnership([PETSc.DECIDE, 100], comm=comm)
PETSc.Sys.Print(f"Global: {N}, local: {n}", comm=comm)

n, N = PETSc.Sys.splitOwnership([10, PETSc.DECIDE], comm=comm)
PETSc.Sys.Print(f"Global: {N}, local: {n}", comm=comm)
