//
//  RedBlackTree.cpp
//  DataStructure
//
//  Created by lutan on 14-7-27.
//  Copyright (c) 2014年 Lutan. All rights reserved.
//

#include "RedBlackTree.h"
#include <vector>

bool checkSubTree(RBTNode *node);

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

void RBTree:: copySubtree(RBTNode* des, RBTNode* source)
{
    if (source == NULL) {
        des = NULL;
        return;
    }
    RBTNode *left = NULL, *right = NULL;
    des->data = source->data;
    des->isRed = source->isRed;
    if (source->leftChild) {
        left = new RBTNode;
        copySubtree(left, source->leftChild);
    }
    if (source->rightChild) {
        right = new RBTNode;
        copySubtree(right, source->rightChild);
    }
    des->leftChild = left;
    des->rightChild = right;
    if (left) {
        left->parent = des;
    }
    if (right) {
        right->parent = des;
    }
}

//-------------------------------------------------------- constructor and destructor--------------------------------------------------------
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
    RBTNode* node = rbTree.root;
    root = NULL;
    if (node) {
        root = new RBTNode;
        root->parent = NULL;
        copySubtree(root, node);
    }
}

RBTree::~RBTree()
{
    removeAllNodes();
}
//----------------------------------------------------end constructor and destructor--------------------------------------------------------

void RBTree::operator=(const RBTree &tree)
{
    removeAllNodes();
    RBTNode* node = tree.root;
    if (node) {
        root = new RBTNode;
        root->parent = NULL;
        copySubtree(root, node);
    }
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


//----------------------------------------------------remove nodes-----------------------------------------------------------------------------
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
        if (nodeToRemove->leftChild != NULL && nodeToRemove->rightChild != NULL) {
            if (nodeToRemove->rightChild) {
                RBTNode *originalNode = nodeToRemove;
                nodeToRemove = nodeToRemove->rightChild;
                while (nodeToRemove->leftChild) {
                    nodeToRemove = nodeToRemove->leftChild;
                }
                originalNode->data = nodeToRemove->data;
                delete_one_child(nodeToRemove);
            }
            else{
                RBTNode *originalNode = nodeToRemove;
                nodeToRemove = nodeToRemove->leftChild;
                while (nodeToRemove->rightChild) {
                    nodeToRemove = nodeToRemove->rightChild;
                }
                originalNode->data = nodeToRemove->data;
                delete_one_child(nodeToRemove);
            }
        }
        else{
            delete_one_child(nodeToRemove);
        }
    }
    else{
        printf("no such node\n");
    }
}

void RBTree:: delete_one_child(RBTNode *n)
{
    if (n->rightChild != NULL && n->leftChild != NULL) {
        printf("error:with two non leaf childrens-------------------------------\n");
    }
    if (n == root) {
        delete root;
        root = NULL;
        return;
    }
    RBTNode *child = n->leftChild == NULL? n->rightChild : n->leftChild;
    if(child){
        child->parent = n->parent;
        if (n->parent) {
            if (n == n->parent->leftChild) {
                n->parent->leftChild = child;
            }
            else{
                n->parent->rightChild = child;
            }
        }
        
        if (n->isRed == false) {
            if (child->isRed == true){
                child->isRed = false;
            }
            else{
                delete_case1(child);
            }
        }
    }
    else{
        if (!n->isRed) {
            delete_case1(n);
        }
        if (n == n->parent->leftChild) {
            n->parent->leftChild = NULL;
        }
        else{
            n->parent->rightChild = NULL;
        }
    }
    delete n;
}

void RBTree:: delete_case1(RBTNode *n)
{
    if (n->parent != NULL)
        delete_case2(n);
}

void RBTree:: delete_case2(RBTNode *n)
{
    RBTNode *s = sibling(n);
    
    if (s->isRed == true) {
        n->parent->isRed = true;
        s->isRed = false;
        if (n == n->parent->leftChild){
            leftRotation(n->parent);
        }
        else{
            rightRotation(n->parent);
        }
    }
    delete_case3(n);
}

void RBTree:: delete_case3(RBTNode *n)
{
    RBTNode *s = sibling(n);
    bool left = true;
    if (s->leftChild) {
        left = !s->leftChild->isRed;
    }
    bool right = true;
    if (s->rightChild) {
        right = !s->rightChild->isRed;
    }
    if ((n->parent->isRed == false) &&
        (s->isRed == false) &&
        left &&
        right) {
        s->isRed = true;
        delete_case1(n->parent);
    } else
        delete_case4(n);
}

void RBTree:: delete_case4(RBTNode *n)
{
    RBTNode *s = sibling(n);
    
    bool left = true;
    if (s->leftChild) {
        left = !s->leftChild->isRed;
    }
    bool right = true;
    if (s->rightChild) {
        right = !s->rightChild->isRed;
    }
    
    if ((n->parent->isRed == true) &&
        (s->isRed == false) &&
        left &&
        right) {
        s->isRed = true;
        n->parent->isRed = false;
    } else
        delete_case5(n);
}

void RBTree:: delete_case5(RBTNode *n)
{
    RBTNode *s = sibling(n);
    
    bool left = true;
    if (s->leftChild) {
        left = !s->leftChild->isRed;
    }
    bool right = true;
    if (s->rightChild) {
        right = !s->rightChild->isRed;
    }
    
    if  (s->isRed == false) {
        if ((n == n->parent->leftChild) &&
            right &&
            !left) { /* this last test is trivial too due to cases 2-4. */
            s->isRed = true;
            s->leftChild->isRed = false;
            rightRotation(s);
        } else if ((n == n->parent->rightChild) &&
                   left &&
                   !right) {/* this last test is trivial too due to cases 2-4. */
            s->isRed = true;
            s->rightChild->isRed = false;
            leftRotation(s);
        }
    }
    delete_case6(n);
}

void RBTree:: delete_case6(RBTNode *n)
{
    RBTNode *s = sibling(n);
    
    s->isRed = n->parent->isRed;
    n->parent->isRed = false;
    
    if (n == n->parent->leftChild) {
        s->rightChild->isRed = false;
        leftRotation(n->parent);
    } else {
        s->leftChild->isRed = false;
        rightRotation(n->parent);
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
//------------------------------------------------------------end  delete a node----------------------------------------------------------------


//------------------------------------------------------------find a node----------------------------------------------------------------------
RBTNode* RBTree:: findNode(int a)
{
    if (root) {
        RBTNode *tmpNode = root;
        while (tmpNode->data != a) {
            if (tmpNode->data > a) {
                if (tmpNode->leftChild) {
                    tmpNode = tmpNode->leftChild;
                }
                else{
                    return NULL;
                }
            }
            else{
                if (tmpNode->rightChild) {
                    tmpNode = tmpNode->rightChild;
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
//-----------------------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------chekc the validation of tree------------------------------------------------------------
bool RBTree:: checkRBTree()
{
    if (root){
        if (root->isRed) {
            return false;
        }
    }
    return checkSubTree(root);
}

bool checkBlackLength(RBTNode *node, int* a)
{
    if (node == NULL) {
        *a = 1;
        return true;
    }
    int b = node->isRed? 0 : 1;
    int leftLen, rightLen;
    bool equal = checkBlackLength(node->leftChild, &leftLen);
    if (!equal) {
        return false;
    }
    equal = checkBlackLength(node->rightChild, &rightLen);
    if (!equal) {
        return false;
    }
    
    if (leftLen == rightLen) {
        *a = rightLen + b;
        return true;
    }
    else{
        return false;
    }
}

bool checkSubTree(RBTNode *node)
{
    if (node == NULL) {
        return true;
    }
    if (node->isRed) {
        if (node->leftChild) {
            if (node->leftChild->isRed) {
                return false;
            }
        }
        if (node->rightChild) {
            if (node->rightChild->isRed) {
                return false;
            }
        }
    }
    int a;
    bool ok = checkBlackLength(node, &a);
    return ok;
}
//---------------------------------------------------end chekc the validation of tree------------------------------------------------------------


//---------------------------------------------------print all nodes of tree------------------------------------------------------------
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

