/*ISSAC KOSHY
 *PANICKER
 *ISSACKOS
 */

#ifndef A3_HPP
#define A3_HPP
#include <math.h>

using namespace std;

__global__ void evaluate(float *x, float *y, int n, float h, float calc){
  extern __shared__ float buf[];
    float* b = buf;

    int tx = threadIdx.x;
    int bx = blockIdx.x;
    int m = blockDim.x;
    int g = gridDim.x;
    int index = bx * m + tx;
    float cur = x[index];
    float computek =0.0;

    for (int i = 0; i < g; i++) {
        b[tx] = x[i*m + tx];
        __syncthreads();
        for (int j = 0; j < m && i*m+j<n ; j++) {
        computek += expf(-powf((cur-b[j]/h),2));
}
}
    y[index] = calc*computek; 
}        
          
void gaussian_kde(int n, float h,const std::vector<float>& x, std::vector<float>& y) {
        
    int m = 32;
    float *d_x, *d_y;
    int size = n*sizeof(float);
    float calc = 1/(n*h*sqrtf(2*M_PI));
    
    cudaMalloc(&d_x, size);
    cudaMalloc(&d_y, size);

    cudaMemcpy(d_x, x.data(), size, cudaMemcpyHostToDevice);
    
    evaluate<<<(int)ceil(n/(float)m),m,m*sizeof(float)>>>(d_x,d_y,n,h,calc);
    
    cudaMemcpy(y.data(), d_y, size, cudaMemcpyDeviceToHost);
    
    cudaFree(d_x);
    cudaFree(d_y);

} // gaussian_kde

#endif // A3_HPP


