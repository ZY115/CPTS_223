#pragma once
#ifndef __BST_H
#define __BST_H

#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using namespace std;

template <typename T>
struct Node {
    T value;
    Node* left;
    Node* right;

    Node(T val) : value(val), left(nullptr), right(nullptr) {}
    ~Node() {
        value = 0;
        left = nullptr;
        right = nullptr;
    }
};

template <typename T>
class BST {
protected:
    Node<T>* _root;

    // Helper method to recursively insert a value into the BST
    void addHelper(Node<T>* root, T val) {
        if (root->value > val) {
            if (!root->left) {
                root->left = new Node<T>(val);
            }
            else {
                addHelper(root->left, val);
            }
        }
        else {
            if (!root->right) {
                root->right = new Node<T>(val);
            }
            else {
                addHelper(root->right, val);
            }
        }
    }

    // Helper method to print BST values in an in-order traversal
    void printInOrderHelper(Node<T>* root) {
        if (!root) return;
        printInOrderHelper(root->left);
        cout << root->value << ' ';
        printInOrderHelper(root->right);
    }

    // Helper method to count the number of nodes in the BST
    int nodesCountHelper(Node<T>* root) {
        if (!root) return 0;
        return 1 + nodesCountHelper(root->left) + nodesCountHelper(root->right);
    }

    // Helper method to compute the height of the BST
    int heightHelper(Node<T>* root) {
        if (!root) return -1;
        return 1 + max(heightHelper(root->left), heightHelper(root->right));
    }

    // Helper method to delete a value from the BST
    bool deleteValueHelper(Node<T>* parent, Node<T>* current, T value) {
        if (!current) return false;
        if (current->value == value) {
            if (current->left == nullptr || current->right == nullptr) {
                Node<T>* temp = current->left;
                if (current->right) temp = current->right;
                if (parent) {
                    if (parent->left == current) {
                        parent->left = temp;
                    }
                    else {
                        parent->right = temp;
                    }
                }
                else {
                    this->_root = temp;
                }
                delete current;
            }
            else {
                Node<T>* validSubs = current->right;
                while (validSubs->left) {
                    validSubs = validSubs->left;
                }
                T temp = current->value;
                current->value = validSubs->value;
                validSubs->value = temp;
                return deleteValueHelper(current, current->right, temp);
            }
            return true;
        }
        if (current->value > value) {
            return deleteValueHelper(current, current->left, value);
        }
        return deleteValueHelper(current, current->right, value);
    }

    // New helper functions
    void destroyTree(Node<T>* root) {
        if (!root) return;
        destroyTree(root->left);
        destroyTree(root->right);
        delete root;
    }

    //This function uses a queue to process nodes at the current level before moving on to the next level
    void printLevelOrderHelper(Node<T>* root) {
        if (!root) return;
        queue<Node<T>*> q;
        q.push(root);
        while (!q.empty()) {
            int n = q.size();
            for (int i = 0; i < n; i++) {
                Node<T>* curr = q.front();
                cout << curr->value << (i < n - 1 ? " " : "\n");
                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
                q.pop();
            }
        }
    }

    //Recursive helper function to check if the Binary Search Tree contains a particular value
    bool containsHelper(Node<T>* root, T value) {
        if (!root) return false;
        if (root->value == value) return true;
        if (root->value > value) return containsHelper(root->left, value);
        return containsHelper(root->right, value);
    }

    //This function uses backtracking to explore each possible path in the tree
    void printMaxPathHelper(Node<T>* root, vector<T>& path, vector<T>& maxPath) {
        if (!root) return;
        path.push_back(root->value);
        if (!root->left && !root->right) {
            if (path.size() > maxPath.size()) {
                maxPath = path;
            }
        }
        printMaxPathHelper(root->left, path, maxPath);
        printMaxPathHelper(root->right, path, maxPath);
        path.pop_back();
    }

public:
    BST() : _root(nullptr) {}

    ~BST() {
        destroyTree(_root);
    }

    void add(T val) {
        if (_root) {
            addHelper(_root, val);
        }
        else {
            _root = new Node<T>(val);
        }
    }

    void print() {
        printInOrderHelper(_root);
    }

    void printLevelOrder() {
        printLevelOrderHelper(_root);
    }

    int nodesCount() {
        return nodesCountHelper(_root);
    }
    
    int height() {
        return heightHelper(_root);
    }
    
    bool deleteValue(T value) {
        return deleteValueHelper(nullptr, _root, value);
    }
    
    bool contains(T value) {
        return containsHelper(_root, value);
    }
    
    void printMaxPath() {
        vector<T> path, maxPath;
        printMaxPathHelper(_root, path, maxPath);
        for (size_t i = 0; i < maxPath.size(); ++i) {
            cout << maxPath[i] << (i == maxPath.size() - 1 ? "\n" : " ");
        }
    }
};

#endif // __BST_H
