#include <stdio.h>

__global__
void mykernel(){
  printf("Hello from mykernel\n");
}

int hello(){
  mykernel<<<1,1>>>();
  cudaDeviceSynchronize();
  return 0;
}
