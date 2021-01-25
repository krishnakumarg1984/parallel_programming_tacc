/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   %%%%
   %%%% This program file is part of the book and course
   %%%% "Parallel Computing"
   %%%% by Victor Eijkhout, copyright 2020
   %%%%
   %%%% commcompare.c : basics in MPL
   %%%%
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

#include <cstdlib>
#include <iostream>
#include <iomanip>
using namespace std;

#include <mpl/mpl.hpp>
 
int main() {

  const mpl::communicator &comm =
    mpl::environment::comm_world();
  cout << "same: " << boolalpha << (comm==comm) << endl;

  mpl::communicator copy =
    mpl::environment::comm_world();
  cout << "copy: " << boolalpha << (comm==copy) << endl;

  mpl::communicator init = comm;
  cout << "init: " << boolalpha << (init==comm) << endl;

  // WRONG: copy = comm;
  // error: overload resolution selected deleted operator '='

  {
    mpl::communicator init;
    // WRONG: init = mpl::environment::comm_world();
    // error: overload resolution selected deleted operator '='
  }

  auto eq = comm.compare(copy);
  cout << static_cast<int>(eq) << endl;

  return EXIT_SUCCESS;
}

