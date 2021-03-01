//
// Created by fyuling on 2020/12/10.
//

#ifndef EX2_WALK_H
#define EX2_WALK_H

#include <stdio.h>
#include "interval_tree.h"

void inorder_tree_walk(struct IT T, struct node *x, FILE *f)
{
    if(x != T.nil){
        inorder_tree_walk(T, x->left, f);
        fprintf(f, "%d %d %d\n", x->low, x->high, x->max);
        inorder_tree_walk(T, x->right, f);
    }
}

#endif //EX2_WALK_H
