/*  AVINASH
 *  KOMMINENI
 *  akommine
 */

#ifndef A3_HPP
#define A3_HPP
#include <math.h>

using namespace std;

// __device__
// float computek(float v){
//     float v1= powf(v,2);
//     float v2 = expf(-v1/2);
//     float v3 = sqrtf(2*M_PI);
//     float v4 = v2/v3;
//     return v4;
// }

__global__
void evaluate(float *x, float *y, int n, float h){
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    printf("%d\n",x[i]);

}

void gaussian_kde(int n, float h, const std::vector<float>& x, std::vector<float>& y) {
    printf("Hello....\n");
    int m = 32;

    float *deviceX, *deviceY;

    int size = n*sizeof(float);

    cudaMalloc(&deviceX, size);
    cudaMalloc(&deviceY, size);

    cudaMemcpy(&deviceX, &x, size, cudaMemcpyHostToDevice);

    // dim3 dimGrid((int)ceil(n/m), (int)ceil(n/m));
    // dim3 dimBlock(m);

    // evaluate<<<dimGrid, dimBlock>>>(d_x, d_y, n, h);

    evaluate<<<(int)ceil(n/m),m>>>(deviceX, deviceY,n,h);

    printf("End!!!!!!!!!\n");
    for (int i = 0; i < 5; i++) {
        cout<<x[i]<<"\t"<<y[i]<<endl;
    }
} // gaussian_kde

#endif // A3_HPP
