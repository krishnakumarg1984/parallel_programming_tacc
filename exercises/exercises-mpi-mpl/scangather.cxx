/****************************************************************
 ****
 **** This program file is part of the book 
 **** `Parallel programming with MPI and OpenMP'
 **** by Victor Eijkhout, eijkhout@tacc.utexas.edu
 ****
 **** copyright Victor Eijkhout 2012-2021
 ****
 **** MPI Exercise for the use of Scan/Exscan
 ****
 ****************************************************************/

#include <iostream>
#include <iomanip>
#include <sstream>
#include <random>
using namespace std;
#include <mpl/mpl.hpp>

#define max(a,b) ( (a)>(b) ? (a) : (b) )

int main(int argc,char **argv) {

  const mpl::communicator &comm_world = mpl::environment::comm_world();
  int nprocs,procno;
  // compute communicator rank and size
  nprocs = comm_world.size();
  procno = comm_world.rank();

  // set the default random number generator
  random_device r;
  default_random_engine generator{ r() };
  // distribution: int between 0 and nprocs
  uniform_int_distribution<int> distribution(0,nprocs);

  /*
   * How many elements do I have locally?
   * Allocate space.
   */
  int
    my_number_of_elements = distribution(generator),
    my_first_index=0;
  /*
   * Exercise:
   * - determine the index of your first element.
   *   Which routine do you use here?
   */
/**** your code here ****/
    (mpl::plus<int>(),
     my_number_of_elements,my_first_index);
  {
    stringstream proctext;
    proctext << "Proc " << setw(3) << procno
             << " has " << setw(3) << my_number_of_elements
             << " elements, range [" << setw(4) << my_first_index
             << "," << setw(4) << my_first_index+my_number_of_elements
             << ")";
    cout << proctext.str() << endl;
  }
  
  /*
   * Create a local array of size `my_number_of_elements'
   * Fill in this local array
   */
  int total_number_of_elements;
  vector<int> my_elements( max(my_number_of_elements,1) );
  for (int i_element=0; i_element<my_number_of_elements; i_element++)
    my_elements.at(i_element) = my_first_index+i_element;

  comm_world.reduce( mpl::plus<int>(),0,
		     my_number_of_elements,total_number_of_elements );
  if (procno==0) {
    stringstream proctext;
    proctext << "Total number of elements: " << total_number_of_elements;
    cout << proctext.str() << endl;
  }

  /*
   * Gather all local arrays into one global
   */
  // how many elements from each process?
  if (procno==0) {
    vector<int> size_buffer(nprocs);
    comm_world.gather
      ( 0,my_number_of_elements,size_buffer.data() );
  } else {
    comm_world.gather
      ( 0,my_number_of_elements );
  }

  // // where are they going to go in the big buffer?
  // vector<int> displ_buffer;
  // if (procno==0)
  //   displ_buffer = vector<int>(nprocs);
  // comm_world.gather
  //   ( 0,my_first_index,displ_buffer.data() );

  /*
   * Use Gatherv to collect the small buffers into a big one
   */
  if (procno==0) {
    vector<int> size_buffer(nprocs);
    comm_world.gather
      ( 0,my_number_of_elements,size_buffer.data() );
    {
      stringstream proctext;
      proctext << "Number of elements:";
      for ( int ip=0; ip<nprocs; ip++ )
	proctext << " " << size_buffer.at(ip);
      cout << proctext.str() << endl;
    }

    // now create the big buffer
    vector<int> gather_buffer( total_number_of_elements );

    mpl::layouts<int> receive_layout;
    for ( int iproc=0,loc=0; iproc<nprocs; iproc++ ) {
      auto siz = size_buffer.at(iproc);
      receive_layout.push_back
	( mpl::indexed_layout<int>( {{ siz,loc }} ) );
      loc += siz;
    }

    comm_world.gatherv
      ( 0,my_elements.data(),mpl::contiguous_layout<int>(my_number_of_elements),
	gather_buffer.data(),receive_layout );

    /*
     * Print the gathered material
     */
    {
      stringstream proctext;
      proctext << "Gathered:";
      for (int i_element=0; i_element<total_number_of_elements; i_element++)
	proctext << " " << gather_buffer[i_element];
      cout << proctext.str() << endl;
    }

  } else {
    comm_world.gather
      ( 0,my_number_of_elements );

    comm_world.gatherv
      ( 0,my_elements.data(),mpl::contiguous_layout<int>(my_number_of_elements) );
  }

  return 0;
}
