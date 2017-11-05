#include<stdio.h>
#include<omp.h>
#include<iostream>

using std::cout;
using std::endl;


static long num_steps= 100000;
#define NUM_THREADS 4


double step;
int main(){
    int i, nthreads;
    double pi;
    step = 1/(double)NUM_THREADS;
    double start, end;
    start = omp_get_wtime();
    omp_set_num_threads(NUM_THREADS);
    #pragma omp parallel
    {
        int i, id, nthrds;
        double x,sum;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        if(id==0)nthreads=nthrds;
        for(i=id;i<num_steps;i=i+nthrds){
            x = (i+0.5)*step;
            sum += 4/(1.0 + x*x);
        }
        #pragma omp critical
        pi += sum*step;
    }

    end = omp_get_wtime();
    double timeTaken = end-start;
    cout<<timeTaken<<endl;
    cout<<pi<<endl;
}
