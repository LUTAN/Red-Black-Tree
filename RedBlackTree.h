//
//  RedBlackTree.h
//  SkipList
//
//  Created by lutan on 14-7-27.
//  Copyright (c) 2014年 Lutan. All rights reserved.
//

#ifndef __SkipList__RedBlackTree__
#define __SkipList__RedBlackTree__

#include <iostream>

struct RBTNode {
    int data;
    bool isRed;
    RBTNode *parent;
    RBTNode *leftChild;
    RBTNode *rightChild;
};

class RBTree{
private:
    RBTNode *root;
    
    void insertRoot(RBTNode *n);
    void insertWithBlackParents(RBTNode *n);
    void insertWithRedParentAndUncle(RBTNode *n);
    void insertWithLeftRotation(RBTNode *n);
    void insertWithRightRotation(RBTNode *n);
public:
    RBTree(){root = NULL;};
    RBTree(int a);
    RBTree(RBTNode root);
    RBTree(const RBTree &rbTree);
    ~RBTree();
    
    bool getRootData(int *a) const;
    void insertSertion(int a);
    void removeNode(int a);
    void removeAllNodes();
    void printTree();
};


#endif /* defined(__SkipList__RedBlackTree__) */
