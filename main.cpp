#include "bench.h"
#include <iostream>
using namespace std;


int main(){

  float result [NB_COL * NB_LINE] __attribute__ ((aligned (32)));
  float array_a[NB_COL * NB_LINE]   __attribute__ ((aligned (32)));
  float array_b[NB_COL * NB_LINE]   __attribute__ ((aligned (32)));

  //callback_function intrinsic_vect_add;
  double ellapsedTime = bench(intrinsic_vect_add_unloop, result,
  array_a, array_b);
  std::cout << "intrisit_add + unloop 4 register=" << ellapsedTime << " cycles by access "  <<endl;

  ellapsedTime =bench(intrinsic_vect_add, result, array_a, array_b);
  std::cout << "intracit add                    =" << ellapsedTime << "cycles by access "  << endl;

  ellapsedTime =bench(fast, result, array_a, array_b);(result, array_a,
  array_b);
  std::cout << "line the col                    =" << ellapsedTime << " cyclesby access "  <<endl;

  /*
  ellapsedTime =bench(slow, result, array_a, array_b);
  std::cout << "col then line= " << ellapsedTime << " cycles by access "  <<
  endl;
  */
  return 0;

}

