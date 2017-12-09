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
    // if(i==0)printf("GridDim:%d \t BlockDim:%d", gridDim.x, blockDim.x);

    if(i<n){
        float xi = x[i];
        __syncthreads();
        for (int l = 0; l < gridDim.x; l++) {
            // if(l*m + idx < n)
            Xs[idx] = x[l*m + idx];
            __syncthreads();
            for (int v = 0; v < m; v++) {
                printf("l is %d v is %d Xs is %d\n",l,v,Xs[v] );
            }
            for (int j = 0; j < m && (l*m + j<n); j++) {
                printf("cur = %f - b[%d] = %f\n",xi,j,Xs[j]);
                float a = (xi - Xs[j])/h;
                k += expf(-powf(a,2));
                // k += 1;
                // k = Xs[idx];
                k = xi;
            }
            __syncthreads();
            // k = xi;
        }
        // y[i] = A*k;
        y[i] = k;
    }
}

void gaussian_kde(int n, float h, std::vector<float>& x, std::vector<float>& y) {
   // printf("Hello....\n");
   int m = 4;

   float *deviceX, *deviceY;

   int size = n*sizeof(float);
   float A = 1/(n*h*sqrtf(2*M_PI));

   cudaMalloc(&deviceX, size);
   cudaMalloc(&deviceY, size);

   cudaMemcpy(deviceX, x.data(), size, cudaMemcpyHostToDevice);
   evaluate<<<(int)ceil((float)n/(float)m),m,m*sizeof(float)>>>(deviceX, deviceY,n,h,A);
   cudaMemcpy(y.data(), deviceY, size, cudaMemcpyDeviceToHost);
   // printf("End!!!!!!!!!%d\n",(int)ceil((float)n/(float)m));

   cout<<A<<endl;
   vector<float> y2(n);
   for (int j = 0; j < n; j++) {
       float k = 0;
       for (int i = 0; i < n; i++) {
           float a = (x[j] - x[i])/h;
           k += expf(-powf(a,2));
       }
       y2[j] = k;
   }

   for (int i = 0; i < n; i++) {
       cout<<x[i]<<"\t"<<y[i]<<"\t"<<y2[i]<<endl;
   }
} // gaussian_kde

#endif // A3_HPP
