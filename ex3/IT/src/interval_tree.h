//
// Created by fyuling on 2020/12/10.
//

#ifndef EX2_INTERVAL_TREE_H
#define EX2_INTERVAL_TREE_H

#include <stdlib.h>

int three_num_max(int a, int b, int c)
{
    int x;
    if(a > b) x = a;
    else x = b;
    if(x > c) return x;
    else return c;
}

struct node{
    // low is the key
    int low;
    int high;
    int max;
    struct node *p;
    struct node *left;
    struct node *right;
    int color; //0: red, 1:black

};

struct IT{
    //interval tree
    struct node *root;
    struct node *nil;
};

struct IT create()
{
    struct IT T;

    T.root=(struct node*)malloc(sizeof(struct node));

    T.nil=T.root;
    T.root->right=T.nil;
    T.root->left=T.nil;
    T.root->color=1;
    T.root->p=T.nil;
    T.root->max = 0;

    return T;

}

struct IT LEFT_ROTATE(struct IT T, struct node *x){
    struct node *y = x->right;
    x->right=y->left;
    if(y->left!=T.nil){
        y->left->p=x;
    }
    y->p=x->p;

    if(x->p==T.nil){
        T.root=y;
    } else if(x==x->p->left){
        x->p->left=y;
    } else{
        x->p->right=y;
    }
    y->left=x;
    x->p=y;

    y->max = x->max;
    x->max = three_num_max(x->high, x->left->max, x->right->max);

    return T;

}

struct IT RIGHT_ROTATE(struct IT T, struct node *x){
    struct node *y = x->left;
    x->left=y->right;
    if(y->right!=T.nil){
        y->right->p=x;
    }
    y->p=x->p;

    if(x->p==T.nil){
        T.root=y;
    } else if(x==x->p->left){
        x->p->left=y;
    } else{
        x->p->right=y;
    }
    y->right=x;
    x->p=y;

    y->max = x->max;
    x->max = three_num_max(x->high, x->left->max, x->right->max);

    return T;
}

struct IT IT_INSERT_FIXUP(struct IT T, struct node *z){
    struct node *y;
    while (z->p->color==0){
        if(z->p==z->p->p->left){
            y=z->p->p->right;
            if(y->color==0) {  // 0: red
                z->p->color=1;
                y->color=1;
                z->p->p->color=0;
                z=z->p->p;
            } else {
                if (z == z->p->right) {
                    z = z->p;
                    T = LEFT_ROTATE(T, z);

                }

                z->p->color = 1;
                z->p->p->color = 0;
                T = RIGHT_ROTATE(T, z->p->p);
            }


        } else{
            y=z->p->p->left;
            if(y->color==0) {  // 0: red

                z->p->color=1;
                y->color=1;
                z->p->p->color=0;
                z=z->p->p;
            } else {
                if (z == z->p->left) {
                    z = z->p;
                    T = RIGHT_ROTATE(T, z);

                }

                z->p->color = 1;
                z->p->p->color = 0;
                T = LEFT_ROTATE(T, z->p->p);
            }

        }
    }
    T.root->color=1;
    return T;
}

struct IT IT_INSERT(struct IT T, struct node *z)
//向区间树插入 z
{
    struct node *y=T.nil;
    struct node *x=T.root;
    while (x!=T.nil){
        y=x;
        if(z->low<x->low){
            x=x->left;
        }else{
            x=x->right;
        }

    }
    z->p=y;
    if(y==T.nil){
        T.root=z;
    } else if(z->low<y->low){
        y->left=z;
    } else y->right=z;
    z->left=T.nil;
    z->right=T.nil;
    z->color=0;
    while(y!=T.nil){
        y->max = three_num_max(y->high, y->left->max, y->right->max);
        y=y->p;
    }
    T=IT_INSERT_FIXUP(T, z);
    return T;
}

struct IT insert(struct IT T, int n1, int n2)
{
    struct node *z=(struct node*)malloc(sizeof(struct node));
    z->low=n1;
    z->high=n2;
    z->max=n2;
    T=IT_INSERT(T,z);
    return T;
}

struct node *MINIMUM(struct IT T, struct node *z)
{
    struct node *x=z;
    while(x->left!=T.nil){
        x=x->left;
    }
    return x;
}

struct node *SUCCESSOR(struct IT T, struct node *z)
{
    struct node *x=z,*y;
    if(x->right!=T.nil){
        return MINIMUM(T, x->right);
    }
    y=x->p;
    while (y!=T.nil&&x==y->right){
        x=y;
        y=y->p;
    }
    return y;
}

struct IT IT_DELETE_FIXUP(struct IT T, struct node *x)
{
    struct node *w;
    while (x!=T.root&&x->color==1){
        if(x==x->p->left){
            w=x->p->right;
            if(w->color==0){
                w->color=1;
                x->p->color=0;
                T=LEFT_ROTATE(T,x->p);
                w=x->p->right;
            }
            if(w->left->color==1&&w->right->color==1){
                w->color=0;
                x=x->p;
            } else {
                if (w->right->color == 1) {
                    w->left->color = 1;
                    w->color = 0;
                    T=RIGHT_ROTATE(T, w);
                    w = x->p->right;
                }
                w->color=x->p->color;
                x->p->color=1;
                w->right->color=1;
                T=LEFT_ROTATE(T,x->p);
                x=T.root;
            }

        } else{
            w=x->p->left;
            if(w->color==0){
                w->color=1;
                x->p->color=0;
                T=RIGHT_ROTATE(T,x->p);
                w=x->p->left;
            }
            if(w->right->color==1&&w->left->color==1){
                w->color=0;
                x=x->p;
            } else {
                if (w->left->color == 1) {
                    w->right->color = 1;
                    w->color = 0;
                    T=LEFT_ROTATE(T, w);
                    w = x->p->left;
                }
                w->color=x->p->color;
                x->p->color=1;
                w->left->color=1;
                T=RIGHT_ROTATE(T,x->p);
                x=T.root;
            }
        }
    }
    x->color=1;
    return T;
}

struct IT IT_DELETE(struct IT T, struct node *z)
{
    struct node *x,*y,*w;
    if(z->left==T.nil||z->right==T.nil){
        y=z;
    } else y=SUCCESSOR(T, z);
    if(y->left!=T.nil){
        x=y->left;
    } else x=y->right;
    x->p=y->p;
    if(y->p==T.nil){
        T.root=x;
    } else {
        if (y == y->p->left) {
            y->p->left = x;
        } else y->p->right = x;
    }
    if(y!=z){
        z->low = y->low;
        z->high = y->high;
    }

    w=y->p;
    while (w!=T.nil){
        w->max = three_num_max(w->high, w->left->max, w->right->max);
        w=w->p;
    }

    if(y->color==1){
        T=IT_DELETE_FIXUP(T, x);
    }
    return T;
}
struct node *find(struct IT T, int n1, int n2)
{
    struct node *x=T.root;
    while (x!=T.nil){
        if(x->low==n1){
            if(x->high!=n2){
                return T.nil;
            } else return x;
        } else if(x->low < n1){
            x=x->right;
        } else{
            x=x->left;
        }
    }
    return T.nil;
}

struct IT delete(struct IT T, int n1, int n2)
{
    struct node *x=find(T,n1, n2);
    if(x!=T.nil){
        T = IT_DELETE(T,x);
    }else{
        printf("There is not a node has low value %d and high value %d in the tree!\n", n1, n2);
    }
    return T;
}

int overlap_or_not(struct node *x, int n1, int n2)
{
    // 判断 x 区间是否和 [n1, n2] 重叠, 有重叠返回 1, 否则返回 0
    if(x->high<n1) return 0;
    else if(n2 < x->low) return 0;
    else return 1;
}
struct node *IT_search(struct IT T, int n1, int n2)
{
    struct node *x = T.root;
    while (x != T.nil && !overlap_or_not(x, n1, n2)){
        if(x->left!=T.nil && x->left->max>=n1){
            x=x->left;
        } else x=x->right;
    }
    return x;
}

void search(struct IT T, int n1, int n2, FILE *f)
{
    struct node *x=IT_search(T, n1, n2);
    if(x == T.nil){
        fprintf(f, "NULL\n");
    } else{
        fprintf(f, "%d %d\n", x->low, x->high);
    }

}
#endif //EX2_INTERVAL_TREE_H
