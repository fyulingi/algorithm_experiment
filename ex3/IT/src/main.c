#include <stdio.h>
#include "rand_int_generate.h"
#include "interval_tree.h"
#include "walk.h"

int main() {

    struct IT T;
    int i, j;
    int n = 30;
    int *data_low = (int *)malloc(sizeof(int)*n);
    int *data_high = (int *)malloc(sizeof(int)*n);
    int data_search_low[3], data_search_high[3];
    FILE *f1, *f2, *f3, *f4;

    // 生成随机区间, 并写入文件
    f1 = fopen("../input/input.txt", "w");
    rand_int_generate(f1);
    fclose(f1);

    // 从文件中读入区间数据
    f1 = fopen("../input/input.txt", "r");
    for(i = 0; i < n; i++){
        fscanf(f1, "%d %d", &data_low[i], &data_high[i]);
    }
    fclose(f1);

    // 创建区间树, 并插入节点
    T=create();
    for(i = 0;i<n;i++){
        T=insert(T, data_low[i], data_high[i]);
    }

    // 中序遍历区间树
    f2=fopen("../output/inorder.txt", "w");
    inorder_tree_walk(T, T.root, f2);
    fclose(f2);

    // 随机删除 3 个区间
    int *index_to_delete=rand_index_generate(30, 3);

    for(i = 0; i < 3; i++){
        T=delete(T, data_low[index_to_delete[i]], data_high[index_to_delete[i]]);
    }

    // 将删除有关操作写入文件
    f3 = fopen("../output/delete_data.txt", "w");
    for(i =0; i<3;i++){
        fprintf(f3, "%d %d\n", data_low[index_to_delete[i]], data_high[index_to_delete[i]]);
    }
    inorder_tree_walk(T, T.root, f3);
    fclose(f3);

    // 随机生成 3 个区间进行查找, 将结果写入文件
    f4 = fopen("../output/search.txt", "w");
    rand_int_for_search_generate(data_search_low, data_search_high);
    fprintf(f4, "Three intervals to search:\n");
    for(i=0;i<3;i++){
        fprintf(f4, "%d %d\n", data_search_low[i], data_search_high[i]);
    }
    fprintf(f4, "\n");

    for(i=0;i<3;i++){
        search(T, data_search_low[i], data_search_high[i], f4);
    }
    fclose(f4);

    return 0;
}
