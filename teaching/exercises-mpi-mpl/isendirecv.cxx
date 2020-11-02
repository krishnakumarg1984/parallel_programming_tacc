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
  int nprocs,procno;
  // compute communicator rank and size
  nprocs = comm_world.size();
  procno = comm_world.rank();

  stringstream proctext;

  int mydata=1.,leftdata=0.,rightdata=0.;
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
		comm_world.isend(mydata,sendto)
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
		comm_world.isend(mydata,sendto)
/**** your code here ****/
		comm_world.irecv(rightdata,recvfrom)
/**** your code here ****/

  /*
   * Now make sure all Isend/Irecv operations are completed
   */
/**** your code here ****/
  
  // check correctness
  mydata = mydata+leftdata+rightdata;
  if (procno==0 || procno==nprocs-1) {
    if (mydata!=2) {
      proctext << "Data on proc " << procno << " should be 2, not " << mydata << endl;
      cerr << proctext.str(); proctext.clear();
    }
  } else {
    if (mydata!=3) {
      proctext << "Data on proc " << procno << " should be 3, not " << mydata << endl;
      cerr << proctext.str(); proctext.clear();
    }
  }
  if (procno==0) {
    proctext << "Finished" << endl;
    cerr << proctext.str(); proctext.clear();
  }

  return 0;
}
