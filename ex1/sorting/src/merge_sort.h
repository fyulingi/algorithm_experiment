#ifndef RANDOM_NUM_H_MERGE_SORT_H
#define RANDOM_NUM_H_MERGE_SORT_H


#include <stdlib.h>

int merge(int *A,int p,int q,int r)  //require p<=q<=r
{
    int i,j;
    int *A1 = (int *) malloc(sizeof(int) * (q - p + 1));
    int *A2 = (int *) malloc(sizeof(int) * (r - q));
    for (i = 0; i < q - p + 1; i++) {
        A1[i] = A[p + i];
    }
    for (j = 0; j < r - q; j++) {
        A2[j] = A[q + j + 1];
    }
    i = 0;
    j = 0;
    while (i < q - p + 1 && j < r - q) {
        if (A1[i] <= A2[j]) {
            A[i + j + p] = A1[i];
            i++;
        } else {
            A[i + j + p] = A2[j];
            j++;
        }
    }
    while (i < q - p + 1) {
        A[p + i + j] = A1[i];
        i++;
    }
    while (j < r - q) {
        A[p + i + j] = A2[j];
        j++;
    }
    free(A1);
    free(A2);
    return 0;
}

int merge_so(int *A,int p,int r)
{
    if(p<r){
        int q=(p+r)/2;
        merge_so(A,p,q);
        merge_so(A,q+1,r);
        merge(A,p,q,r);
    }
    return 0;
}

int merge_sort(int *A, int n)
// 调用merge_so, 从 0 开始排序
{
    merge_so(A, 0, n);
    return 0;
}

#endif //RANDOM_NUM_H_MERGE_SORT_H
