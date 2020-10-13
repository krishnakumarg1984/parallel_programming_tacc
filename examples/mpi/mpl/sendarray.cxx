/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   %%%%
   %%%% This program file is part of the book and course
   %%%% "Parallel Computing"
   %%%% by Victor Eijkhout, copyright 2020
   %%%%
   %%%% sendbuffer.cxx : send a buffer in MPL
   %%%%
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

#include <cstdlib>
#include <complex>
#include <iostream>
using std::cout;
using std::endl;

#include <vector>
using std::vector;

#include <mpl/mpl.hpp>
 
int main() {
  const mpl::communicator &comm_world=mpl::environment::comm_world();
  if (comm_world.size()<2)
    return EXIT_FAILURE;

  /*
   * The compiler knows about arrays so we can send them `as is'
   */
  double v[2][2][2];

  // Initialize the data
  if (comm_world.rank()==0) {
    double *vt = &(v[0][0][0]);
    for (int i=0; i<8; i++)
      *vt++ = i;
    
    /*
     * Send and report
     */
    comm_world.send(v, 1);  // send to rank 1

    std::cout << "sent: ";
    vt = &(v[0][0][0]);
    for (int i=0; i<8; i++)
      cout << " " << *(vt+i);
    std::cout << '\n';

    // std::cout << "sent: ";
    // for (double &x : v) 
    //   std::cout << x << ' ';
    // std::cout << '\n';

  } else if (comm_world.rank()==1) {

    /*
     * Receive data and report
     */
    comm_world.recv(v, 0);  // receive from rank 0

    std::cout << "got : ";
    double *vt = &(v[0][0][0]);
    for (int i=0; i<8; i++)
      cout << " " << *(vt+i);
    std::cout << '\n';

  }
  return EXIT_SUCCESS;
}

