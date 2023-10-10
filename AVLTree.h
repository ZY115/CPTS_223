#pragma once
#ifndef AVLTREE_H
#define AVLTREE_H
#include "AVLNode.h"

template <typename T>
class AVLTree {
private:
    AVLNode<T>* root;

    int height(AVLNode<T>* node)const;
    int balanceFactor(AVLNode<T>* node) const;
    AVLNode<T>* rotateLeft(AVLNode<T>* a);
    AVLNode<T>* rotateRight(AVLNode<T>* a);
    AVLNode<T>* insert(AVLNode<T>* node, T value);
    bool contains(AVLNode<T>* node, T value) const;
    bool validate(AVLNode<T>* node) const;
    AVLNode<T>* minValueNode(AVLNode<T>* node);
    AVLNode<T>* remove(AVLNode<T>* root, T value);


public:
    AVLTree() : root(nullptr) {}
    ~AVLTree();

    int height() {
        return height(root);
    }

    void insert(T value) {
        root = insert(root, value);
    }

    bool contains(T value) const {
        return contains(root, value);
    }

    bool validate() const {
        return validate(root);
    }

    void remove(T value) {
        root = remove(root, value);
    }

};

// Function Definitions:

template <typename T>
int AVLTree<T>::height(AVLNode<T>* node)const {
    return node ? node->height : 0;
}

template <typename T>
int AVLTree<T>::balanceFactor(AVLNode<T>* node) const{
    return node ? height(node->left) - height(node->right) : 0;
}

template <typename T>
AVLNode<T>* AVLTree<T>::rotateLeft(AVLNode<T>* a) {
    AVLNode<T>* b = a->right;
    a->right = b->left;
    b->left = a;

    // Update heights
    a->height = 1 + std::max(height(a->left), height(a->right));
    b->height = 1 + std::max(height(b->left), height(b->right));

    return b;
}

template <typename T>
AVLNode<T>* AVLTree<T>::rotateRight(AVLNode<T>* b) {
    AVLNode<T>* a = b->left;
    b->left = a->right;
    a->right = b;

    // Update heights
    b->height = 1 + std::max(height(b->left), height(b->right));
    a->height = 1 + std::max(height(a->left), height(a->right));

    return a;
}

template <typename T>
AVLNode<T>* AVLTree<T>::insert(AVLNode<T>* node, T value) {
    // Standard BST insertion
    if (!node) return new AVLNode<T>(value);

    if (value < node->data) {
        node->left = insert(node->left, value);
    }
    else if (value > node->data) {
        node->right = insert(node->right, value);
    }
    else {
        return node;  // Duplicates not allowed
    }

    // Update height
    node->height = 1 + std::max(height(node->left), height(node->right));

    // Get balance factor to check if it's unbalanced
    int balance = balanceFactor(node);

    // Rotations
    if (balance > 1 && value < node->left->data) {
        return rotateRight(node);
    }
    if (balance < -1 && value > node->right->data) {
        return rotateLeft(node);
    }
    if (balance > 1 && value > node->left->data) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && value < node->right->data) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

template <typename T>
bool AVLTree<T>::contains(AVLNode<T>* node, T value) const {
    if (!node) return false;
    if (value == node->data) return true;
    if (value < node->data) return contains(node->left, value);
    return contains(node->right, value);
}

template <typename T>
bool AVLTree<T>::validate(AVLNode<T>* node) const {
    if (!node) return true;

    int balance = balanceFactor(node);
    if (balance < -1 || balance > 1) return false;

    return validate(node->left) && validate(node->right);
}

template <typename T>
AVLTree<T>::~AVLTree() {
    while (root) {
        remove(root->data);
    }
}

template <typename T>
AVLNode<T>* AVLTree<T>::minValueNode(AVLNode<T>* node) {
    AVLNode<T>* current = node;

    // Traverse all the way left to the leftmost leaf node
    while (current->left != nullptr) {
        current = current->left;
    }

    return current;
}

template <typename T>
AVLNode<T>* AVLTree<T>::remove(AVLNode<T>* node, T value) {
    if (!node) return node;

    if (value < node->data) {
        node->left = remove(node->left, value);
    }
    else if (value > node->data) {
        node->right = remove(node->right, value);
    }
    else {
        if (!node->left || !node->right) {
            AVLNode<T>* temp = node->left ? node->left : node->right;

            if (!temp) {  // No child
                temp = node;
                node = nullptr;
            }
            else {      // One child
                *node = *temp;
            }
            delete temp;
        }
        else {
            AVLNode<T>* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }
    }

    // If the tree had only one node, return
    if (!node) return node;

    // Update height
    node->height = 1 + std::max(height(node->left), height(node->right));

    // Check balance factor
    int balance = balanceFactor(node);

    // Perform rotations if needed (similar to insert)
    if (balance > 1 && balanceFactor(node->left) >= 0) {
        return rotateRight(node);
    }
    if (balance > 1 && balanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && balanceFactor(node->right) <= 0) {
        return rotateLeft(node);
    }
    if (balance < -1 && balanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}


#endif 
