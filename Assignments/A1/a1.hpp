/*  YOUR_FIRST_NAME
 *  YOUR_LAST_NAME
 *  YOUR_UBIT_NAME
 */

#ifndef A1_HPP
#define A1_HPP

#include <vector>
#include <mpi.h>
#include<stdio.h>
#include<iostream>
#include<string.h>
#include <math.h>

using namespace std;

void printArray(vector<signed char>& A, int a, int rank){
    cout<<rank<<endl;
    for (int i = 0; i < a*a; i++){
        cout<<static_cast<int>(A[i])<<"\t";
        if ((i+1)%a==0) {
            cout<<endl;
        }

    }
    cout<<endl;
}


int connected_components(std::vector<signed char>& A, int n, int q, const char* out, MPI_Comm comm) {
    // ...
    int rank, size;

    MPI_Comm_size(comm, &size);
    MPI_Comm_rank(comm, &rank);

    int a = n/q;
    int length = a*a;
    vector<signed char> P(A);

    for (int i = 0; i < length; i++) {
        if (A[i]==1) {
            P[i] = i/a + a*(rank/q);
        }
    }
    // std::vector<int> partialMax(a, 0);
    // std::vector<int> totalMax(a, 0);

    int partialMax[a];
    memset( partialMax, 0, a*sizeof(int) );
    int totalMax[a];
    memset( totalMax, 0, a*sizeof(int) );

    for (int i = 0; i < length; i++) {
        if (P[i]>partialMax[i%a])  {
            partialMax[i%a] = P[i];
        }
    }

    int col = rank%q;
    MPI_Comm col_comm;
    MPI_Comm_split(comm, col, rank, &col_comm);

    MPI_Allreduce(&partialMax, &totalMax, a, MPI_INT, MPI_MAX,col_comm);

    for (int i = 0; i < length; i++) {
        P[i] = totalMax[i%a];
    }

    vector<signed char> M(A);

    for (int i = 0; i < length; i++) {
        M[i] = M[i]*P[i];
    }

    int partialMax2[a];
    memset( partialMax2, 0, a*sizeof(int) );
    int totalMax2[a];
    memset( totalMax2, 0, a*sizeof(int) );

    for (int i = 0; i < length; i++) {
        if (M[i]>partialMax2[i/a])  {
            partialMax2[i/a] = M[i];
        }
    }

    int row = rank/q;
    MPI_Comm row_comm;
    MPI_Comm_split(comm, row, rank, &row_comm);

    MPI_Allreduce(&partialMax2, &totalMax2, a, MPI_INT, MPI_MAX,row_comm);
    vector<signed char> Q(A);
    for (int i = 0; i < length; i++) {
        Q[i] = totalMax2[i/a];
    }

    for (int i = 0; i < length; i++) {
        if (Q[i]== i%a + a*(rank%q)) {
            M[i] = P[i];
        } else{
            M[i] = 0;
        }
    }

    int partialMax3[a];
    memset( partialMax3, 0, a*sizeof(int) );
    int totalMax3[a];
    memset( totalMax3, 0, a*sizeof(int) );

    for (int i = 0; i < length; i++) {
        if (M[i]>partialMax3[i/a])  {
            partialMax3[i/a] = M[i];
        }
    }
    MPI_Allreduce(&partialMax3, &totalMax3, a, MPI_INT, MPI_MAX,row_comm);
    vector<signed char> S(A);
    for (int i = 0; i < length; i++) {
        S[i] = totalMax3[i/a];
    }

    // printArray(S,a,rank);
    // printArray(M,a,rank);

    // Tree Hanging.......
    for (int i = 0; i < length; i++) {
        if (P[i]== i/a + a*(rank/q)) {
            M[i] = S[i];
        } else{
            M[i] = 0;
        }
    }
    // printArray(P,a,rank);
    // printArray(M,a,rank);

    int partialMax4[a];
    memset( partialMax4, 0, a*sizeof(int) );
    int totalMax4[a];
    memset( totalMax4, 0, a*sizeof(int) );

    for (int i = 0; i < length; i++) {
        if (M[i]>partialMax4[i/a])  {
            partialMax4[i/a] = M[i];
        }
    }
    MPI_Allreduce(&partialMax4, &totalMax4, a, MPI_INT, MPI_MAX,row_comm);
    // vector<signed char> S(A);
    for (int i = 0; i < length; i++) {
        Q[i] = totalMax4[i/a];
    }


    for (int i = 0; i < length; i++) {
        P[i] = max(S[i],Q[i]);
    }

    // printArray(Q,a,rank);
    // printArray(S,a,rank);
    // printArray(P,a,rank);

    // cout<<partialMax[0]<<"\t"<<partialMax[1]<<"\t"<<partialMax[2]<<"\t"<<partialMax[3]<<"\n"<<endl;
    // cout<<partialMax2[0]<<"\t"<<partialMax2[1]<<"\t"<<partialMax2[2]<<"\t"<<partialMax2[3]<<endl;
    // cout<<totalMax2[0]<<"\t"<<totalMax2[1]<<"\t"<<totalMax2[2]<<"\t"<<totalMax2[3]<<"\n"<<endl;




    return -1;
} // connected_components

#endif // A1_HPP
