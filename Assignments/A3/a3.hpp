// /*  AVINASH
//  *  KOMMINENI
//  *  akommine
//  */
//
// #ifndef A3_HPP
// #define A3_HPP
// #include <math.h>
//
// using namespace std;
//
// __global__
// void evaluate(float *x, float *y, int n, float h){
//    int i = blockIdx.x*blockDim.x + threadIdx.x;
//     if(i<n) y[i] = x[i];
//
// }
//
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

#ifndef A3_HPP
#define A3_HPP
#include <math.h>

using namespace std;

__device__
float computek(float v){
    float v1= powf(v,2);
    float v2 = expf(-v1/2);
    float v3 = sqrtf(2*M_PI);
    float v4 = v2/v3;
    return v4;
}

__global__ void evaluate(float *x, float *y, int n, float h,int m){
    extern __shared__ float buf[];

    int tx = threadIdx.x;
    int i = blockIdx.x*blockDim.x + threadIdx.x;
    buf[tx] = x[tx];

    for(int k =0;k<m;k++){
        y[i]=0;
        y[i]+=computek(x[i]-buf[tx]);
    }

}

void gaussian_kde(int n, float h, std::vector<float>& x, std::vector<float>& y) {
   printf("Hello....\n");
   int m = 4;

   float *deviceX, *deviceY;

   int size = n*sizeof(float);

   cudaMalloc(&deviceX, size);
   cudaMalloc(&deviceY, size);

   cudaMemcpy(deviceX, x.data(), size, cudaMemcpyHostToDevice);
   evaluate<<<(int)ceil(n/m),m,m*sizeof(float)>>>(deviceX, deviceY,n,h,m);
   cudaMemcpy(y.data(), deviceY, size, cudaMemcpyDeviceToHost);
   printf("End!!!!!!!!!\n");

   int A = 1/(n*h*sqrtf(2*M_PI));
   cout<<A<<endl;
   for (int j = 0; j < n; j++) {
       int k = 0;
       for (int a, i = 0; i < n; i++) {
           a = (x[0] - x[i])/h
           k += expf(-powf(a,2))
       }
       y[j] = A*k;
   }


   for (int i = 0; i < 10; i++) {
       cout<<x[i]<<"-->"<<y[i]<<endl;
   }
} // gaussian_kde

#endif // A3_HPP
