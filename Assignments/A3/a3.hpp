/*  AVINASH
 *  KOMMINENI
 *  akommine
 */

#ifndef A3_HPP
#define A3_HPP

__global__ void mykernel(){
  printf("Hello from mykernel\n");
}

void gaussian_kde(int n, float h, const std::vector<float>& x, std::vector<float>& y) {
    printf("Hello....\n");
    mykernel<<<1,1>>>();
    cudaDeviceSynchronize();
    printf("End!!!!!!!!!\n");
} // gaussian_kde

#endif // A3_HPP
