#include <iostream>
#include "get_cycles.h"

using namespace std;

#include <immintrin.h>

#define NUMBER_OF_REPETITION 10000lu
#define NB_LINE 1000lu
#define NB_COL 100lu


void fast(float* result, float* array_a, float* array_b, size_t nbLine, size_t
nbCol)
{ // Fast because the program is hitting element in memory  order.

  for (size_t i=0; i < nbLine; i++)
  {
    for (size_t j=0; j < nbCol; j++)
    {
      result [i*nbCol + j] =  array_a[i * nbCol +j] + array_b[i *nbCol + j] ;
    }
  }

}

void slow(float* result, float* array_a, float* array_b, size_t nbLine, size_t
nbCol)
{ // Slow because the program does not hit element in memory  order.

  for (size_t i=0; i < nbCol; i++)
  {
    for (size_t j=0; j < nbLine; j++)
    {
      result [i + nbCol*j] =  array_a[i+ nbCol*j] + array_b[i+ nbCol*j] ;
    }
  }
}

#define PLIB_VECTOR_SIZE_FLOAT 8

void vector(float* array_a, float* array_b, float *array_result){
    // Get number of vectoriel register in the array
    long unsigned int nbVect = NB_LINE*NB_COL/PLIB_VECTOR_SIZE_FLOAT;

    for (size_t i(0lu); i<nbVect; ++i){
        register long unsigned int shift = PLIB_VECTOR_SIZE_FLOAT*i;
        __m256 reg_vec_a = _mm256_load_ps(array_a + shift); // taille en bit;
        __m256 reg_vec_b = _mm256_load_ps(array_b + shift) ; // taille en bit;
        __m256 reg_vec_sum = _mm256_add_ps(reg_vec_a, reg_vec_b);
        _mm256_store_ps(array_result + shift, reg_vec_sum);
    }
}


int main(){
  float result [NB_COL * NB_LINE] __attribute__ ((aligned (32)));
  float array_a[NB_COL * NB_LINE]   __attribute__ ((aligned (32)));
  float array_b[NB_COL * NB_LINE]   __attribute__ ((aligned (32)));

  for (size_t i(0lu); i<NB_LINE * NB_COL; ++i){
    result[i] = 0;
    array_a[i]=1;
    array_b[i]=2;
  }
  std::cout << "result[0] = " << result[0] <<  ", result[-1] =" << result[NB_LINE * NB_COL -10] << std::endl;


  size_t total_nb_elem = NB_LINE * NB_COL;
  uint64_t beginTime(rdtsc());

  for (int i=0; i < NUMBER_OF_REPETITION; i++)
    vector(array_a, array_b, result);
  uint64_t endTime(rdtsc());
  double ellapsedTime = (endTime - beginTime)/(total_nb_elem*(double)NUMBER_OF_REPETITION);

  cout << "intrinsic: " << ellapsedTime << " cycles by access " << endl;
  for (size_t i(0lu); i<NB_LINE * NB_COL; ++i){
    result[i] = 0;
    array_a[i]=1;
    array_b[i]=2;
  }
  beginTime=rdtsc();
  for (int i=0; i < NUMBER_OF_REPETITION; i++)
    fast(result, array_a, array_b, NB_LINE, NB_COL );
  endTime=rdtsc();
  ellapsedTime = (endTime - beginTime)/(total_nb_elem*(double)NUMBER_OF_REPETITION);
  cout << "fast= " << ellapsedTime << " cycles by access "  << endl;

  for (size_t i(0lu); i<NB_LINE * NB_COL; ++i){
    result[i] = 0;
    array_a[i]=1;
    array_b[i]=2;
  }

  beginTime=rdtsc();
  for (int i=0; i < NUMBER_OF_REPETITION; i++)
    slow(result, array_a, array_b, NB_LINE, NB_COL);
  endTime=rdtsc();
  ellapsedTime = (endTime - beginTime)/(total_nb_elem*(double)NUMBER_OF_REPETITION);
  cout << "slow= " << ellapsedTime << " cycles by access "  << endl;

  return 0;

}

