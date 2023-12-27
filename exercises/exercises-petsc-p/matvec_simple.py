#!/usr/bin/env python

# import math
import sys

from petsc4py import init

init(sys.argv)
from petsc4py import PETSc  # noqa: E402

comm = PETSc.COMM_WORLD

nprocs = comm.Get_size()
procno = comm.Get_rank()


def CreateMatrixDense(comm, nlocal):  # noqa: N802
    A = PETSc.Mat().create(comm=comm)  # noqa: N806
    A.setType(PETSc.Mat.Type.MPIDENSE)
    # procno = comm.Get_rank()
    # if procno == 0:
    #     nlocal = 1
    A.setSizes(((nlocal, None), (nlocal, None)))
    A.assemblyBegin(PETSc.Mat.AssemblyType.FLUSH)
    A.assemblyEnd(PETSc.Mat.AssemblyType.FLUSH)

    _, nglobal = A.getSize()
    first, last = A.getOwnershipRange()
    for row in range(first, last):
        col = row
        v = 2.5
        A.setValue(row, col, v)
        if col + 1 < nglobal:
            A[row, col + 1] = -0.75
    A.assemblyBegin(PETSc.Mat.AssemblyType.FINAL)
    A.assemblyEnd(PETSc.Mat.AssemblyType.FINAL)
    return A


def CreateMatrixSparse(comm, nlocal):  # noqa: N802
    A = PETSc.Mat().create(comm=comm)  # noqa: N806
    A.setType(PETSc.Mat.Type.MPIAIJ)
    procno = comm.Get_rank()
    if procno == 0:
        nlocal = 1
    A.setSizes(((nlocal, None), (nlocal, None)))
    A.setPreallocationNNZ((3, 1))
    A.assemblyBegin(PETSc.Mat.AssemblyType.FLUSH)
    A.assemblyEnd(PETSc.Mat.AssemblyType.FLUSH)

    _, nglobal = A.getSize()
    first, last = A.getOwnershipRange()
    for row in range(first, last):
        col = row
        v = 2.0
        A.setValue(row, col, v)
        col = row - 1
        v = -1.0
        if col >= 0:
            A[row, col] = v
        col = row + 1
        v = -1
        if col < nglobal:
            A[row, col] = v
    A.assemblyBegin(PETSc.Mat.AssemblyType.FINAL)
    A.assemblyEnd(PETSc.Mat.AssemblyType.FINAL)
    return A


def run_explicit():
    nlocal = PETSc.Options().getInt("nlocal", 2)  # default is not optional
    # A = CreateMatrixSparse(comm, nlocal)
    A = CreateMatrixDense(comm, nlocal)  # noqa: N806
    A.view()  # just checking: screen output

    x = PETSc.Vec().create(comm=comm)
    x.setType(PETSc.Vec.Type.MPI)
    n_local_rows, _ = A.getLocalSize()
    x.setSizes((n_local_rows, PETSc.DECIDE))
    x.setFromOptions()
    x.assemblyBegin()
    x.assemblyEnd()
    print("Vec local size on %d: %s" % (procno, str(x.getSizes())))
    y = x.duplicate()
    x.set(2)
    A.mult(x, y)
    y.view()


class MyShellMatrix(object):
    def __init__(self, N):  # noqa: N803
        self.N = N
        # scalar = PETSc.ScalarType
        # self.U = np.zeros([m + 2, n + 2], dtype=scalar)

    def mult(self, A, x, y):  # noqa: N803, ARG002
        # m, n = self.m, self.n
        # xx = x.getArray(readonly=1).reshape(m, n)
        # yy = y.getArray(readonly=0).reshape(m, n)
        yy = y.getArray(readonly=0)
        # laplace2d(self.U, xx, yy)
        yy[:] = 1.0


def construct_operator(N):  # noqa: N803
    """
    Uses *shell* matrix.
    """
    context = MyShellMatrix(N)
    A = PETSc.Mat().createPython(N, context)  # noqa: N806
    A.setUp()
    return A


def run_shell():
    opts = PETSc.Options()  # Access option database to read options from command line
    N = opts.getInt("N", 2)  # noqa: N806 # Read `-N <int>`, defaults to 2
    # m = opts.getInt("m", N)
    # n = opts.getInt("n", m)
    A = construct_operator(N)  # noqa: N806, RUF100, F841,

    x = PETSc.Vec().create(comm=comm)
    x.setType(PETSc.Vec.Type.MPI)
    n_local_rows, _ = A.getLocalSize()
    x.setSizes((n_local_rows, PETSc.DECIDE))
    x.setFromOptions()
    x.assemblyBegin()
    x.assemblyEnd()
    print(f"Vec local size on rank {procno}: {x.getSizes()}")
    y = x.duplicate()
    x.set(2)
    A.mult(x, y)
    y.view()


if __name__ == "__main__":
    # run_explicit()
    run_shell()
