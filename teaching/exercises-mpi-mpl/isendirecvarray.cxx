/****************************************************************
 ****
 **** This program file is part of the book 
 **** `Parallel programming with MPI and OpenMP'
 **** by Victor Eijkhout, eijkhout@tacc.utexas.edu
 ****
 **** copyright Victor Eijkhout 2020
 ****
 **** MPI Exercise for Isend/Irecv
 ****
 ****************************************************************/

#include <iostream>
#include <sstream>
using namespace std;
#include <mpl/mpl.hpp>

int main() {

  const mpl::communicator &comm_world = mpl::environment::comm_world();
  MPI_Comm_set_errhandler(MPI_COMM_WORLD,MPI_ERRORS_RETURN);
  int nprocs,procno;
  // compute communicator rank and size
  nprocs = comm_world.size();
  procno = comm_world.rank();

  stringstream proctext;

#define N 100
  vector<int> indata(N,1.), outdata(N);
  int leftdata=0.,rightdata=0.;
  int sendto,recvfrom;
  mpl::irequest_pool requests;

  // Exercise:
  // -- set `sendto' and `recvfrom' twice
  //    once to get data from the left, once from the right
  // -- for first/last process use MPI_PROC_NULL

  /*
   * Stage 1: get data from the left.
   * Exercise: who are you communicating with?
   */
/**** your code here ****/
  /*  
   * Start isend and store the request
   */
/**** your code here ****/
		comm_world.isend(indata[0],sendto)
/**** your code here ****/
		comm_world.irecv(leftdata,recvfrom)
/**** your code here ****/


  /*
   * Stage 2: data from the right
   * Exercise: who are you communicating with?
   */
/**** your code here ****/
  /* 
   * Start isend and store the request
   */
/**** your code here ****/
		comm_world.isend(indata[N-1],sendto)
/**** your code here ****/
		comm_world.irecv(rightdata,recvfrom)
/**** your code here ****/

  /*
   * Now make sure all Isend/Irecv operations are completed
   */
/**** your code here ****/
  
  /*
   * Do the averaging operation
   * Note that leftdata==rightdata==0 if not explicitly received.
   */
  for (int i=0; i<N; i++)
    if (i==0)
      outdata[i] = leftdata + indata[i] + indata[i+1];
    else if (i==N-1)
      outdata[i] = indata[i-1] + indata[i] + rightdata;
    else
      outdata[i] = indata[i-1] + indata[i] + indata[i+1];
  
  /*
   * Check correctness of the result:
   * value should be 2 at the end points, 3 everywhere else
   */
  int 
    error = nprocs;
  for (int i=0; i<N; i++) {
    if ( (procno==0 && i==0) || (procno==nprocs-1 && i==N-1) ) {
      if (outdata[i]!=2) {
	proctext << "Data on proc " << procno << ", index " << i
		 << " should be 2, not " << outdata[i] << endl;
	cerr << proctext.str(); proctext.clear();
	error = procno;
      }
    } else {
      if (outdata[i]!=3) {
	proctext << "Data on proc " << procno << ", index " << i
		 << " should be 3, not " << outdata[i] << endl;
	cerr << proctext.str(); proctext.clear();
	error = procno;
      }
    }
  }
  int
    errors=-1;
  comm_world.allreduce(mpl::min<int>(),error,errors);
  if (procno==0) {
    if (errors==nprocs) 
      proctext << "Finished; all results correct" << endl;
    else
      proctext << "First error occurred on proc " << errors << endl;
    cout << proctext.str(); proctext.clear();
  }

  return 0;
}
