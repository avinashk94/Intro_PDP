#include <stdio.h>
#include "file1.hpp"



int hello(){
  mykernel<<<1,1>>>();
  cudaDeviceSynchronize();
  return 0;
}
