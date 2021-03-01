#ifndef RANDOM_NUM_H_QUICK_SORT_H
#define RANDOM_NUM_H_QUICK_SORT_H

int swap(int *A,int i,int j)  // swap i and j position in array A
{
    int k=A[j];
    A[j]=A[i];
    A[i]=k;
    return 0;
}

int partition(int *A,int p,int r)
{
    int x=A[r],i=p-1;
    for(int j=p;j<r;j++){
        if(A[j]<=x){
            i=i+1;
            swap(A,i,j);
        }
    }
    swap(A,r,i+1);
    return(i+1);
}


int quick_so(int *A, int p, int r)
{
    if(p<r){
        int q=partition(A,p,r);
        quick_so(A,p,q-1);
        quick_so(A,q+1,r);
    }
    return 0;
}

int quick_sort(int *A, int n)
{
    quick_so(A, 0, n);
    return 0;
}

#endif //RANDOM_NUM_H_QUICK_SORT_H
