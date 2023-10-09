#include "petscversion.h"
#include <petsc.h>
#include <petscsys.h>
#include <stdio.h>
#if PETSC_VERSION_LT(3, 17, 0)
#else
#error This program uses APIs abandoned in 3.17
#endif

int main(void)
{
    printf("%s", PETSC_VERSION_GIT);
    return EXIT_SUCCESS;
}
