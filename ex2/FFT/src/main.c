#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "FFT.h"

int main()
{
    // 文件指针
    FILE *f1=fopen("../input/2_2_input.txt","r");
    FILE *f2=fopen("../output/result.txt","w");
    FILE *f3=fopen("../output/time.txt","w");

    // 计时相关
    LARGE_INTEGER time_start;
    LARGE_INTEGER time_over;
    double dqFreq;
    LARGE_INTEGER fre;
    QueryPerformanceFrequency(&fre);
    dqFreq=(double)fre.QuadPart;

    int i,j,n;
    double time;

    // comp 类型在“FFH.h”中有定义
    // p 存储当前问题的输入(复数格式)
    // y 存储当前问题的输出(复数格式)
    struct comp *p;
    struct comp *y;

    // i 控制从文件读入的问题序号
    for(i=0;i<6;i++){
        // 读入第 i 个问题, 并存储为comp类型
        fscanf(f1,"%d",&n);
        p=(struct comp *)malloc(sizeof(struct comp)*n);
        y=(struct comp *)malloc(sizeof(struct comp)*n);
        for(j=0;j<n;j++){
            fscanf(f1,"%lf",&(p[j].re));
            p[j].im=0;
        }

        QueryPerformanceCounter(&time_start);    // 计时开始
        recursive_FFT(p, y, n);
        QueryPerformanceCounter(&time_over);    // 计时结束
        time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;  //转化为 μs 单位

        // 将第 i 个问题的实部结果写入文件
        for(j=0;j<n;j++){
            fprintf(f2,"%lf ",y[j].re);
        }
        fprintf(f2,"\n");

        // 写入第 i 个问题的运行时间
        fprintf(f3,"%.2lf μs\n",time);

        free(p);
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);

    return 0;
}
