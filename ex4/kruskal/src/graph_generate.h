//
// Created by fyuling on 2021/1/1.
//

#ifndef EX1_GRAPH_GENERATE_H
#define EX1_GRAPH_GENERATE_H

#include <stdlib.h>

struct edge{
    int u;
    int v;
    int w;
};

struct graph{
    int size;
    int **weight;
    int edge_num;
    struct edge *E;
};

int *edge_index_generate(int i, int n){
    // 从 0 - i-1 中, 生成 n 个数
    int j, k, temp;
    int *data = (int *)malloc(sizeof(int) * n);

    int list[i];
    for(j = 0; j < i; j++) {
        list[j] = j;
    }


    for(j = 0; j < i; j++) {
        k = j + rand() % (i - j);
        temp = list[j];
        list[j] = list[k];
        list[k] = temp;
    }

    for(j = 0; j < n; j++) {
        data[j] = list[j];
    }

    return data;
}

struct graph graph_generate(int graph_size)
        // 生成规模为 graph_size 的随机无向联通图
        // 连通性已在算法运行过程中保证
{

    int i, j, k, flag, weight;
    int *edge_index;

    struct graph G;
    G.size = graph_size;
    G.edge_num = 0;

    // generate weight
    G.weight = (int **)malloc(sizeof(int *) * graph_size);
    for(i = 0; i < graph_size; i++){
        G.weight[i] = (int *)malloc(sizeof(int) * graph_size);
    }

    for(i = 0; i < graph_size; i++){
        for(j =0; j < graph_size; j++){
            G.weight[i][j] = 0;  // 表示无边连接
        }
    }


    int *count_edge = (int *)malloc(sizeof(int) * graph_size);
    for(i = 0; i < graph_size; i++){
        count_edge[i] = 0;
    }

    for(i = 1; i < graph_size; i++){
        edge_index = edge_index_generate(i, i/2 +1);
        flag = 1;
        for(j = 0; j < i/2; j++){
            if(count_edge[edge_index[j]] < graph_size/2){
                weight = 1 + rand() % 20;
                G.weight[i][edge_index[j]] = weight;
                G.weight[edge_index[j]][i] = weight;
                count_edge[i]++;
                count_edge[edge_index[j]]++;
                flag = 0;
            }
        }
        if(flag == 1){
            // 表示目前 i 节点加入, 尚未构成连通图
            for(j = 0; j < i; j++){
                if(count_edge[j] < graph_size/2){
                    weight = 1 + rand() % 20;
                    G.weight[i][j] = weight;
                    G.weight[j][i] = weight;
                    count_edge[i]++;
                    count_edge[j]++;
                    break;
                }
            }
            if(j == i){
                printf("error\n");
            }
        }
    }


    free(count_edge);

    for(i = 0; i < G.size - 1; i++){
        for(j = i + 1; j < G.size; j++){
            if(G.weight[i][j] > 0){
                G.edge_num++;
            }
        }
    }

    G.E = (struct edge *)malloc(sizeof(struct edge) * G.edge_num);
    k = 0;
    for(i = 0; i < G.size - 1; i++){
        for(j = i + 1; j < G.size; j++){
            if(G.weight[i][j] > 0){
                G.E[k].u = i;
                G.E[k].v = j;
                G.E[k].w = G.weight[i][j];
                k++;
            }
        }
    }

    return G;

}


void graph_print(struct graph G, FILE *f){
    int i, j;
    for(i = 0; i < G.size-1; i++){
        for(j = i+1; j < G.size; j++){
            if(G.weight[i][j] > 0){
                fprintf(f, "(%d, %d, %d)\n", i+1, j+1, G.weight[i][j]);
            }
        }
    }



}


#endif //EX1_GRAPH_GENERATE_H