//
// Created by fyuling on 2020/12/19.
//

#ifndef EX1_WALK_H
#define EX1_WALK_H

#include <stdio.h>
#include "RBT.h"


void print_color(struct node *x, FILE *f)
{
    if(x->color==0) {
        fprintf(f,"red    ");
    } else{
        fprintf(f,"black  ");
    }
}

void inorder_tree_walk(struct RBT T, struct node *x, FILE *f)
{
    if(x!=T.nil){
        inorder_tree_walk(T,x->left,f);
        fprintf(f,"%d\t",x->key);
        print_color(x,f);
        fprintf(f,"%d\n",x->size);
        inorder_tree_walk(T,x->right,f);
    }
}

#endif //EX1_WALK_H
