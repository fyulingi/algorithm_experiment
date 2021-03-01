//
// Created by fyuling on 2020/12/10.
//

#ifndef EX2_RAND_INT_GENERATE_H
#define EX2_RAND_INT_GENERATE_H

#include <stdlib.h>
#include <stdio.h>

int *rand_index_generate(int range, int n)
{
    int i,j,temp;
    int *data=(int *)malloc(sizeof(int)*n);
    int *list=(int *)malloc(sizeof(int)*range);

    for(i=0;i<range;i++){
        list[i]=i;
    }

    for (i = 0; i < range; i++) {
        j = i + rand() % (range - i);
        temp = list[i];
        list[i] = list[j];
        list[j] = temp;
    }

    for(i = 0; i < n; i++){
        data[i] = list[i];
    }


    return data;

}

int *rand_intnum_generate(int n)
// 生成 n 个互不相同的区间
{

    int i,j,temp;
    int list[45]; //储存可能出现的左端点值
    int *data = (int *)malloc(sizeof(int)*2*n);
    for(i = 0; i < 25; i++){
        list[i] = i;
    }
    for(i = 25; i < 45; i++){
        list[i] = i+5;
    }


    for (i = 0; i < 45; i++) {
        j = i + rand() % (45 - i);
        temp = list[i];
        list[i] = list[j];
        list[j] = temp;
    }

    for(i = 0; i < n; i++){
        data[i] = list[i];
        if(data[i] < 25){
            data[30 + i] = rand() % (25 - data[i]) + data[i] + 1;
        } else{
            data[30 + i] = rand() % (50 - data[i]) + data[i] + 1;
        }
    }

    return data;
}

void rand_int_generate(FILE *f)
{
    int i;
    int *raw_data = rand_intnum_generate(30);

    for(i = 0; i < 30; i++){
        fprintf(f, "%d %d\n", raw_data[i], raw_data[30 + i]);
    }
}

void rand_int_for_search_generate(int *data_search_low, int *data_search_high)
{
    // 生成三个区间, 存储在 data_search_low, data_search_high 中

    // 第一个区间位于 (25, 30) (i.e. [26, 29]) 中
    data_search_low[0] = rand() % 3 + 26;
    data_search_high[0] = data_search_low[0] + rand() % (29 - data_search_low[0]) +1;

    // 第二个区间位于 [0, 25] 中
    data_search_low[1] = rand() % 25;
    data_search_high[1] = data_search_low[1] + rand() % (25 - data_search_low[0]) +1;

    // 第三个区间位于 [30, 50] 中
    data_search_low[2] = rand() % 20 + 30;
    data_search_high[2] = data_search_low[2] + rand() % (50 - data_search_low[0]) +1;
}
#endif //EX2_RAND_INT_GENERATE_H
