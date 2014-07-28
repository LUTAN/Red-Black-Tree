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
    if ((n != NULL) && (n->parent != NULL)){
        return (n->parent)->parent;
    }
    else{
        return NULL;
    }
}

RBTNode *getUncle(const RBTNode *n)
{
    RBTNode *g = getGrandparent(n);
    if (g == NULL){
        return NULL; // No grandparent means no uncle
    }
    if (n->parent == g->leftChild){
        return g->rightChild;
    }
    else{
        return g->leftChild;
    }
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
        //left rotation
        RBTNode *p = n->parent;
        g->leftChild = n;
        p->parent = n;
        p->rightChild = n->leftChild;
        n->parent = g;
        if (n->leftChild) {
            n->leftChild->parent = p;
        }
        n->leftChild = p;
        
        n = n->leftChild;
        
    } else if ((n == n->parent->leftChild) && (n->parent == g->rightChild)) {
        // right rotation
        RBTNode *p = n->parent;
        g->rightChild = n;
        p->parent = n;
        p->leftChild = n->rightChild;
        if (n->rightChild) {
            n->rightChild->parent = p;
        }
        n->parent = g;
        n->rightChild = p;
        
        n = n->rightChild;
    }
    insertWithRightRotation(n);
}

void RBTree:: insertWithRightRotation(RBTNode *n)
{
    RBTNode *g = getGrandparent(n), *p = n->parent;
    p->isRed = false;
    g->isRed = true;
    
    if (n == n->parent->leftChild){
        p->parent = g->parent;
        if (g->parent) {
            if (g == g->parent->leftChild) {
                g->parent->leftChild = p;
            }
            else{
                g->parent->rightChild = p;
            }
        }
        else{
            root = p;
        }
        g->parent = p;
        g->leftChild = p->rightChild;
        if (p->rightChild) {
            p->rightChild->parent = g;
        }
        
        p->rightChild = g;
    }
    else{
        p->parent = g->parent;
        if (g->parent) {
            if (g == g->parent->leftChild) {
                g->parent->leftChild = p;
            }
            else{
                g->parent->rightChild = p;
            }
        }
        else{
            root = p;
        }
        g->parent = p;
        g->rightChild = p->leftChild;
        if (p->leftChild) {
            p->leftChild->parent = g;
        }
        
        p->leftChild = g;
    }
}
//-----------------------------------------------------------------end insertion-----------------------------------------------------------------

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
}

void RBTree::printTree()
{
    printNode(root);
    printf("\n");
}

