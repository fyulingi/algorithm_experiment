//
// Created by fyuling on 2021/1/1.
//

#ifndef EX1_KRUSCAL_H
#define EX1_KRUSCAL_H

#include <stdio.h>

#include "graph_generate.h"

struct set_node{
    int u;
    int v;
    int w;
    struct set_node *next;
};

struct set{
    struct set_node *first;
    struct set_node *last;
    int size;
};

struct set create_set(){
    struct set A;

    A.first = NULL;
    A.last = NULL;
    A.size = 0;

    return A;
}

struct set insert_set(struct set A, int i, int j, int a){
    struct set_node *p;

    if(A.size == 0) {
        A.first = (struct set_node *) malloc(sizeof(struct set_node));
        A.last = A.first;
        p = A.first;
        p->u = i;
        p->v = j;
        p->w = a;
        p->next = NULL;
        A.size = 1;
        return A;
    } else {
        p = (struct set_node *) malloc(sizeof(struct set_node));
        p->u = i;
        p->v = j;
        p->w = a;
        p->next = NULL;
        A.last->next = p;
        A.last = p;
        A.size++;
        return A;
    }
}

void swap(struct edge *E, int i, int j){

    int temp1 = E[i].u;
    int temp2 = E[i].v;
    int temp3 = E[i].w;

    E[i].u = E[j].u;
    E[i].v = E[j].v;
    E[i].w = E[j].w;

    E[j].u = temp1;
    E[j].v = temp2;
    E[j].w = temp3;

}

int max_heapfy(struct edge *E,int n,int i)  //need to heapfy size_n max_heap A at node i
{
    while(2*i+1<=n){
        if(E[i].w>E[2*i+1].w){
            if(2*i+2>n||E[i].w>E[2*i+2].w){
                return 0;
            }
            else{
                swap(E,i,2*i+2);
                i=2*i+2;
            }
        }
        else{
            if(2*i+2>n||E[i].w>E[2*i+2].w){
                swap(E,i,2*i+1);
                i=2*i+1;
            }
            else if(E[2*i+1].w>E[2*i+2].w){
                swap(E,i,2*i+1);
                i=2*i+1;
            }
            else{
                swap(E,i,2*i+2);
                i=2*i+2;
            }
        }
    }
    return 0;
}

void build_max_heap(struct edge *E,int n)
{
    for(int i=(n-1)/2; i>=0;i--){
        max_heapfy(E,n,i);
    }
}

void heap_sort(struct edge *E,int n)
{
    build_max_heap(E,n);
    for(int i= n; i > 0; i--){
        swap(E, 0, i);
        max_heapfy(E,i-1,0) ;
    }
}


void Union(int *S, int i, int j, int size)
{
    int key = S[j];

    for(int k = 0; k < size; k++){
        if(S[k] == key){
            S[k] = S[i];
        }
    }
}

struct set kruscal(struct graph G)
        // 对 G 运行 kruscal 算法, 将结果返回一个 set 类型
{
    int i;

    struct set A = create_set();

    // S 维护节点所在的集合
    int *S = (int *)malloc(sizeof(int) * G.size);
    for(i = 0; i < G.size; i++){
        S[i] = i;
    }

    heap_sort(G.E, G.edge_num - 1);

    for(i = 0; i < G.edge_num; i++){
        if(S[G.E[i].u] != S[G.E[i].v]){
            A = insert_set(A, G.E[i].u, G.E[i].v, G.E[i].w);
            Union(S, G.E[i].u, G.E[i].v, G.size);
        }
    }

    free(S);
    return A;
}




#endif //EX1_KRUSCAL_H
