#ifndef BENCH__HH
#define BENCH__HH

#define NUMBER_OF_REPETITION 50000000lu
#define NB_LINE 100lu
#define NB_COL 10lu

// CACHE L1 32 kBytes -> entre 1000 et 2660 elemnets
//32 kBytes / 4 (float) / 3 (C_Array)
//32 kBytes / 4 (float) / 3 (C_Array)

/* AVX 2 has 256-bit register size
float if 4 bytes / 32 bits size
So we can use 8 elements (float)
*/
#define AVX2_VECTOR_SIZE_FLOAT 8

void fast(float* result, float* array_a, float* array_b);
void fast_align(float* result, float* array_a, float* array_b);
void slow(float* result, float* array_a, float* array_b);
void intrinsic_vect_add( float *array_result, float* array_a, float* array_b);
void intrinsic_vect_add_unrool( float *array_result, float* array_a, float*
array_b);
typedef void (*callback_function)(float* array_a, float* array_b, float
*array_result); // type for conciseness
double bench(callback_function pFunc, float* result, float* array_a, float*
array_b, bool verbose = 0);

#endif