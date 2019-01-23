#ifndef BENCH__HH
#define BENCH__HH

#define NUMBER_OF_REPETITION 50000lu
#define NB_LINE 1000lu
#define NB_COL 100lu


/* AVX 2 has 256-bit register size
float if 4 bytes / 32 bits size
So we can use 8 elements (float)
*/
#define AVX2_VECTOR_SIZE_FLOAT 8

void fast(float* result, float* array_a, float* array_b);
void slow(float* result, float* array_a, float* array_b);
void intrinsic_vect_add( float *array_result, float* array_a, float* array_b);
void intrinsic_vect_add_unloop( float *array_result, float* array_a, float*
array_b);
typedef void (*callback_function)(float* array_a, float* array_b, float
*array_result); // type for conciseness
double bench(callback_function pFunc, float* result, float* array_a, float*
array_b, bool verbose = 0);

#endif