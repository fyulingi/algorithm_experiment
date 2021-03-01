#include <stdio.h>
#include <math.h>
#include <string.h>
#include <windows.h>
#include "graph_generate.h"
#include "johnson.h"

char *join(char *s1, char *s2)
// 连接字符串
{
    char *result = (char *) malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);

    return result;
}

int main()
{
    int i, j, k, l;
    int edge_size;
    int input_size[4] = {27, 81, 243, 729};
    int log_size[2] = {5, 7};
    char name_1[4][3] = {"1", "2", "3", "4"};
    char name_2[2][7] = {"1.txt", "2.txt"};

    double time;
    LARGE_INTEGER time_start;	//开始时间
    LARGE_INTEGER time_over;
    double dqFreq;		//计时器频率
    LARGE_INTEGER fre;	//计时器频率
    QueryPerformanceFrequency(&fre);
    dqFreq=(double)fre.QuadPart;


    FILE *f1, *f2, *f3;
    struct graph G;
    struct source_node_queue *source_john;

    f3 = fopen("../output/time.txt", "w");
    for(i = 0; i < 4; i++){
        for(j = 0; j < 2; j++){
            edge_size = (int) (log(input_size[i])/log(log_size[j]));
            G = graph_generate(input_size[i], edge_size, 1, 50);

            f1 = fopen(join(join("../input/input", name_1[i]), name_2[j]), "w");
            graph_print(G, f1);
            fclose(f1);

            QueryPerformanceCounter(&time_start);    //计时开始
            source_john = johnson(G);
            QueryPerformanceCounter(&time_over);    //计时结束
            time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;

            fprintf(f3, "time for %d nodes, log %d N: %.2lf μs\n", input_size[i], log_size[j], time);

            f2 = fopen(join(join("../output/result", name_1[i]), name_2[j]), "w");
            for(k = 0; k < input_size[i]; k++){
                for(l = 0; l < input_size[i]; l++) {
                    print_path_i_j(source_john[k], k, l, f2);
                }
                fprintf(f2, "\n");
            }
            fclose(f2);

        }
    }

    fclose(f3);
    printf("Success!\n");
    return 0;
}
