#include<stdio.h>
#include<omp.h>
#include<iostream>

using std::cout;
using std::endl;


static long num_steps= 100000;
#define NUM_THREADS 8
#define PAD 8


double step;
int main(){
    int i, nthreads;
    double sum[NUM_THREADS][PAD], pi;
    step = 1/(double)NUM_THREADS;
    double start, end;
    start = omp_get_wtime();
    omp_set_num_threads(NUM_THREADS);
    #pragma omp parallel
    {
        int i, id, nthrds;
        double x;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        if(id==0)nthreads=nthrds;
        for(i=id, sum[id][0]=0.0;i<num_steps;i=i+nthrds){
            x = (i+0.5)*step;
            sum[id][0] += 4/(1.0 + x*x);
        }
        for(i=0,pi=0;i<nthreads;i++)pi=pi+sum[i][0];
    }

    end = omp_get_wtime();
    double timeTaken = end-start;
    cout<<timeTaken<<endl;
    cout<<pi<<endl;
}
