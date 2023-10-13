#!/usr/bin/env python

import sys

from petsc4py import PETSc

petsc_init_success = PETSc.Sys.isInitialized()
if not petsc_init_success:
    PETSc.Sys.Print("PETSc is not initialized")
    sys.exit(1)

PETSc.Sys.Print("PETSc is initialized")
