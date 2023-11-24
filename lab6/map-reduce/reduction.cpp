/**
 * @file reduction.cpp
 * @brief getting the average of elements in a vector.
 * @author Mantas Macionis
 * @date november-2023
 * @see https://github.com/mantasmacionis/ccDevLabs/
 * @license Creative Commons Attribution-NonCommercial-ShareAlike 4.0
 */

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <complex>      /* complex number data type */
#include <time.h>       /* time */
#include <functional>  /* function type */
#include <limits>
#include <vector>      /* vectors used instead of arrays */
#include <omp.h>
using namespace std ;


const int LENGTH=2000;
int NumThreads=1;


///! Find out how many threads are running!
/**
 * @brief Get the number of threads currently running in parallel.
 *
 * This function uses OpenMP to determine the number of threads currently active
 * within the parallel region.
 *
 * @return The number of threads currently running in the parallel region.
 */
int get_num_threads(void) {
    int num_threads = 1;
    //must ask in parallel region otherwise 1 is returned
    #pragma omp parallel
    {
        #pragma omp single
        num_threads = omp_get_num_threads();
    }
    return num_threads;
}

/**
 * @brief Calculate the sum of elements in a vector using a serial method.
 *
 * This function iterates through each element in the input vector 'data' and
 * calculates the sum using a serial approach.
 *
 * @param data The vector containing integer values for which the sum is calculated.
 * @return The sum of all elements in the vector.
 */
float getSerialSum(vector<int> data){
  float sum=0.0;
  for(auto& value:data){
    sum+=value;
  }
  return sum;
}

/**
 * @brief Calculate the sum of elements in a vector using parallelization.
 *
 * @param data The vector containing integer values for which the sum is calculated.
 * @return The sum of all elements in the vector, computed in parallel.
 */
float getParallelSum(vector<int> data){
  float sum=0.0;
#pragma omp parallel for reduction(+:sum)
  for(int i=0;i<data.size();++i){
    sum+=data[i];
  }
  return sum;
}


/**
 * @brief Calculate the sum of elements in a vector using tiled parallelization.
 *
 * using OpenMP. The workload is distributed among threads in
 * the map step, and the partial results are aggregated in the reduce step.
 *
 * @param data The vector containing integer values for which the sum is calculated.
 * @return The sum of all elements in the vector, computed using tiled parallelization.
 */
float getTiledParallelsum(vector<int> data){
  float result =0.0;
  NumThreads=get_num_threads();
  float tileResult[NumThreads];
  for(int i=0;i<NumThreads;++i) tileResult[i]=0.0;
  //map step here
#pragma omp parallel for 
  for (int i=0; i < data.size(); ++i ){
    int tid = omp_get_thread_num();
    tileResult[tid] =tileResult[tid]+data[i];
  }
  //reude step here
  for (int i=0; i < NumThreads ; ++i ){
    std::cout << i<< ":"<< tileResult[i] << "- ";
    result+=tileResult[i];
  }
  std::cout <<std::endl;
  return result ;
}


/**
 * @brief Entry point of the program for calculating averages using different methods.
 *
 * This function initializes variables, generates a vector with random values,
 * and calculates the average using serial, parallel, and tiled parallel methods.
 * The results are printed to the console.
 *
 * @return 0 on successful execution.
 */
int main(void){
  float sum=0.0;
  int average=0;
  NumThreads=omp_get_num_threads();
  srand (time(NULL));
  vector<int> data(1000);
  for(auto& value:data){
    value=10;//rand()%1000;
  }

 // Calculate and print the average using serial computation
  sum=getSerialSum(data);
  average=sum/data.size();
  cout <<"Serial Average is: "<<average<<endl;
   // Calculate and print the average using parallel computation
  sum=getParallelSum(data);
  average=sum/data.size();
  cout <<"Parallel Average is: "<<average<<endl;
  cout << endl;
  // Calculate and print the average using tiled parallel computation
  sum=getTiledParallelsum(data);
  average=sum/data.size();
  cout <<"Parallel Average is: "<<average<<endl;
  cout << endl;
}
// 
// reduction.cpp ends here
