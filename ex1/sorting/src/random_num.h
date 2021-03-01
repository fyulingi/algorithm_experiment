#ifndef RANDOM_NUM_H_RANDOM_NUM_H
#define RANDOM_NUM_H_RANDOM_NUM_H

#include <stdlib.h>

void random_num_generate(FILE *f, int n)  //generate n random num range from 0 to m
{
    int i;
    srand(1);
    for(i=0;i<n-1;i++){
        fprintf(f,"%d\n",rand());
    }
    fprintf(f,"%d",rand());
}

#endif //RANDOM_NUM_H_RANDOM_NUM_H
