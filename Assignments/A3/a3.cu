#include <stdio.h>

__global__ void mykernel(){
  printf("Hello from mykernel\n");
}

void hello(){
  mykernel<<<1,1>>>();
  cudaDeviceSynchronize();
}
