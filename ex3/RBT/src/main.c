#include <stdio.h>
#include <windows.h>

#include "rand_num_generate.h"
#include "RBT.h"
#include "walk.h"


int main() {

    struct RBT T;
    int n=100; //length of rand_num writen to the "input.txt"
    int i, j;
    int length_to_read[5]={20, 40, 60, 80, 100};
    int *data_to_read, *data_to_delete, *data_to_delete_index;
    FILE *f1, *f2, *f3, *f4, *f5;

    // 计时相关
    double time;
    LARGE_INTEGER time_start;
    LARGE_INTEGER time_over;
    double dqFreq;
    LARGE_INTEGER fre;
    QueryPerformanceFrequency(&fre);
    dqFreq=(double)fre.QuadPart;



    int choice;
    printf("Input a num to do something:\n0:exit\t1:generate rand num\t2:insert and delete\n");
    scanf("%d",&choice);

    while(choice!=0){
        switch (choice) {
            case 1: {
                f1=fopen("../input/input.txt","w");
                int *raw_data=rand_num_generate(n, 300);
                for(i=0;i<n;i++){
                    fprintf(f1,"%d\n",raw_data[i]);
                }
                fclose(f1);
                break;
            }
            case 2:{
                f2 = fopen("../output/inorder.txt", "w");
                f3 = fopen("../output/delete_data.txt", "w");
                f4 = fopen("../output/time1.txt", "w");
                f5 = fopen("../output/time2.txt", "w");

                for(i = 0; i < 5; i++) {

                    // 读入要插入的数据
                    n = length_to_read[i];
                    data_to_read = (int *) malloc(sizeof(int) * n);

                    f1 = fopen("../input/input.txt", "r");
                    for (j = 0; j < n; j++) {
                        fscanf(f1, "%d", &data_to_read[j]);
                    }
                    fclose(f1);

                    // 开始创建红黑树并插入节点
                    T = create();


                    QueryPerformanceCounter(&time_start);    // 计时开始
                    for (j = 0; j < n; j++) {
                        T = insert(T, data_to_read[j]);
                    }
                    QueryPerformanceCounter(&time_over);     // 计时结束
                    time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;  //转化为 μs 单位

                    fprintf(f4, "%.2f μs\n", time);

                    // 中序遍历并写入文件
                    inorder_tree_walk(T, T.root, f2);
                    fprintf(f2, "\n");

                    // 要删除的节点关键字
                    data_to_delete_index = rand_num_generate(n / 4, n);
                    data_to_delete = (int *) malloc(sizeof(int) * (n / 4));

                    for (j = 0; j < n / 4; j++) {
                        data_to_delete[j] = data_to_read[data_to_delete_index[j] - 1];
                        fprintf(f3, "%d ", data_to_delete[j]);
                    }
                    fprintf(f3, "\n");

                    // 删除操作
                    QueryPerformanceCounter(&time_start);    // 计时开始
                    for (j = 0; j < n / 4; j++) {
                        T = delete(T, data_to_delete[j]);
                    }
                    QueryPerformanceCounter(&time_over);     // 计时结束
                    time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;  //转化为 μs 单位

                    fprintf(f5, "%.2f μs\n", time);

                    // 中序遍历
                    inorder_tree_walk(T, T.root, f3);
                    fprintf(f3, "\n");


                }

                fclose(f2);
                fclose(f3);
                fclose(f4);
                fclose(f5);

                break;

            }
            default:{
                printf("Please input a right num\n");
            }

        }
        printf("Input a num to do something:\n0:exit\t1:generate rand num\t2:insert and delete\n");
        scanf("%d",&choice);
    }
    printf("Thanks for using this program!\nGood good study, day day up!\n");

    return 0;
}