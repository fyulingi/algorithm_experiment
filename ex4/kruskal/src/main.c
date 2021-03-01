#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "graph_generate.h"
#include "kruscal.h"



char *join(char *s1, char *s2)
// 连接字符串
{   char *result = (char *) malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);

    return result;
}


int main() {
    int i, j, weight;  // weight 记录最小生成树代价
    struct graph G;
    struct set A;
    struct set_node *p;
    FILE *f1, *f2, *f3 = fopen("../output/time.txt", "w");
    double time;

    LARGE_INTEGER time_start;	//开始时间
    LARGE_INTEGER time_over;
    double dqFreq;		//计时器频率
    LARGE_INTEGER fre;	//计时器频率
    QueryPerformanceFrequency(&fre);
    dqFreq=(double)fre.QuadPart;

    int input_size[4] = {8, 64, 128, 512};
    char file_name[4][8] = {"1.txt", "2.txt", "3.txt", "4.txt"};

    for(i = 0; i < 4; i++){
        G = graph_generate(input_size[i]);

        f1 = fopen(join("../input/input", file_name[i]), "w");
        graph_print(G, f1);
        fclose(f1);

        QueryPerformanceCounter(&time_start);    //计时开始
        A = kruscal(G);
        QueryPerformanceCounter(&time_over);    //计时结束
        time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;

        p = A.first;
        weight = 0;
        f2 = fopen(join("../output/result", file_name[i]), "w");
        for(j = 0; j < A.size; j++){
            fprintf(f2, "( %d, %d, %d)\n", p->u + 1, p->v + 1, p->w);
            weight = weight + p->w;
            p = p->next;
        }
        fprintf(f2, "%d", weight);
        fclose(f2);

        fprintf(f3, "%.2lf μs\n", time);
    }

    fclose(f3);

    return 0;
}
