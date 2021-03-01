#ifndef JOHNSON_H_DIJKSTRA_H
#define JOHNSON_H_DIJKSTRA_H

#include "graph_generate.h"
#include "bellman_ford.h"

struct path_node{
    int u;
    struct path_node *next;
};

struct source_node_dij{
    int u;
    int d;
    int pi;
};

struct source_node_queue{
    int size;
    struct source_node_dij *sourceNode;
};

struct source_node_queue init_dij(struct graph G, int s)
{
    struct source_node_queue sourcenodequeue;
    sourcenodequeue.sourceNode = (struct source_node_dij *)malloc(sizeof(struct source_node_dij) * (G.size - 1));
    sourcenodequeue.size = G.size - 1;


    for (int i = 0; i < G.size - 1; ++i) {
        sourcenodequeue.sourceNode[i].d = 100000;
        sourcenodequeue.sourceNode[i].pi = G.size - 1;
        sourcenodequeue.sourceNode[i].u = i;   // 代表 NULL
    }

    sourcenodequeue.sourceNode[s].u = 0;
    sourcenodequeue.sourceNode[0].u = s;
    sourcenodequeue.sourceNode[0].d = 0;

    return sourcenodequeue;
}

struct source_node_queue swap_dij(struct source_node_queue sourceNodeQueue, int i, int j)
{
    int temp1 = sourceNodeQueue.sourceNode[i].d;
    int temp2 = sourceNodeQueue.sourceNode[i].u;
    int temp3 = sourceNodeQueue.sourceNode[i].pi;

    sourceNodeQueue.sourceNode[i].d = sourceNodeQueue.sourceNode[j].d;
    sourceNodeQueue.sourceNode[i].u = sourceNodeQueue.sourceNode[j].u;
    sourceNodeQueue.sourceNode[i].pi = sourceNodeQueue.sourceNode[j].pi;

    sourceNodeQueue.sourceNode[j].d = temp1;
    sourceNodeQueue.sourceNode[j].u = temp2;
    sourceNodeQueue.sourceNode[j].pi = temp3;

    return sourceNodeQueue;

}

struct source_node_queue heapfy(struct source_node_queue sourceNodeQueue, int i)
{

    int n = sourceNodeQueue.size - 1;
    while(2*i+1<=n){
        if(sourceNodeQueue.sourceNode[i].d < sourceNodeQueue.sourceNode[2*i+1].d){
            if(2*i+2>n||sourceNodeQueue.sourceNode[i].d < sourceNodeQueue.sourceNode[2*i+2].d){
                return sourceNodeQueue;
            }
            else{
                sourceNodeQueue = swap_dij(sourceNodeQueue,i,2*i+2);
                i=2*i+2;
            }
        }
        else{
            if(2*i+2>n||sourceNodeQueue.sourceNode[i].d < sourceNodeQueue.sourceNode[2*i+2].d){
                sourceNodeQueue = swap_dij(sourceNodeQueue,i,2*i+1);
                i=2*i+1;
            }
            else if(sourceNodeQueue.sourceNode[2*i+1].d < sourceNodeQueue.sourceNode[2*i+2].d){
                sourceNodeQueue = swap_dij(sourceNodeQueue,i,2*i+1);
                i=2*i+1;
            }
            else{
                sourceNodeQueue = swap_dij(sourceNodeQueue,i,2*i+2);
                i=2*i+2;
            }
        }
    }

    return sourceNodeQueue;
}
struct source_node_queue  extract_min(struct source_node_queue sourcenodequeue, int *a)
{
    if(sourcenodequeue.size > 0) {
        sourcenodequeue = swap_dij(sourcenodequeue, sourcenodequeue.size - 1, 0);
        sourcenodequeue.size = sourcenodequeue.size - 1;
        sourcenodequeue = heapfy(sourcenodequeue, 0);

        *a = sourcenodequeue.sourceNode[sourcenodequeue.size].u;

        return sourcenodequeue;
    }
}

void Uni_dij(int *S, int u)
{
    S[u] = 1;
}

struct source_node_queue decrease_key(struct source_node_queue sourceNodeQueue, int i, int key)
{
    sourceNodeQueue.sourceNode[i].d = key;
    while (i > 0 && sourceNodeQueue.sourceNode[(i+1)/2 - 1].d > sourceNodeQueue.sourceNode[i].d){
        sourceNodeQueue = swap_dij(sourceNodeQueue, i, (i+1)/2 - 1);
        i = (i+1)/2 - 1;
    }
    return sourceNodeQueue;
}

struct source_node_queue relax_dij(struct graph G, int u, int v, int w, struct source_node_queue sourceNodeQueue)
{
    int i = 0, j = 0;
    while (sourceNodeQueue.sourceNode[i].u != u){
        i ++;
    }
    while (sourceNodeQueue.sourceNode[j].u != v){
        j ++;
    }

    if(sourceNodeQueue.sourceNode[j].d > sourceNodeQueue.sourceNode[i].d + w){
        sourceNodeQueue.sourceNode[j].pi = u;
        sourceNodeQueue = decrease_key(sourceNodeQueue, j, sourceNodeQueue.sourceNode[i].d + w);
    }
    return  sourceNodeQueue;
}

struct source_node_queue dijkstra(struct graph G, int s)
        // 针对 G.new 的算法, 忽略了 G.new 中的 s 节点
{
    int i, u;
    struct node *no;
    struct edge *ed;

    // S[i] = 1: s in the set
    int *S = (int *)malloc(sizeof(int )* (G.size - 1));
    for(i = 0; i < G.size - 1; i++){
        S[i] = 0;
    }
    S[s] = 1;

    struct source_node_queue sourcenodequeue = init_dij(G, s);

    while (sourcenodequeue.size > 0) {
        sourcenodequeue = extract_min(sourcenodequeue, &u);
        Uni_dij(S, u);

        no = G.first;
        for (i = 0; i < u; i++) {
            no = no->next;
        }
        ed = no->e;
        while (ed != NULL) {
            sourcenodequeue = relax_dij(G, u, ed->v, ed->w, sourcenodequeue);
            ed = ed->next;
        }
    }

    return sourcenodequeue;
}


#endif //JOHNSON_H_DIJKSTRA_H
