//
//  RedBlackTree.cpp
//  SkipList
//
//  Created by lutan on 14-7-27.
//  Copyright (c) 2014年 Lutan. All rights reserved.
//

#include "RedBlackTree.h"

void insertRoot(RBTNode *n);
void insertWithBlackParents(RBTNode *n);
void insert_case3(RBTNode *n);
void insert_case4(RBTNode *n);
void insert_case5(RBTNode *n);
void rotate_left(RBTNode *n);
void rotate_right(RBTNode *n);

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

void insertRoot(RBTNode *n)
{
    if (n->parent == NULL)
        n->isRed = false;
    else
        insertWithBlackParents(n);
}

void insertWithBlackParents(RBTNode *n)
{
    if (n->parent->isRed == false)
        return; /* Tree is still valid */
    else
        insert_case3(n);
}

void insert_case3(RBTNode *n)
{
    RBTNode *u = getUncle(n), *g;
    
    if ((u != NULL) && (u->isRed == true)) {
        n->parent->isRed = false;
        u->isRed = false;
        g = getGrandparent(n);
        g->isRed = true;
        insertRoot(g);
    } else {
        insert_case4(n);
    }
}

void insert_case4(RBTNode *n)
{
    RBTNode *g = getGrandparent(n);
    
    if ((n == n->parent->rightChild) && (n->parent == g->leftChild)) {
        rotate_left(n->parent);
        n = n->leftChild;
        
    } else if ((n == n->parent->leftChild) && (n->parent == g->rightChild)) {
        rotate_right(n->parent);
        n = n->rightChild;
    }
    insert_case5(n);
}

void insert_case5(RBTNode *n)
{
    RBTNode *g = getGrandparent(n);
    
    n->parent->isRed = false;
    g->isRed = true;
    if (n == n->parent->leftChild)
        rotate_right(g);
    else
        rotate_left(g);
}

void rotate_left(RBTNode *n)
{
    RBTNode *g = getGrandparent(n);
    RBTNode *saved_p = g->leftChild;
    RBTNode *saved_left_n = n->leftChild;
    
    //change position
    g->leftChild = n;
    n->leftChild = saved_p;
    saved_p->rightChild = saved_left_n;
    saved_p->parent = n;
    n->parent = g;
}

void rotate_right(RBTNode *n)
{
    RBTNode *g = getGrandparent(n);
    RBTNode *saved_p = g->rightChild;
    RBTNode *saved_right_n = n->rightChild;
    
     //change position
    g->rightChild = n;
    n->rightChild = saved_p;
    saved_p->leftChild = saved_right_n;
    saved_p->parent = n;
    n->parent = g;
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
}

void RBTree::printTree()
{
    printNode(root);
}

