/**
 * @file quicksort.cpp
 * @brief parallelized quicksort algorithm.
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

using namespace std ;


const int LENGTH=2000;

/**
 * @brief Partition a vector based on the QuickSort algorithm.
 *
 * This function partitions a vector 'myArray' between indices 'low' and 'high'
 * using the QuickSort algorithm. It chooses the pivot element as the last element
 * (index 'high') and rearranges the elements such that elements smaller than the
 * pivot are on the left, and elements greater than the pivot are on the right.
 *
 * @param myArray The vector to be partitioned.
 * @param low The lower index of the partition.
 * @param high The higher index of the partition.
 * @return The index of the pivot after partitioning.
 */
int partition (vector<int>& myArray , int low , int high ){
  int pivot=myArray[high];
  int k=high;
  int i=low;
  int temp=0;
  while (i<k){
    while (myArray[i]<pivot && i<k)++i;
    while (myArray[k]>pivot && i<k)--k;
    if (i<k){
      temp=myArray[i];
      myArray[i]=myArray[k];
      myArray[k]=temp;
      i++;//do not decrement k here OR ELSE!!
    }
  }
  return i-1;
}
  
/**
 * @brief Perform parallelized QuickSort on a vector within a specified range.
 *
 * The sorting is performed within the specified
 * range defined by the indices 'low' and 'high'. Parallelization is achieved using
 * OpenMP tasks, and a recursive approach is taken to sort subarrays.
 *
 * @param myArray The vector to be sorted.
 * @param low The lower index of the range to be sorted.
 * @param high The higher index of the range to be sorted.
 * @return Always returns 1.
 */
int quicksort(vector<int>& myArray , int low , int high ){
  if (low<high){
    int pivot=partition(myArray,low,high);
    //really we should only do this if each partition is above a certain size (1000 elements?)
    //otherwise the overhead outweighs any gains from using threads
    #pragma omp task shared(myArray)
    quicksort(myArray,low,pivot);
    quicksort(myArray,pivot+1,high);
    #pragma omp taskwait
  return 1;
  }
}//quicksort


/**
 * @brief main method of the program to demonstrate parallelized QuickSort on a vector.
 *
 * This function initializes a vector 'data' with random values, prints the initial
 * unsorted vector, performs parallelized QuickSort on it, and then prints the sorted vector.
 *
 * @return 0 on successful execution.
 */
int main(void){
  srand (time(NULL)); /**< Seed the random number generator */
    // Generate a vector 'data' with random values
  vector<int> data(LENGTH);
  for(auto& value:data){
    value=rand()%1000;
  }
 
  for(auto& value:data){
    cout<<value<<" ";
  }
   // Print the initial unsorted vector
  cout << endl<<"*******************************"<<endl;
  quicksort(data,0,data.size()-1);
  for(auto& value:data){
    cout<<value<<" ";
  }
  cout << endl;
}
// 
// quicksort.cpp ends here
