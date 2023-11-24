/**
 * @file stencil.cpp
 * @brief stencil operation.
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

//array dimension
const int DIM=1000;
const int SIZE=4;

/**
 * @brief Calculate the neighboring elements of a specified index in a vector.
 *
 * This function extracts neighboring elements of the specified index 'index' from
 * the input vector 'in' and stores them in the output vector 'out'. The number of
 * neighboring elements is determined by the size of the 'out' vector.
 *
 * @param in The input vector from which neighbors are extracted.
 * @param index The index for which neighbors are calculated.
 * @param out The output vector to store the neighboring elements.
 * @return Always returns 1.
 */
int calcNeighbours(vector<float> const  &in, int index, vector<float>& out){
  int amount=out.size();
  for(int i=0;i<out.size();++i){//put neighbours of in[i] into out vector
    int k=i-amount/2;
    if (k<0){//wrap k around size of in vector
      k=in.size()+k;
    }else if (k>=in.size()){
      k=k-in.size();
    }
    out[i]=in[k];
  }
  return 1;
}

/**
 * @brief Apply a stencil operation on each element of an input vector.
 *
 * @param in The input vector on which the stencil operation is applied.
 * @param out The output vector to store the results of the stencil operation.
 * @param f The function object representing the stencil operation.
 * @param size The size of the neighborhood used for the stencil operation.
 */
void stencil(vector<float> const &in, vector<float> &out,
	     function <float(vector<float>) > f,int size){
#pragma openmp parallel for
  for (int i=0; i < in.size(); ++i){
    vector<float> neighbours(size);
    calcNeighbours(in,i,neighbours);
    out[i]=f(neighbours);
  }
}



/**
 * @brief Calculate the average of values in a vector.
 *
 * This function calculates the average of the values in the input vector
 * 'currentValues' and returns the result.
 *
 * @param currentValues The vector containing values for which the average is calculated.
 * @return The average value of the elements in the input vector.
 */
float getNewValue(vector<float> currentValues){
  float average=0.0;
  float total=0.0;
  for(auto const& value: currentValues){
    total+=value;
  }
  return total/currentValues.size();
}

/**
 * @brief Entry point of the program to demonstrate a stencil operation.
 *
 * This function initializes two vectors 'first' and 'second', performs a stencil
 * operation on 'first' using the function 'getNewValue', and prints the sum of
 * values in both vectors before and after the stencil operation.
 *
 * @return 0 on successful execution.
 */
int main(void){
  vector<float> first(DIM), second(DIM);
  //initilise vectors
  srand (time(NULL));
   
   // Initialize 'first' vector with random values between 0 and 1
  for(auto& value: first) {
    value=(float)rand() / ((float)(RAND_MAX)+(float)(1));
  }
  // Initialize 'second' vector with zeros
  for(auto it=second.begin(); it<second.end();++it){
    *it=0.0f;
  }
  // Calculate and print the sum of values in the 'first' vector
  float sum=0.0f;
  for(auto const&value: first){
    sum+=value;
  }
  cout << sum <<endl;
  // Perform stencil operation on 'first' and store results in 'second'
  stencil(first,second,getNewValue,SIZE);
  sum=0.0f;
  for(auto const&value: second){
    sum+=value;
  }
  cout << sum <<endl;
  return 0;
}
// 
// stencil.cpp ends here
