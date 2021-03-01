#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "quick_sort.h"
#include "heap_sort.h"
#include "insertion_sort.h"
#include "merge_sort.h"
#include "counting_sort.h"
#include "random_num.h"

char* join(char *s1, char *s2)
    // 连接字符串
{   char *result = (char *) malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);

    return result;
}

int main(){
    int choice;
    int i,j,k,*data,n;
    FILE *f;
    double time[6];

    LARGE_INTEGER time_start;	//开始时间
    LARGE_INTEGER time_over;
    double dqFreq;		//计时器频率
    LARGE_INTEGER fre;	//计时器频率
    QueryPerformanceFrequency(&fre);
    dqFreq=(double)fre.QuadPart;

    int scale[6]={3,6,9,12,15,18};
    char time_txt[]="time.txt";
    int (*function[5])(int *, int ) = {insertion_sort, heap_sort, quick_sort, merge_sort, counting_sort};
    char sort_name[5][40]={"../output/insertion_sort/", "../output/heap_sort/", "../output/quick_sort/", "../output/merge_sort/", "../output/counting_sort/"};
    char file_sort[6][15]={"result_3.txt","result_6.txt","result_9.txt","result_12.txt","result_15.txt","result_18.txt",};

    // 菜单界面, 0 退出, 1 生成随机数文件, 2 五种排序
    printf("input a num to do something:\n");
    printf("0 to exit\n1 to generate a random number file\n2 to sort by 5 methods\n");
    scanf("%d",&choice);

    while (choice!=0) {
        switch (choice) {
            case 0:
                exit(0);
            case 1:
                  //  创建随机数文件
                f = fopen("../input/input.txt", "w");
                random_num_generate(f, 1 << 18);
                fclose(f);
                break;
            case 2:
                for (i = 0; i < 5; i++) {
                    //  5种排序算法
                    for (j = 0; j < 6; j++) {
                        //  读取文件
                        f = fopen("../input/input.txt", "r");
                        n = 1 << scale[j];
                        data = (int *) malloc(sizeof(int) * (n));
                        for (k = 0; k < n; k++) {
                            fscanf(f, "%d", &data[k]);  // need to add & before a
                        }
                        fclose(f);


                        // 排序并记录时间
                        QueryPerformanceCounter(&time_start);    //计时开始
                        function[i](data, n - 1);
                        QueryPerformanceCounter(&time_over);    //计时结束
                        time[j] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;


                        // 将排序结果写入 result_n.txt 文件
                        f = fopen(join(sort_name[i], file_sort[j]), "w");
                        for (k = 0; k < n; k++) {
                            fprintf(f, "%d\n", data[k]);
                        }
                        fclose(f);
                        free(data);

                    }


                    // 将时间写入 time.txt 文件
                    f = fopen(join(sort_name[i], time_txt), "w");
                    for (k = 0; k < 6; k++) {
                        fprintf(f, "%.2lf", time[k]);
                        fprintf(f," μs\n");
                    }
                    fclose(f);
                }
                break;
            default: exit(0);
        }
        printf("input a num to do something:\n");
        printf("0 to exit\n1 to generate a random number file\n2 to sort by 5 methods\n");
        scanf("%d", &choice);
    }
    return 0;
}