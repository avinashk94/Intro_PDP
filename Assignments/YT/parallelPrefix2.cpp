#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>

int main()
{
  int *arr, *partial, *temp;
  int num_threads, work, n;
  int i, mynum, last;
  printf("Enter length:");
  scanf("%d", &n);
  if(!(arr = (int *) malloc (sizeof (int) * n))) return -1;
  printf("Enter numbers:\n");
  for(i = 0; i < n; i++)
    scanf("%d", arr + i);
#pragma omp parallel default(none) private(i, mynum, last) shared(arr, partial, temp, num_threads, work, n)
  {
#pragma omp single
    {
      num_threads = omp_get_num_threads();
      if(!(partial = (int *) malloc (sizeof (int) * num_threads))) exit(-1);
      if(!(temp = (int *) malloc (sizeof (int) * num_threads))) exit(-1);
      work = n / num_threads + 1; /*sets length of sub-arrays*/
    }
    mynum = omp_get_thread_num();
    /*calculate prefix-sum for each subarray*/
    for(i = work * mynum + 1; i < work * mynum + work && i < n; i++)
      arr[i] += arr[i - 1];
    partial[mynum] = arr[i - 1];
#pragma omp barrier
    /*calculate prefix sum for the array that was made from last elements of each of the previous sub-arrays*/
    for(i = 1; i < num_threads; i <<= 1) {
      if(mynum >= i)
        temp[mynum] = partial[mynum] + partial[mynum - i];
#pragma omp barrier
#pragma omp single
      memcpy(partial + 1, temp + 1, sizeof(int) * (num_threads - 1));
    }
    /*update original array*/
    for(i = work * mynum; i < (last = work * mynum + work < n ? work * mynum + work : n); i++)
      arr[i] += partial[mynum] - arr[last - 1];
  }
  for(i = 0; i < n; i++)
    printf("%d\n", arr[i]);
  return 0;
}
