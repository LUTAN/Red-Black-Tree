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
        leftRotation(n->parent);
        n = n->leftChild;
        
    } else if ((n == n->parent->leftChild) && (n->parent == g->rightChild)) {
        // right rotation
        rightRotation(n->parent);
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
        rightRotation(g);
    }
    else{
        leftRotation(g);
    }
}
//-----------------------------------------------------------------end insertion-----------------------------------------------------------------

//----------------------------------------------------------------rotation of node------------------------------------------------------------
void RBTree:: rightRotation(RBTNode *node)
{
    RBTNode *n= node->leftChild;
    RBTNode *p = node->parent;
    n->parent = p;
    if (p) {
        if (node == p->leftChild) {
            p->leftChild = n;
        }
        else{
            p->rightChild = n;
        }
    }
    else{
        root = n;
    }
    
    node->parent = n;
    node->leftChild = n->rightChild;
    if (n->rightChild) {
        n->rightChild->parent = node;
    }
    n->rightChild = node;
}

void RBTree:: leftRotation(RBTNode *node)
{
    RBTNode *n= node->rightChild;
    RBTNode *p = node->parent;
    n->parent = p;
    if (p) {
        if (node == p->leftChild) {
            p->leftChild = n;
        }
        else{
            p->rightChild = n;
        }
    }
    else{
        root = n;
    }
    
    node->parent = n;
    node->rightChild = n->leftChild;
    if (n->leftChild) {
        n->leftChild->parent = node;
    }
    n->leftChild= node;
}
//----------------------------------------------------end rotation-----------------------------------------------------------------------------

RBTNode *sibling(RBTNode* n)
{
    if (n->parent == NULL) {
        return NULL;
    }
    if (n == n->parent->leftChild){
        return n->parent->rightChild;
    }
    else{
        return n->parent->leftChild;
    }
}

void RBTree:: removeNode(int a)
{
    RBTNode *nodeToRemove = findNode(a);
    if (nodeToRemove) {
        if (nodeToRemove->leftChild == NULL && nodeToRemove->rightChild == NULL) {
            if (nodeToRemove->isRed) {
                if (nodeToRemove == nodeToRemove->parent->leftChild) {
                    nodeToRemove->parent->leftChild = NULL;
                }
                else{
                    nodeToRemove->parent->rightChild = NULL;
                }
                delete nodeToRemove;
            }
            else{
                //the node to remove is not red node
                
            }
        }
        else if (nodeToRemove->isRed){
            if (nodeToRemove->leftChild) {
                
            }
            else{
                
            }
        }
        else{
            if (nodeToRemove->leftChild) {
                
            }
            else{
                
            }
        }
    }
    else{
        printf("no such node\n");
    }
}

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
    root = NULL;
}

//------------------------------------------------------------find a node----------------------------------------------------------------------
RBTNode* RBTree:: findNode(int a)
{
    if (root) {
        RBTNode *tmpNode = root;
        while (tmpNode->data != a) {
            if (tmpNode->data > a) {
                if (tmpNode->rightChild) {
                    tmpNode = tmpNode->rightChild;
                }
                else{
                    return NULL;
                }
            }
            else{
                if (tmpNode->leftChild) {
                    tmpNode = tmpNode->leftChild;
                }
                else{
                    return NULL;
                }
            }
        }
        
        return tmpNode;
    }
    else{
        printf("it is an empty red-black-tree");
        return NULL;
    }
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

