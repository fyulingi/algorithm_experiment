#ifndef EX2_FFT_H
#define EX2_FFT_H

#include <math.h>
#include <stdlib.h>
#define PI 3.1415926525


struct comp{
    // 定义一个结构体, 表示复数
    double re;
    double im;
};

struct comp comp_plus(struct comp x, struct comp y)
{
    // 输入两个复数 x, y, 返回复数 x+y
    struct comp z;
    z.re=x.re+y.re;
    z.im=x.im+y.im;
    return z;
}

struct comp comp_subt(struct comp x, struct comp y)
{
    // 输入两个复数 x, y, 返回复数 x-y
    struct comp z;
    z.re=x.re-y.re;
    z.im=x.im-y.im;
    return z;
}

void comp_value(struct comp *x, struct comp y)
{
    // 将复数 y 的数值存储到 x 对应地址
    (*x).re=y.re;
    (*x).im=y.im;
}
struct comp comp_multi(struct comp x, struct comp y)
{
    // 输入两个复数 x, y, 返回复数 x*y
    struct comp z;
    z.re=x.re*y.re-x.im*y.im;
    z.im=x.im*y.re+x.re*y.im;
    return z;
}

int recursive_FFT(struct comp *data, struct comp *y, int n)
{
    // 输入 data 为一多项式的系数表示(复数), 返回 y, 表示 data 的 DFS
    // n-1 为多项式的次数, n 为 2 的幂
    int i;
    int m=n/2;

    if(n==1)
    {
        y[0].re=data[0].re;
        y[0].im=data[0].im;
        return 0;
    }

    // omega_n 表示 n 次单位根
    struct comp omega_n, omega, temp;
    omega.re=1,omega.im=0;
    omega_n.re=cos(2*PI/n),omega_n.im=sin(2*PI/n);

    struct comp *a0=(struct comp *)malloc(sizeof(struct comp)*m);
    struct comp *a1=(struct comp *)malloc(sizeof(struct comp)*m);

    for(i=0;i<m;i++){
        comp_value(&a0[i],data[2*i]);
        comp_value(&a1[i],data[2*i+1]);
    }

    struct comp *y0=(struct comp *)malloc(sizeof(struct comp)*m);
    recursive_FFT(a0,y0,m);
    free(a0);
    struct comp *y1=(struct comp *)malloc(sizeof(struct comp)*m);
    recursive_FFT(a1,y1,m);
    free(a1);

    for(i=0;i<m;i++){
        comp_value(&temp, comp_multi(omega, y1[i]));
        comp_value(&(y[i]), comp_plus(y0[i], temp));
        comp_value(&(y[m+i]), comp_subt(y0[i], temp));
        comp_value(&omega, comp_multi(omega,omega_n));
    }
    free(y0);
    free(y1);

    return 0;
}


#endif //EX2_FFT_H
