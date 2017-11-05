#include<stdio.h>
#include<omp.h>
#include<iostream>

using std::cout;
using std::endl;

static long num_steps = 100000;
#define NUM_THREADS 3
double step;
int main (){
    int i;
    double pi, sum = 0.0;
    step = 1.0/(double) num_steps;

    double start, end;
    start = omp_get_wtime();
    // #pragma omp parallel
    // {
    //     double x;
        #pragma omp parallel for reduction(+:sum)
            for (i=0;i< num_steps; i++){
                double x = (i+0.5)*step;
                sum += 4.0/(1.0+x*x);
            }
    // }
    pi = step * sum;

    end = omp_get_wtime();
    double timeTaken = end-start;
    cout<<timeTaken<<endl;
    cout<<pi<<endl;
}
