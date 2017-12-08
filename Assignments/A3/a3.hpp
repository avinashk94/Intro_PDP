/*  AVINASH
 *  KOMMINENI
 *  akommine
 */

#ifndef A3_HPP
#define A3_HPP
#include <math.h>

using namespace std;

_global_ void evaluate(float *x, float *y, int n, float h){
 int i = blockIdx.x*blockDim.x + threadIdx.x;
    if(i<n) y[i] = x[i];

}

void gaussian_kde(int n, float h, const std::vector<float>& x, std::vector<float>& y) {
    printf("Hello....\n");
    int m = 4;

    float *deviceX, *deviceY;

    int size = n*sizeof(float);

    cudaMalloc(&deviceX, size);
    cudaMalloc(&deviceY, size);

    cudaMemcpy(deviceX, &x, size, cudaMemcpyHostToDevice);

    evaluate<<<(int)ceil(n/m),m,m>>>(deviceX, deviceY,n,h);

    cudaMemcpy(&y, deviceY, size, cudaMemcpyDeviceToHost);

    printf("End!!!!!!!!!\n");
    for (int i = 0; i < 5; i++) {
        cout<<x[i]<<"\t"<<y[i]<<endl;
    }
} // gaussian_kde

#endif // A3_HPP
