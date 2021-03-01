//
// Created by fyuling on 2020/12/19.
//

#ifndef EX1_RAND_NUM_GENERATE_H
#define EX1_RAND_NUM_GENERATE_H


#include <stdlib.h>

int *rand_num_generate(int n, int m)
// 生成 n 个互不相同的正整数, 范围在 1 - m
{
    int i,j,temp;
    int list[m];
    int *vector=(int *)malloc(sizeof(int)*n);
    for (i = 0; i < m; i++) {
        list[i] = i+1;
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

#endif //EX1_RAND_NUM_GENERATE_H
