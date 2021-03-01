#ifndef EX1_MATRIX_CHAIN_H
#define EX1_MATRIX_CHAIN_H

void matrix_chain_order(long long *p, long long **m, int **s, int n)
// 求解问题规模记录在 p 的矩阵连乘问题
// 最佳乘法次数记录在二维数组 m, 最佳分割下标记录在二维数组 s
// n 是矩阵链长度
{
    int i, j, k, l;

    long long q;
    for(i = 0; i < n; i++){
        m[i][i] = 0;
        s[i][i]=i;
    }

    for(l = 1; l < n; l++){
        for(i = 0; i <= n-l-1; i++){
            j = i+l;
            m[i][j] = m[i][i]+m[i+1][j]+p[i]*p[i+1]*p[j+1];
            s[i][j] = i;
            for(k = i+1; k <= j-1; k++){
                q = m[i][k]+m[k+1][j]+p[i]*p[k+1]*p[j+1];
                if(q < m[i][j]){
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}

#endif //EX1_MATRIX_CHAIN_H