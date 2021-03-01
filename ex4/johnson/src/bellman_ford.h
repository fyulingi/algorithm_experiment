#ifndef MAIN_C_BELLMAN_FORD_H
#define MAIN_C_BELLMAN_FORD_H

#include "graph_generate.h"

struct source_node{
    int d;
    int pi;
};

void init(struct graph G, int s, struct source_node *source)
{
    for (int i = 0; i < G.size; ++i) {
        source[i].d = 100000;
        source[i].pi = G.size;         // 代表 NULL
    }

    source[s].d = 0;
}

int relax(struct source_node *source, int i, int j, int w)
{
    if(source[i].d == 100000){
        return 0;   // infinity + num = infinity
    } else if (source[j].d > source[i].d + w) {
        source[j].d = source[i].d + w;
        source[j].pi = i;
        return 1;
    }
    return 0;
}

int bellman_ford(struct graph G, int s, struct source_node *source)
{
    int i;
    struct node *no;
    struct edge *ed;

    init(G, s, source);

    for(i = 0; i < G.size - 1; i++){
        for(no = G.first; no != NULL; no = no->next){
            ed = no->e;
            while (ed != NULL){
                relax(source, no->u, ed->v, ed->w);
                ed = ed->next;
            }
        }
    }

    for(no = G.first; no != NULL; no = no->next){
        ed = no->e;
        while (ed != NULL){
            if(source[ed->v].d > source[no->u].d + ed->w){
                return 0;
            }
            ed = ed->next;
        }
    }

    return 1;

}

#endif //MAIN_C_BELLMAN_FORD_H
