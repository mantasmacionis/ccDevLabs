/**
 * @file mandelbroit.cpp
 * @brief iterative mandelbrot algorithm.
 * @author Mantas Macionis
 * @date november-2023
 * @see https://github.com/mantasmacionis/ccDevLabs/
 * @license Creative Commons Attribution-NonCommercial-ShareAlike 4.0
 */
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <complex>      /* complex number data type */
#include <time.h>       /* time */
#include <limits>

using namespace std ;

const int ROW=1000;
const int COL=1000;
const int DEPTH=10;

/**
 * @brief Calculate the Mandelbrot value for a given complex number.
 *
 * Applying the Mandelbrot iteration for the specified depth to determine
 * the number of iterations before the escape condition is met.
 *
 * @param c The complex number for which the Mandelbrot value is calculated.
 * @param depth The maximum number of iterations to perform.
 * @return The number of iterations before the escape condition is met.
 */
int calc(complex<int> c, int depth){
    int count=0;
    complex<int> z=0;
    for(int i=0;i<depth;++i){
	if (abs(z)>2.0){
            break;
	}
	z=z*z+c;
	count++;
    }
    return count;
}

/**
 * @brief Generate the Mandelbrot set and store the results in a 2D array.
 *
 * @param p The 2D array to store Mandelbrot values.
 * @param depth The maximum number of iterations for Mandelbrot calculations.
 */
void mandel( int p[ROW][COL], int depth){
  #pragma omp parallel for collapse(2)	  
  for(int i=0;i<ROW;++i){
        for(int k=0;k<COL;++k){
	  p[i][k]=calc(complex<int>(i,k),depth);
	}
    }
}

/**
 * @brief Entry point of the program to generate the Mandelbrot set.
 *
 * Initialise necessary variables, generate the Mandelbrot
 * set using the 'mandel' function, measure the time taken, and output the
 * elapsed time to the console.
 *
 * @return 0 for successful execution.
 */
int main(void){

  
  int myArray[ROW][COL];
  /* initialize random seed: */
  srand (time(NULL));
  
  clock_t begin = clock();
  mandel(myArray,DEPTH);
  clock_t end = clock();
  double timeSec = (end - begin) / static_cast<double>( CLOCKS_PER_SEC );
  std::cout << timeSec << std::endl;
}
