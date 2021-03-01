#ifndef RANDOM_NUM_H_COUNTING_SORT_H
#define RANDOM_NUM_H_COUNTING_SORT_H

int counting_sort(int *A,int n)  //element in array A[0,...,n] is not bigger than 1<<15
{
    int k = 1<<15; // range of the elements
    int *C=(int *)malloc(sizeof(int)*(k+1));
    int i,j,m=0;
    for(i=0;i<=k;i++){
        C[i]=0;
    }
    for(i=0;i<=n;i++){
        C[A[i]]++;
    }
    for(i=0;i<=k;i++){
        for(j=0;j<C[i];j++){
            A[m]=i;
            m++;
        }
    }
    free(C);
    return 0;
}

#endif //RANDOM_NUM_H_COUNTING_SORT_H
