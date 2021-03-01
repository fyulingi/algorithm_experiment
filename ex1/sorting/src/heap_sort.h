#ifndef RANDOM_NUM_H_HEAP_SORT_H
#define RANDOM_NUM_H_HEAP_SORT_H

int max_heapfy(int *A,int n,int i)  //need to heapfy size_n max_heap A at node i
{
    while(2*i+1<=n){
        if(A[i]>A[2*i+1]){
            if(2*i+2>n||A[i]>A[2*i+2]){
                return 0;
            }
            else{
                swap(A,i,2*i+2);
                i=2*i+2;
            }
        }
        else{
            if(2*i+2>n||A[i]>A[2*i+2]){
                swap(A,i,2*i+1);
                i=2*i+1;
            }
            else if(A[2*i+1]>A[2*i+2]){
                swap(A,i,2*i+1);
                i=2*i+1;
            }
            else{
                swap(A,i,2*i+2);
                i=2*i+2;
            }
        }
    }
    return 0;
}

int build_max_heap(int *A,int n)
{
    for(int i=(n-1)/2;i>=0;i--){
        max_heapfy(A,n,i);
    }
    return 0;
}

int heap_sort(int *A,int n)  //assume A[0,***,n] is the array we need to sort
{
    build_max_heap(A,n);
    for(int i=n;i>0;i--){
        swap(A,0,i);
        max_heapfy(A,i-1,0) ;
    }
    return 0;
}

#endif //RANDOM_NUM_H_HEAP_SORT_H
