/****************************************************************
 ****
 **** This program file is part of the book 
 **** `Parallel programming with MPI and OpenMP'
 **** by Victor Eijkhout, eijkhout@tacc.utexas.edu
 ****
 **** copyright Victor Eijkhout 2012-2020
 ****
 **** MPI Exercise for sendrecv : three-point combination in MPL
 ****
 ****************************************************************/

#include <iostream>
#include <sstream>
using namespace std;
#include <mpl/mpl.hpp>

int main(int argc,char **argv) {

  const mpl::communicator &comm_world = mpl::environment::comm_world();
  int nprocs,procno;
  // compute communicator rank and size
  nprocs = comm_world.size();
  procno = comm_world.rank();

  stringstream proctext;
  
  int mydata=1,leftdata=0,rightdata=0;
  int sendto,recvfrom;

  // Exercise:
  // -- set `sendto' and `recvfrom' twice
  // -- once to get data from the left, once from the right

  // first get left neighbour data
  //hint:  sendto = 
  //hint:  recvfrom =
/**** your code here ****/
  mpl::tag t0(0);
  comm_world.sendrecv
    ( mydata,sendto,t0,
      leftdata,recvfrom,t0 );

  // then the right neighbour data
  //hint:  recvfrom =
  //hint:  sendto = 
/**** your code here ****/
  comm_world.sendrecv( mydata,sendto,t0, rightdata,recvfrom,t0 );

  // check correctness
  mydata = mydata+leftdata+rightdata;

  int error=nprocs,errors;
  if (procno==0 || procno==nprocs-1) {
    if (mydata!=2) {
      proctext << "Data on proc " << procno << " should be 2, not " << mydata << endl;
      error = procno;
    }
    cerr << proctext.str(); proctext.clear();
  } else {
    if (mydata!=3) {
      proctext << "Data on proc " << procno << " should be 3, not " << mydata << endl;
      error = procno;
    }
  }

  comm_world.allreduce(mpl::min<int>(),error,errors);
  if (procno==0) {
    if (errors==nprocs) 
      proctext << "Finished; all results correct" << endl;
    else
      proctext << "First error occurred on proc " << errors << endl;
    cerr << proctext.str(); proctext.clear();
  }

  return 0;
}
