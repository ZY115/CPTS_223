#pragma once

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

template <typename K, typename V>
struct Node {
    K key;
    V value;
    Node* next;
};

template <typename K, typename V>
class LinkedList {
private:
    Node<K, V>* head;
    size_t size;

public:
    LinkedList() : head(nullptr), size(0) {
        std::srand(std::time(nullptr)); // initialize random seed
    }

    ~LinkedList() {
        clear();
    }

    void insert(K key, V value) {
        push_back(key, value);
    }

    void push_back(K key, V value) {
        Node<K, V>* newNode = new Node<K, V>{ key, value, nullptr };
        if (!head) {
            head = newNode;
        }
        else {
            Node<K, V>* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        size++;
    }

    bool removeByKey(K key) {
        if (!head) return false;
        if (head->key == key) {
            Node<K, V>* temp = head;
            head = head->next;
            delete temp;
            size--;
            return true;
        }

        Node<K, V>* prev = head;
        Node<K, V>* current = head->next;

        while (current) {
            if (current->key == key) {
                prev->next = current->next;
                delete current;
                size--;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }

    void display() const {
        Node<K, V>* temp = head;
        while (temp) {
            std::cout << temp->key << ": " << temp->value << std::endl;
            temp = temp->next;
        }
    }

    bool containsKey(K key) const {
        Node<K, V>* temp = head;
        while (temp) {
            if (temp->key == key) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    size_t getSize() const {
        return size;
    }

    void clear() {
        while (head) {
            Node<K, V>* temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }

    Node<K, V>* getRandomNode() {
        if (size == 0) {
            return nullptr;
        }
        int index = std::rand() % size;
        Node<K, V>* temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp;
    }

    std::vector<V> getTwoRandomValuesExcluding(V excludedValue) {
        std::vector<V> values;
        while (values.size() < 2) {
            V randomValue = getRandomNode()->value;
            if (randomValue != excludedValue && std::find(values.begin(), values.end(), randomValue) == values.end()) {
                values.push_back(randomValue);
            }
        }
        return values;
    }
};

#endif 
