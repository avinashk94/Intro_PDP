/*  AVINASH
 *  KOMMINENI
 *  akommine
 */

#ifndef A3_HPP
#define A3_HPP
#include <math.h>

using namespace std;

__global__
void evaluate(float *x, float *y, int n, float h){
   int i = blockIdx.x*blockDim.x + threadIdx.x;
    if(i<n) y[i] = x[i];

}

void gaussian_kde(int n, float h, const std::vector<float>& x, std::vector<float>& y) {

    float *d_x,*d_y;
    int m = 16;

    int size = n*sizeof(float);

    cudaMalloc(&d_x, n*sizeof(float));
    cudaMalloc(&d_y, n*sizeof(float));

    cudaMemcpy(d_x, &x, size , cudaMemcpyHostToDevice);

    dim3 dimGrid((int)ceil(n/m), (int)ceil(n/m));
    dim3 dimBlock(m,m);

    evaluate<<<dimGrid, dimBlock>>>(d_x, d_y, n, h);

    cudaMemcpy(&y, d_y, size , cudaMemcpyDeviceToHost);

    for(int i =0;i<n;i++) cout<<y[i]<<"\n";

    cudaFree(d_x);
    cudaFree(d_y);

} // gaussian_kde

#endif // A3_HPP

// void gaussian_kde(int n, float h, const std::vector<float>& x, std::vector<float>& y) {
//     printf("Hello....\n");
//     int m = 32;
//
//     float *deviceX, *deviceY;
//
//     int size = n*sizeof(float);
//
//     cudaMalloc(&deviceX, size);
//     cudaMalloc(&deviceY, size);
//
//     cudaMemcpy(deviceX, &x, size, cudaMemcpyHostToDevice);
//
//     evaluate<<<(int)ceil(n/m),m>>>(deviceX, deviceY,n,h);
//
//     cudaMemcpy(&y, deviceY, size, cudaMemcpyDeviceToHost);
//
//     printf("End!!!!!!!!!\n");
//     for (int i = 0; i < 5; i++) {
//         cout<<x[i]<<"\t"<<y[i]<<endl;
//     }
// } // gaussian_kde
//
// #endif // A3_HPP
