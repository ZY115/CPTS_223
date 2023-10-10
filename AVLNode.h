#pragma once
#ifndef AVLNODE_H
#define AVLNODE_H
#include "AVLTree.h"
template <typename T>
class AVLNode {
public:
    T data;
    AVLNode<T>* left; 
    AVLNode<T>* right; 
    int height;

    // Constructor
    AVLNode(T value)
        : data(value), left(nullptr), right(nullptr), height(1) {}

    // Destructor
    ~AVLNode() {
        delete left;
        delete right;
    }
};

#endif
