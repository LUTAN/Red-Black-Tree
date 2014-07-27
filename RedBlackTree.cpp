//
//  RedBlackTree.cpp
//  SkipList
//
//  Created by lutan on 14-7-27.
//  Copyright (c) 2014年 Lutan. All rights reserved.
//

#include "RedBlackTree.h"
#include <vector>


RBTNode* createRoot(int a)
{
    RBTNode *node = new RBTNode;
    node->data = a;
    node->isRed = false;
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
    removeAllNodes();
}

bool RBTree::getRootData(int *a) const
{
    if (root) {
        *a = root->data;
        return true;
    }
    return false;
}

//---------------------------------------------------------------insertion-----------------------------------------------------------------
void RBTree:: insertSertion(int a)
{
    RBTNode *node = new RBTNode;
    node->data = a;
    node->leftChild = NULL;
    node->rightChild = NULL;
    node->isRed = true;
    
    if (root) {
        RBTNode *tmpnod = root;
        printTree();
        while (tmpnod) {
            if (a >= tmpnod->data) {
                if (tmpnod->rightChild) {
                    tmpnod = tmpnod->rightChild;
                }
                else
                {
                    tmpnod->rightChild = node;
                    node->parent = tmpnod;
                    break;
                }
            }
            else{
                if (tmpnod->leftChild) {
                    tmpnod = tmpnod->leftChild;
                }
                else
                {
                    tmpnod->leftChild = node;
                    node->parent = tmpnod;
                    break;
                }
            }
        }
        
    }
    else{
        node->parent = NULL;
    }
    
    insertRoot(node);
}

RBTNode *getGrandparent(const RBTNode *n)
{
    if ((n != NULL) && (n->parent != NULL))
        return n->parent->parent;
    else
        return NULL;
}

RBTNode *getUncle(const RBTNode *n)
{
    RBTNode *g = getGrandparent(n);
    if (g == NULL)
        return NULL; // No grandparent means no uncle
    if (n->parent == g->leftChild)
        return g->rightChild;
    else
        return g->leftChild;
}

void RBTree:: insertRoot(RBTNode *n)
{
    if (n->parent == NULL){
        n->isRed = false;
        root = n;
    }
    else{
        insertWithBlackParents(n);
    }
}

void RBTree::insertWithBlackParents(RBTNode *n)
{
    if (n->parent->isRed == false){
        return; /* Tree is still valid */
    }
    else{
        insertWithRedParentAndUncle(n);
    }
}

void RBTree::insertWithRedParentAndUncle(RBTNode *n)
{
    RBTNode *u = getUncle(n), *g;
    
    if ((u != NULL) && (u->isRed == true)) {
        n->parent->isRed = false;
        u->isRed = false;
        g = getGrandparent(n);
        g->isRed = true;
        insertRoot(g);
    } else {
        insertWithLeftRotation(n);
    }
}

void RBTree:: insertWithLeftRotation(RBTNode *n)
{
    RBTNode *g = getGrandparent(n);
    
    if ((n == n->parent->rightChild) && (n->parent == g->leftChild)) {
        rotate_left(n->parent);
        n = n->leftChild;
        
    } else if ((n == n->parent->leftChild) && (n->parent == g->rightChild)) {
        rotate_right(n->parent);
        n = n->rightChild;
    }
    insertWithRightRotation(n);
}

void RBTree:: insertWithRightRotation(RBTNode *n)
{
    RBTNode *g = getGrandparent(n);
    
    n->parent->isRed = false;
    g->isRed = true;
    if (n == n->parent->leftChild){
        rotate_right(g);
    }
    else{
        rotate_left(g);
    }
}

void RBTree:: rotate_left(RBTNode *node)
{
    RBTNode *tmpN = node->rightChild;
    node->rightChild = tmpN->leftChild;
    tmpN->parent = node->parent;
    tmpN->leftChild = node;
    node->parent = tmpN;
}

void RBTree:: rotate_right(RBTNode *node)
{
    RBTNode *tmpN = node->leftChild;
    tmpN->parent = node->parent;
    tmpN->rightChild = node;
    node->parent = tmpN;
    node->leftChild = tmpN->rightChild;
    if (tmpN->parent == NULL) {
        root = tmpN;
    }
}
//-------------------------------------------------end insertion--------------------------------------------------------------

void deleteNode(RBTNode* node)
{
    if (node) {
        RBTNode *left = node->leftChild;
        RBTNode *right = node->rightChild;
        delete node;
        if (left) {
            deleteNode(left);
        }
        if (right) {
            deleteNode(right);
        }
    }
}

void RBTree::removeAllNodes()
{
    deleteNode(root);
}

void printNode(RBTNode* node)
{
    if (node == NULL) {
        printf("it is an empty red-black-tree");
        return;
    }
    if (node->leftChild) {
        printNode(node->leftChild);
    }
    printf("%d--", node->data);
    if (node->rightChild) {
        printNode(node->rightChild);
    }
    printf("\n");
}

void RBTree::printTree()
{
    printNode(root);
    std::vector<RBTNode> arr;
    if (root) {
        arr.push_back(*root);
        int cur = 0;
        while (cur < arr.size()) {
            RBTNode node = arr[cur];
            printf("%d--", node.data);
            if (node.leftChild) {
                arr.push_back(*node.leftChild);
            }
            if (node.rightChild) {
                arr.push_back(*node.rightChild);
            }
            cur++;
        }
    }
    printf("\n");
}

