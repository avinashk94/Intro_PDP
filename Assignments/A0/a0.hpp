/*  AVINASH
 *  KOMMINENI
 *  akommine
 */

#include<stdio.h>
#include<omp.h>
#include<iostream>
#include<string.h>
#include<vector>
#include <math.h>

#ifndef A0_HPP
#define A0_HPP
#define NUM_THREADS 4

using namespace std;

template <typename T, typename Op>
void omp_scan(int n, const T* in, T* out, Op op) {
    int i,j;
    int index1, index2;
    std::copy(in, in+n, out);
    // omp_set_num_threads(NUM_THREADS);
    for (j = 0; j < log2(n); j++){
        #pragma omp parallel for private(index1, index2) num_threads(NUM_THREADS)
        for (i = 1; i<n/(int)pow(2,j+1)+1; i++) {
            index1 = i*(int)pow(2,j+1) -1;
            index2 = (i-1)*(int)pow(2,j+1) -1+(int)pow(2,j);
            out[index1] = op(out[index1],out[index2]);
        }
    }

    for (j = log2(n)-1; j>=0; j--){
        #pragma omp parallel for private(index1, index2) num_threads(NUM_THREADS)
        for (i = 1; i<n/(int)pow(2,j+1)+1; i++) {
            index1 = i*(int)pow(2,j+1) -1;
            index2 = (i)*(int)pow(2,j+1) -1+(int)pow(2,j);
            if (index1<n && index2<n) out[index2] += out[index1];
            // cout<<index1<<"\t"<<index2<<"\t"<<i<<"\t"<<j<<"\t"<<out[index2]<<endl;
        }
    }

    // for(int i=0;i<n;i++)cout<<i<<"\t"<<*(out+i)<<endl;
} // omp_scan

#endif // A0_HPP
