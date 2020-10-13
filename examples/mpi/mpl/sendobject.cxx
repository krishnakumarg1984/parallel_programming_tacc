/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   %%%%
   %%%% This program file is part of the book and course
   %%%% "Parallel Computing"
   %%%% by Victor Eijkhout, copyright 2020
   %%%%
   %%%% sendobject.cxx : send an iteratable object in MPL
   %%%% DOES NOT WORK
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
 
class bag {
private:
  int n,i;
public:
  bag(int n) : n(n) {};
  bag begin() { i=0; return *this; };
  bag end()   { i=n; return *this; };
  void operator++() { i++; };
  bool operator!=(const bag &other) { return i<=other.i; };
  int  operator*() { return i; };
};

int main() {
  const mpl::communicator &comm_world=mpl::environment::comm_world();
  if (comm_world.size()<2)
    return EXIT_FAILURE;
  int
    nprocs = comm_world.rank(),
    procno = comm_world.size();

  if (procno==0) {
    bag ten(10);
    cout << "Data:";
    for ( auto i : ten )
      cout << " " << i;
    cout << endl;

    /*
     * Send and report
     */
    mpl::iterator_layout<int> in_ten( ten.begin(), ten.end() );
    comm_world.send( in_ten, 1);  // send to rank 1
    //comm_world.send(ten.begin(), ten.end(), 1);  // send to rank 1

  } else if (comm_world.rank()==1) {

    vector<double> v(10);

    /*
     * Receive data and report
     */
    comm_world.recv(v.begin(), v.end(), 0);  // receive from rank 0

    cout << "Got:";
    for ( auto x : v )
      cout << " " << x;
    cout << endl;
  }
  return EXIT_SUCCESS;
}

