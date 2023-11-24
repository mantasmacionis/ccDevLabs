/**
 * @file saxpy.cpp
 * @brief scalar multiplication and vector addition.
 * @author Mantas Macionis
 * @date november-2023
 * @see https://github.com/mantasmacionis/ccDevLabs/
 * @license Creative Commons Attribution-NonCommercial-ShareAlike 4.0
 */
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <limits>

/**
 * @brief Perform SAXPY operation in parallel.
 *
 * @param n The size of the vectors.
 * @param a The scalar multiplier.
 * @param y The output vector, modified in place.
 * @param x The input vector.
 */
void saxpy(unsigned long n, float a,float y[], float x[])
{
#pragma omp parallel for
	for (unsigned long i=0; i < n; ++i)
	{
		y[i]=a * x[i] + y[i];
	}
}

/**
 * @brief Entry point of the program for the SAXPY operation.
 *
 * This function initializes vectors, 'x' and 'y', with random values and performs
 * the SAXPY operation on them using a scalar multiplier 'A'. The size of the vectors
 * is defined by the constant 'size'.
 *
 * @return 0 on successful execution.
 */
int main(void)
{
  const unsigned long size=1000000;
  const float A=1.234;
  
  float y[size];
  float x[size];
  /* initialize random seed: */
  srand (time(NULL));
  


  for(unsigned long long int i=0;i<size;++i){
    y[i]=i*i;
    /* generate secret number between 1 and 1000000: */
    x[i] = rand() % 1000000 + 1;
  }
  /**
 * @brief Measure the execution time of the SAXPY operation.
 *
 * @param size The size of the vectors 'x' and 'y'.
 * @param A The scalar multiplier for the SAXPY operation.
 * @param y The output vector modified in place.
 * @param x The input vector.
 */
  clock_t begin = clock();
  saxpy(size,A,y,x);
  clock_t end = clock();
  double timeSec = (end - begin) / static_cast<double>( CLOCKS_PER_SEC );
  std::cout << timeSec << std::endl;
}

// 
// saxpy.cpp ends here
