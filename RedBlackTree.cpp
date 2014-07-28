//
//  RedBlackTree.cpp
//  SkipList
//
//  Created by lutan on 14-7-27.
//  Copyright (c) 2014年 Lutan. All rights reserved.
//

#include "RedBlackTree.h"

RBTNode* createRoot(int a)
{
    RBTNode *node = new RBTNode;
    node->data = a;
    node->parent = NULL;
    node->leftChild = NULL;
    node->rightChild = NULL;
    return node;
}

RBTree::RBTree(int a)
{
    root = createRoot(a);
}

RBTree::RBTree(RBTNode node)
{
    root = createRoot(node.data);
}

RBTree::RBTree(const RBTree &rbTree)
{
    
}

RBTree::~RBTree()
{
    
}

bool RBTree::getRootData(int *a) const
{
    if (root) {
        *a = root->data;
        return true;
    }
    return false;
}

void RBTree:: insertSertion(int a)
{
    
}