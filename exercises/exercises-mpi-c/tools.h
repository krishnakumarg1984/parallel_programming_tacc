/****************************************************************
 ****
 **** This program file is part of the book 
 **** `Parallel programming with MPI and OpenMP'
 **** by Victor Eijkhout, eijkhout@tacc.utexas.edu
 ****
 **** copyright Victor Eijkhout 2012-2021
 ****
 **** tools.h : support routine prototypes
 ****
 ****************************************************************/

#include <math.h>

#define ISAPPROX(x,y) \
  ( ( x==0. && fabs(y)<1.e-14 ) || ( y==0. && fabs(x)<1.e-14 ) || \
    fabs(x-y)/fabs(x)<1.e-14 )

double array_error(double ref_array[],double value_array[],int array_size);
int int_array_error(int ref_array[],int value_array[],int array_size);
int test_all_the_same_int( int value,MPI_Comm comm );
void print_final_result( int cond,MPI_Comm comm );
void error_process_print(int error_proc, MPI_Comm comm);
