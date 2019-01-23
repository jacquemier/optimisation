#include <iostream>
#include "get_cycles.h"

using namespace std;

#include <immintrin.h>

#define NUMBER_OF_REPETITION 50000lu
#define NB_LINE 1000lu
#define NB_COL 100lu


/* AVX 2 has 256-bit register size
float if 4 bytes / 32 bits size
So we can use 8 elements (float)
*/
#define AVX2_VECTOR_SIZE_FLOAT 8

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


void intrinsic_vect_add_unloop( float *array_result, float* array_a, float* array_b){
    // Get number of vectoriel register in the array
    long unsigned int nbVect = NB_LINE*NB_COL/AVX2_VECTOR_SIZE_FLOAT;

    __m256 reg_vec_a; // taille en bit;
    __m256 reg_vec_b; // taille en bit;
    __m256 reg_vec_c; // taille en bit;
    __m256 reg_vec_d; // taille en bit;
    __m256 reg_vec_sum_a;
    __m256 reg_vec_sum_b;
    __m256 reg_vec_sum;
    register long unsigned int shift;

    for (size_t i(0lu); i<nbVect/2; ++i){
        // Compute add on 8 float thanks to intrinsic vectorized addition
        // (packed addition => _mm256_add_ps )
        shift = AVX2_VECTOR_SIZE_FLOAT*(i*2);
        reg_vec_a = _mm256_load_ps(array_a + shift); // taille en bit;
        reg_vec_b = _mm256_load_ps(array_b + shift) ; // taille en bit;
        reg_vec_sum_a = _mm256_add_ps(reg_vec_a, reg_vec_b);
        _mm256_store_ps(array_result + shift, reg_vec_sum_a);

        shift = AVX2_VECTOR_SIZE_FLOAT*(i*2+1);
        reg_vec_c = _mm256_load_ps(array_a + shift); // taille en bit;
        reg_vec_d = _mm256_load_ps(array_b + shift) ; // taille en bit;
        reg_vec_sum_b = _mm256_add_ps(reg_vec_c, reg_vec_d);
        _mm256_store_ps(array_result + shift, reg_vec_sum_b);

    }
}

typedef void (*callback_function)(float* array_a, float* array_b, float
*array_result); // type for conciseness

//callback_function bench; // variable to store function pointer type
double bench(callback_function pFunc, float* result, float* array_a, float*
array_b, bool verbose = 0);

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

int main(){

  float result [NB_COL * NB_LINE] __attribute__ ((aligned (32)));
  float array_a[NB_COL * NB_LINE]   __attribute__ ((aligned (32)));
  float array_b[NB_COL * NB_LINE]   __attribute__ ((aligned (32)));

  //callback_function intrinsic_vect_add;
  double ellapsedTime = ellapsedTime  = bench(intrinsic_vect_add, result,
  array_a, array_b);
  std::cout << "intrisit_add= " << ellapsedTime << " cycles by access "  <<
  endl;

  ellapsedTime =bench(intrinsic_vect_add_unloop, result, array_a, array_b);
  std::cout << "intracit add + unloop 4 register = " << ellapsedTime << " cycles by access "  << endl;

  ellapsedTime =bench(fast, result, array_a, array_b);(result, array_a,
  array_b);
  std::cout << "line the col= " << ellapsedTime << " cycles by access "  <<
  endl;

  /*
  ellapsedTime =bench(slow, result, array_a, array_b);
  std::cout << "col then line= " << ellapsedTime << " cycles by access "  <<
  endl;
  */
  return 0;

}

