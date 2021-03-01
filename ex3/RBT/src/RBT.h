//
// Created by fyuling on 2020/12/19.
//

#ifndef EX1_RBT_H
#define EX1_RBT_H

# include <stdlib.h>
# include <stdio.h>

struct node{
    int key;
    struct node *p;
    struct node *left;
    struct node *right;
    int color; // 0: red; 1: black
    int size;  //left.size+right.size+1
};

struct RBT{
    struct node *root;
    struct node *nil;
};


struct RBT create()
{
    struct RBT T;
    T.root=(struct node*)malloc(sizeof(struct node));

    T.nil=T.root;
    T.root->right=T.nil;
    T.root->left=T.nil;
    T.root->color=1;
    T.root->p=T.nil;
    T.root->size=0;
    return T;

}

struct RBT LEFT_ROTATE(struct RBT T, struct node *x){
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
    y->size=x->size;
    x->size=x->left->size+x->right->size+1;
    return T;


}
struct RBT RIGHT_ROTATE(struct RBT T, struct node *x){
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
    y->size=x->size;
    x->size=x->left->size+x->right->size+1;
    return T;
}

struct RBT RB_INSERT_FIXUP(struct RBT T, struct node *z){
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
struct RBT RB_INSERT(struct RBT T, struct node *z)
//向红黑树插入 z
{
    struct node *y=T.nil;
    struct node *x=T.root;
    while (x!=T.nil){
        y=x;
        if(z->key<x->key){
            x=x->left;
        }else{
            x=x->right;
        }

    }
    z->p=y;
    if(y==T.nil){
        T.root=z;
    } else if(z->key<y->key){
        y->left=z;
    } else y->right=z;
    z->left=T.nil;
    z->right=T.nil;
    z->color=0;
    while(y!=T.nil){
        y->size+=1;
        y=y->p;
    }
    T=RB_INSERT_FIXUP(T, z);
    return T;
}

struct RBT insert(struct RBT T, int n)
{
    struct node *z=(struct node*)malloc(sizeof(struct node));
    z->key=n;
    z->size=1;
    T=RB_INSERT(T,z);
    return T;
}


struct node *MINIMUM(struct RBT T, struct node *z)
{
    struct node *x=z;
    while(x->left!=T.nil){
        x=x->left;
    }
    return x;
}

struct node *SUCCESSOR(struct RBT T, struct node *z)
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

struct RBT RB_DELETE_FIXUP(struct RBT T, struct node *x)
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

struct RBT RB_DELETE(struct RBT T, struct node *z)
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
        z->key=y->key;
    }
    w=y->p;
    while (w!=T.nil){
        w->size-=1;
        w=w->p;
    }
    if(y->color==1){
        T=RB_DELETE_FIXUP(T, x);
    }
    return T;
}

struct node *find(struct RBT T, int n)
{
    struct node *x=T.root;
    while (x!=T.nil){
        if(x->key==n){
            return x;
        } else if(x->key < n){
            x=x->right;
        } else{
            x=x->left;
        }
    }
    return T.nil;
}

struct RBT delete(struct RBT T, int n)
{
    struct node *x=find(T,n);
    if(x!=T.nil){
        T=RB_DELETE(T,x);
    }else{
        printf("There is not a node has value %d in the tree!\n", n);
    }
    return T;
}


#endif //EX1_RBT_H
