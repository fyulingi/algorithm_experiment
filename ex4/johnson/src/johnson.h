#ifndef MAIN_C_JOHNSON_H
#define MAIN_C_JOHNSON_H

#include "graph_generate.h"
#include "bellman_ford.h"
#include "dijkstra.h"

struct graph new_graph(struct graph G)
{
    int i, j;
    struct graph G_new;
    struct node *no1;
    struct node *no2;
    struct edge *ed1;
    struct edge *ed2;

    no2 = G.first;

    for(i = 0; i < G.size; i++)
    {
        if(i == 0){
            G_new.first = (struct node *)malloc(sizeof(struct node));
            G_new.last = G_new.first;
            no1 = G_new.first;
            no1->u = no2->u;
            no1->next = NULL;

        } else{
            G_new.last->next = (struct node *)malloc(sizeof(struct node));
            no1 = G_new.last->next;
            no1->u = no2->u;
            no1->next = NULL;
            G_new.last = no1;
        }

        // 权值复制
        ed2 = no2->e;
        j = 0;      // 第一个 edge 节点
        while(ed2 != NULL){
            if(j == 0){
                no1->e = (struct edge *)malloc(sizeof(struct edge));
                ed1 = no1->e;
                ed1->v = ed2->v;
                ed1->w = ed2->w;
                ed1->next = NULL;
                ed2 = ed2->next;
                j = 1;
            } else{
                ed1->next = (struct edge *)malloc(sizeof(struct edge));
                ed1 = ed1->next;
                ed1->v = ed2->v;
                ed1->w = ed2->w;
                ed1->next = NULL;
                ed2 = ed2->next;
            }
        }
        no2 = no2->next;

    }

    G_new.last->next = (struct node *)malloc(sizeof(struct node));
    G_new.last = G_new.last->next;
    no1 = G_new.last;

    no1->u = i;
    no1->next = NULL;
    for(j = 0; j < i; j++){
        if (j == 0){
            no1->e = (struct edge *)malloc(sizeof(struct edge));
            ed1 = no1->e;
            ed1->v = j;
            ed1->w = 0;
            ed1->next = NULL;
        } else{
            ed1->next = (struct edge *)malloc(sizeof(struct edge));
            ed1 = ed1->next;
            ed1->v = j;
            ed1->w = 0;
            ed1->next = NULL;
        }
    }

    G_new.size = G.size + 1;
    G_new.edge_num = G.edge_num + G.size;
    return G_new;
}


int  print_path_i_j(struct source_node_queue sourceNodeQueue, int i, int j, FILE *f)
{
    int k;
    int sum = 0;
    struct path_node *path_first;
    struct path_node *path_last;
    struct path_node *p, *q;

    if(i == j){
        fprintf(f, "(%d  %d)\n", i+1, sum);
        return 0;
    } else{
        path_first = (struct path_node *) malloc(sizeof(struct path_node));
        path_last = (struct path_node *) malloc(sizeof(struct path_node));
        path_first->u = i;
        path_last->u = j;
        path_last->next = NULL;

        p = path_last;

        k = 0;
        while (sourceNodeQueue.sourceNode[k].u != j){
            k++;
        }
        sum = sourceNodeQueue.sourceNode[k].d;

        if(sourceNodeQueue.sourceNode[k].d == 100000){
            fprintf(f, "(there is no path between %d and %d)\n", i + 1, j + 1);
            return 0;
        }
    }

    while (sourceNodeQueue.sourceNode[k].pi != i) {
        q = p;
        p = (struct path_node *) malloc(sizeof(struct path_node));
        p->u = sourceNodeQueue.sourceNode[k].pi;
        p->next = q;

        k = 0;
        while (sourceNodeQueue.sourceNode[k].u != p->u) {
            k++;
        }
    }

    path_first->next = p;

    p = path_first;

    fprintf(f, "(");
    while (p->next != NULL) {
        fprintf(f, "%d, ", p->u + 1);
        p = p->next;
    }
    fprintf(f, "%d  %d)\n", p->u + 1, sum);

//    p = path_first;
//    q = p->next;
//    while (p != NULL){
//        free(p);
//        p = q;
//        q = p->next;
//    }

    return 0;

}

struct source_node_queue *johnson(struct graph G)
{
    int i, j;
    struct node *no;
    struct edge *ed;
    struct graph G_new = new_graph(G);
    struct source_node_queue *source_john = (struct source_node_queue*)malloc(sizeof(struct source_node_queue)*(G.size - 1));
    
    struct source_node *source = (struct source_node *)malloc(sizeof(struct source_node)*G_new.size);

    if(bellman_ford(G_new, G_new.size - 1, source) == 0){
        printf("the input graph contains a negative-weight cycle\n");
        return 0;
    } else{
        for(no = G_new.first; no != G_new.last; no = no->next){
            ed = no->e;
            while (ed != NULL){
                ed->w = ed->w + source[no->u].d - source[ed->v].d;
                ed = ed->next;
            }
        }

        for(i = 0; i < G.size; i++){
            source_john[i] = dijkstra(G_new, i);
        }

        for(i = 0; i < G.size; i++){
            for(j = 0; j < G.size; j++){
                if(source_john[i].sourceNode[j].d != 100000) {
                    source_john[i].sourceNode[j].d =
                            source_john[i].sourceNode[j].d - source[i].d + source[source_john[i].sourceNode[j].u].d;
                }
            }
        }

    }
    return source_john;

}

#endif //MAIN_C_JOHNSON_H
