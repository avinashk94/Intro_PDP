#include<stdio.h>
#include<omp.h>
#include<iostream>
#include<string.h>
#include<vector>
#include <math.h>

using namespace std;

// using std::cout;
// using std::endl;

int sizeOfInput = 16;
#define NUM_THREADS 3

void recursiveOperator(double *input, double *output, int sizeOfInput);
double *input, *output;
#include<omp.h>
int main(){

    omp_set_num_threads(NUM_THREADS);
    double start, end;
    input = new double[sizeOfInput];
    output = new double[sizeOfInput];
    /////////////////////////////////////////////////////////////
    start = omp_get_wtime();
    #pragma omp parallel for//Initialising a sequence of numbers.
        for(int i=0; i< sizeOfInput; i++) {
            input[i] = i;
        }
    end = omp_get_wtime();
    cout<<end-start<<endl;
    cout<<*(input + 0)<<"\t"<<*(input + 10)<<"\t"<<*(input + 50)<<"\t"<<*(input + sizeOfInput-1)<<"\n"<<endl;
    /////////////////////////////////////////////////////////////

    start = omp_get_wtime();
    int nuOfSteps = log2(sizeOfInput);
    // #pragma omp for
    // for(int i=0;i<nuOfSteps;i++){
    // #pragma omp parallel for
    for(int j=1; j<sizeOfInput/2+1;j++){
        input[2*j-1] = input[2*j-2] + input[2*j-1];
        // cout<<j<<"\t"<<input[2*j-1]<<endl;
    }

    // }

    end = omp_get_wtime();
    cout<<end-start<<endl;
    // for(int i=0;i<sizeOfInput;i++)cout<<i<<"\t"<<*(input+i)<<endl;

}

void recursiveOperator(double *input, double *output, int sizeOfInput){
    // #pragma omp parallel for
    // for (int i = 0; i < log2(sizeOfInput); i++) cout<<i<<endl;

}
