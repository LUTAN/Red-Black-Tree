//
//  RedBlackTree.h
//  DataStructure
//
//  Created by lutan on 14-7-27.
//  Copyright (c) 2014年 Lutan. All rights reserved.
//

#ifndef __DataStructure__RedBlackTree__
#define __DataStructure__RedBlackTree__

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
    void rightRotation(RBTNode *node);
    void leftRotation(RBTNode *node);
    RBTNode* findNode(int a);
    void delete_one_child(RBTNode *n);
    void delete_case1(RBTNode *n);
    void delete_case2(RBTNode *n);
    void delete_case3(RBTNode *n);
    void delete_case4(RBTNode *n);
    void delete_case5(RBTNode *n);
    void delete_case6(RBTNode *n);
    
public:
    RBTree(){root = NULL;};
    RBTree(int a);
    RBTree(RBTNode root);
    RBTree(const RBTree &rbTree);
    ~RBTree();
    
    void insertSertion(int a);
    void removeNode(int a);
    void removeAllNodes();
    void copySubtree(RBTNode* des, RBTNode* source);
    void operator=(const RBTree &tree);
    bool checkRBTree() const;
    
    void printTree();
};


#endif /* defined(__DataStructure__RedBlackTree__) */
