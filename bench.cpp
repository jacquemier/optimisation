#include <iostream>
#include "get_cycles.h"
#include "bench.h"

using namespace std;

#include <immintrin.h>


void fast(float* result, float* array_a, float* array_b)
{ // Fast because the program is hitting element in memory  order.

  for (size_t i=0; i < NB_LINE; i++)
  {
    for (size_t j=0; j < NB_COL; j++)
    {
      result [i*NB_COL + j] =  array_a[i * NB_COL +j] + array_b[i *NB_COL + j] ;
    }
  }
}


void fast_align(float* __restrict__ result, float* __restrict__ array_a, 
float* __restrict__ array_b)
{ // Fast because the program is hitting element in memory  order.

  for (size_t i=0; i < NB_LINE; i++)
  {
    for (size_t j=0; j < NB_COL; j++)
    {
      result [i*NB_COL + j] =  array_a[i * NB_COL +j] + array_b[i *NB_COL + j] ;
    }
  }
}


void slow(float* result, float* array_a, float* array_b)
{ // Slow because the program does not hit element in memory  order.

  for (size_t i=0; i < NB_COL; i++)
  {
    for (size_t j=0; j < NB_LINE; j++)
    {
      result [i + NB_COL*j] =  array_a[i+ NB_COL*j] + array_b[i+ NB_COL*j] ;
    }
  }
}


void intrinsic_vect_add( float *array_result, float* array_a, float* array_b){
    // Get number of vectoriel register in the array
    long unsigned int nbVect = NB_LINE*NB_COL/AVX2_VECTOR_SIZE_FLOAT;

    __m256 reg_vec_a; // taille en bit;
    __m256 reg_vec_b; // taille en bit;
    __m256 reg_vec_sum;
    register long unsigned int shift;

    for (size_t i(0lu); i<nbVect; ++i){
        // Compute add on 8 float thanks to intrinsic vectorized addition
        // (packed addition => _mm256_add_ps )
        shift = AVX2_VECTOR_SIZE_FLOAT*i;
        reg_vec_a = _mm256_load_ps(array_a + shift); // taille en bit;
        reg_vec_b = _mm256_load_ps(array_b + shift) ; // taille en bit;
        reg_vec_sum = _mm256_add_ps(reg_vec_a, reg_vec_b);
        _mm256_store_ps(array_result + shift, reg_vec_sum);
    }
}


void intrinsic_vect_add_unrool( float *array_result, float* array_a, float* array_b){
    // Get number of vectoriel register in the array
    long unsigned int nbVect = NB_LINE*NB_COL/AVX2_VECTOR_SIZE_FLOAT;
    // By doing two times less of loop, we optimize by using less the Branch predictor

    __m256 reg_vec_a; // 256 -> taille en bit;
    __m256 reg_vec_b;
    __m256 reg_vec_sum;
    register long unsigned int shift;

    for (size_t i(0lu); i<nbVect/2; ++i){
        // Compute add on 8 float thanks to intrinsic vectorized addition
        // (packed addition => _mm256_add_ps )
        shift = AVX2_VECTOR_SIZE_FLOAT*(i*2);
        reg_vec_a = _mm256_load_ps(array_a + shift); // taille en bit;
        reg_vec_b = _mm256_load_ps(array_b + shift) ; // taille en bit;
        reg_vec_sum = _mm256_add_ps(reg_vec_a, reg_vec_b);
        _mm256_store_ps(array_result + shift, reg_vec_sum);

        shift = AVX2_VECTOR_SIZE_FLOAT*(i*2+1);
        reg_vec_a = _mm256_load_ps(array_a + shift); // taille en bit;
        reg_vec_b = _mm256_load_ps(array_b + shift) ; // taille en bit;
        reg_vec_sum = _mm256_add_ps(reg_vec_a, reg_vec_b);
        _mm256_store_ps(array_result + shift, reg_vec_sum);


    }
}

typedef void (*callback_function)(float* array_a, float* array_b, float
*array_result); // type for conciseness



double bench(callback_function pFunc, float* result, float* array_a, float*
array_b, bool verbose){
/* Retrun ellapsedTime  */

    for (size_t i(0lu); i<NB_LINE * NB_COL; ++i){
        result[i] = 0;
        array_a[i]=1;
        array_b[i]=2;
    }
    if (verbose == 1) {
        cout << "--------START-------\n" << endl;
        cout << "BEFORE: result[0] = " << result[0] <<  ", result[-1] =" << result[NB_LINE * NB_COL -1] << std::endl;
    }
    size_t total_nb_elem = NB_LINE * NB_COL;
    uint64_t beginTime=rdtsc();
    for (int i=0; i < NUMBER_OF_REPETITION; i++)
        pFunc(result, array_a, array_b);
    uint64_t endTime=rdtsc();
    double ellapsedTime = (endTime - beginTime)/(total_nb_elem*(double)
    NUMBER_OF_REPETITION);
    if (verbose == 1) {
        cout << "AFTER  : result[0] = " << result[0] <<  ", result[-1] =" << result[NB_LINE * NB_COL -10] << std::endl;
        cout << "\n--------END-------\n\n\n" << endl;
    }
    return ellapsedTime;
}
