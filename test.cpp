#include "bench.h"
#include "assert.h"
#include <iostream>


int main(){
 float result [NB_COL * NB_LINE] __attribute__ ((aligned (32)));
 float array_a[NB_COL * NB_LINE]   __attribute__ ((aligned (32)));
 float array_b[NB_COL * NB_LINE]   __attribute__ ((aligned (32)));
 for (size_t i(0lu); i<NB_LINE * NB_COL; ++i){
        result[i] = 0;
        array_a[i]=i;
        array_b[i]=i+i/2;
 }
 //std::cout <<  result [NB_COL * NB_LINE-1]  << std::endl;
 //callback_function intrinsic_vect_add;
 intrinsic_vect_add( result, array_a, array_b);
 assert ( result [NB_COL * NB_LINE-1] == 249997 );
 for (size_t i(0lu); i<NB_LINE * NB_COL; ++i){
        result[i] = 0;
        array_a[i]=i;
        array_b[i]=i+i/2;
  }

 intrinsic_vect_add_unloop( result, array_a, array_b);
 assert ( result [NB_COL * NB_LINE-1] == 249997 );
 for (size_t i(0lu); i<NB_LINE * NB_COL; ++i){
        result[i] = 0;
        array_a[i]=i;
        array_b[i]=i+i/2;
  }

  fast( result, array_a, array_b);
  assert ( result [NB_COL * NB_LINE-1] == 249997 );

  for (size_t i(0lu); i<NB_LINE * NB_COL; ++i){
        result[i] = 0;
        array_a[i]=i;
        array_b[i]=i+i/2;
  }
  slow( result, array_a, array_b);
  assert ( result [NB_COL * NB_LINE-1] == 249997 );



  return 0;
}