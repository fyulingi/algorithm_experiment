#ifndef RANDOM_NUM_H_INSERTION_SORT_H
#define RANDOM_NUM_H_INSERTION_SORT_H

int insertion_sort(int *A, int n)  // insertion_sort for A[0,...,n]
{
    int i,j,key;
    for(i=1;i<=n;i++){
        key=A[i];
        j=i-1;
        while(A[j]>key&&j>=0){
            A[j+1]=A[j];
            j--;
        }
        A[j+1]=key;
    }
    return 0;
}

#endif //RANDOM_NUM_H_INSERTION_SORT_H
