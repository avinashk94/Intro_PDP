// /*  AVINASH
//  *  KOMMINENI
//  *  akommine
//  */

#ifndef A3_HPP
#define A3_HPP
#include <math.h>

using namespace std;

__global__ void evaluate(float *x, float *y, int n, float h,float A){
    extern __shared__ float buf[];
    float* Xs = buf;

    int m = blockDim.x;
    int idx = threadIdx.x;
    int bdx = blockIdx.x;
    int i = bdx*m + idx;
    float k = 0.0;
    float xi = x[i];
    // if(i==0)printf("GridDim:%d \t BlockDim:%d", gridDim.x, blockDim.x);

    if(i<n){
        for (int l = 0; l < gridDim.x; l++) {
            if(l*m + idx < n){
                Xs[idx] = x[l*m + idx];
                __syncthreads();
                for (int j = 0; j < m; j++) {
                    float a = (xi - Xs[j])/h;
                    k += expf(-powf(a,2));
                }
                __syncthreads();
            }
            // k = Xs[idx];
        }
        y[i] = A*k;
    }
}

void gaussian_kde(int n, float h, std::vector<float>& x, std::vector<float>& y) {
   printf("Hello....\n");
   int m = 4;

   float *deviceX, *deviceY;

   int size = n*sizeof(float);
   float A = 1/(n*h*sqrtf(2*M_PI));

   cudaMalloc(&deviceX, size);
   cudaMalloc(&deviceY, size);

   cudaMemcpy(deviceX, x.data(), size, cudaMemcpyHostToDevice);
   evaluate<<<(int)ceil((float)n/(float)m),m,m*sizeof(float)>>>(deviceX, deviceY,n,h,A);
   cudaMemcpy(y.data(), deviceY, size, cudaMemcpyDeviceToHost);
   printf("End!!!!!!!!!%d\n",(int)ceil((float)n/(float)m));

   cout<<A<<endl;
   vector<float> y2(n);
   for (int j = 0; j < n; j++) {
       float k = 0;
       for (int i = 0; i < n; i++) {
           float a = (x[j] - x[i])/h;
           k += expf(-powf(a,2));
       }
       y2[j] = A*k;
   }


   for (int i = 0; i < 10; i++) {
       cout<<x[i]<<"\t"<<y[i]<<"\t"<<y2[i]<<endl;
   }
} // gaussian_kde

#endif // A3_HPP
