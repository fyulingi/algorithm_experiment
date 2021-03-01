#ifndef MAIN_C_GRAPH_GENERATE_H
#define MAIN_C_GRAPH_GENERATE_H

#include <stdlib.h>

struct edge{
    int v;
    int w;
    struct edge *next;
};

struct node{
    int u;
    struct edge *e;
    struct node *next;
};


struct graph{   // 邻接表表示
    int size;
    int edge_num;
    struct node *first;
    struct node *last;
};


int *rand_num_generate(int n, int m)
// 生成 n 个互不相同的正整数, 范围在 0 - m-1
{
    int i,j,temp;
    int list[m];
    int *vector=(int *)malloc(sizeof(int)*n);
    for (i = 0; i < m; i++) {
        list[i] = i;
    }

    for (i = 0; i < m; i++) {
        j = i + rand() % (m - i);
        temp = list[i];
        list[i] = list[j];
        list[j] = temp;
    }

    for (i = 0; i < n; i++) {
        vector[i] = list[i];
    }

    return vector;
}

struct graph graph_generate(int n, int m, int a, int b)
        // 生成 n 个节点, 每个节点 m 条边的无负值环的有向图
        // 边的权值 [a, b]
{
    struct graph G;
    int i, j, k;
    int *temp;
    struct edge *ed;
    struct node *no;

    for(i = 0; i < n; i++){

        if(i == 0) {
            G.first = (struct node *) malloc(sizeof(struct node));
            G.first->next = NULL;
            G.first->u = i;
            G.last = G.first;
            no = G.first;
        } else {
            no = (struct node *) malloc(sizeof(struct node));
            no->next = NULL;
            no->u = i;
            G.last->next = no;
            G.last = no;
        }

        // 生成边
        temp = rand_num_generate(m, n);

        for(k = 0; k < m; k++){
            if(k == 0){
                no->e = (struct edge *)malloc(sizeof(struct edge));
                ed = no->e;
                ed->w = rand() % 51;
                ed->next = NULL;
                ed->v = temp[k];

            } else{
                ed->next = (struct edge *)malloc(sizeof(struct edge));
                ed = ed->next;
                ed->w = rand() % (b - a + 1) + a;
                ed->next = NULL;
                ed->v = temp[k];
            }

        }

        free(temp);

    }

    G.size = n;
    G.edge_num = n * m;

    return G;
}

void graph_print(struct graph G, FILE *f)
{
    int i;
    struct node *no;
    struct edge *ed;

    no = G.first;
    for(i = 0; i < G.size; i++){
        ed = no->e;
        while (ed != NULL){
            fprintf(f, "(%d, %d, %d)\n", i+1, ed->v + 1, ed->w);
            ed = ed->next;
        }
        no = no->next;
    }
}

#endif //MAIN_C_GRAPH_GENERATE_H
