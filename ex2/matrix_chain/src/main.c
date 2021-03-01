#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "matrix_chain.h"

void print_optimal(int **s, int i, int j, FILE *f)
    // 将从第 i 到第 j 位矩阵的最佳链乘方案写入文件 f
{
    if(i==j){
        fprintf(f, "A%d", i);
    }
    else{
        fprintf(f,"(");
        print_optimal(s, i, s[i-1][j-1]+1,f);
        print_optimal(s, s[i-1][j-1]+2, j, f);
        fprintf(f,")");
    }
}

int main()
{

    // 文件指针
    FILE *f1=fopen("../input/2_1_input.txt","r");
    FILE *f2=fopen("../output/result.txt","w");
    FILE *f3=fopen("../output/time.txt","w");

    int i,j,k,l,n;
    double time;
    long long *p;
    long long **m;
    int **s;

    // 计时相关
    LARGE_INTEGER time_start;
    LARGE_INTEGER time_over;
    double dqFreq;
    LARGE_INTEGER fre;
    QueryPerformanceFrequency(&fre);
    dqFreq=(double)fre.QuadPart;

    // i 控制从文件读入的问题序号
    for(i=0;i<5;i++){

        // 读入矩阵链大小
        fscanf(f1,"%d",&n);
        p=(long long *)malloc(sizeof(long long)*(n+1));
        for(j=0;j<=n;j++){
            fscanf(f1,"%lld",&p[j]);
        }

        // m, s 为二维数组
        // m 为矩阵乘法次数, s 为最佳分割下标
        m=(long long **)malloc(sizeof(long long *)*n);
        s=(int **)malloc(sizeof(int *)*(n));
        for(j=0;j<n;j++){
            m[j]=(long long *)malloc(sizeof(long long )*n);
        }
        for(j=0;j<n;j++){
            s[j]=(int *)malloc(sizeof(int)*(n));
        }

        QueryPerformanceCounter(&time_start);    // 计时开始
        matrix_chain_order(p, m, s, n);          // 矩阵链乘问题求解
        QueryPerformanceCounter(&time_over);     // 计时结束
        time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;  //转化为 μs 单位

        // 最佳乘法次数和链乘方案写入文件
        fprintf(f2, "%lld\n", m[0][n-1]);
        print_optimal(s, 1, n, f2);
        fprintf(f2,"\n");

        // 运行时间写入文件
        fprintf(f3, "%.2lf μs\n", time);

        // 对于 n = 5 情形，输出 m 和 s 表
        if(i == 0){

            // 输出 m 表
            printf("m:\n");
            for(j=0;j<n;j++){
                for(l=0;l<j;l++){
                    printf("\t\t");
                }
                for(k=j;k<n;k++){

                    printf("%15lld ", m[j][k]);
                }
                printf("\n");
            }

            // 输出 s 表
            printf("s:\n");
            for(j=1;j<n;j++){
                for(l=0;l<j;l++){
                    printf("\t");
                }
                for(k=j;k<n;k++){
                    printf("%d\t", s[j][k]);
                }
                printf("\n");
            }

        }

        free(m);
        free(s);
        free(p);
    }

    fclose(f1);
    fclose(f2);
    fclose(f3);
    return 0;
}