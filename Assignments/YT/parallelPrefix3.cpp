#include<stdio.h>
#include<omp.h>
#include<iostream>
#include<string.h>
#include<vector>
#include <math.h>

using namespace std;

// using std::cout;
// using std::endl;

int sizeOfInput = 14;
#define NUM_THREADS 3

void recursiveOperator(double *input, double *output, int sizeOfInput);
long double *input, *output;
#include<omp.h>
int main(){

    omp_set_num_threads(NUM_THREADS);
    double start, end;
    int partialArrayLen, id;
    input = new long double[sizeOfInput];
    output = new long double[sizeOfInput];
    /////////////////////////////////////////////////////////////
    start = omp_get_wtime();
    #pragma omp parallel for//Initialising a sequence of numbers.
        for(int i=0; i< sizeOfInput; i++) {
            input[i] = 1;
        }
    end = omp_get_wtime();
//    cout<<end-start<<endl;
    /////////////////////////////////////////////////////////////
    int i,j;
    int index1, index2;
    start = omp_get_wtime();

    copy(input, input+sizeOfInput, output);


    for (j = 0; j < log2(sizeOfInput); j++){
        #pragma omp parallel for private(index1, index2) num_threads(NUM_THREADS)
        for (i = 1; i<sizeOfInput/(int)pow(2,j+1)+1; i++) {
            index1 = i*(int)pow(2,j+1) -1;
            index2 = (i-1)*(int)pow(2,j+1) -1+(int)pow(2,j);
            output[index1] += output[index2];
        }
    }

    for (j = log2(sizeOfInput)-2; j>=0; j--){
        // #pragma omp parallel for private(index1, index2) num_threads(NUM_THREADS)
        for (i = 1; i<sizeOfInput/(int)pow(2,j+1)+1; i++) {
            index1 = i*(int)pow(2,j+1) -1;
            index2 = (i)*(int)pow(2,j+1) -1+(int)pow(2,j);
            // cout<<index1<<"\t"<<index2<<"\t"<<i<<"\t"<<j<<endl;
            output[index2] += output[index1];
        }
    }

    end = omp_get_wtime();
    cout<<end-start<<endl;
    cout<<input[sizeOfInput-1]<<endl;
    cout<<output[sizeOfInput-1]<<endl;
   for(int i=0;i<sizeOfInput;i++)cout<<i<<"\t"<<*(output+i)<<endl;
}
