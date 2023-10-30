#pragma once
#ifndef __CHAINING_HASH_H
#define __CHAINING_HASH_H

#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <stdexcept>
#include "Hash.h"

using std::vector;
using std::list;
using std::pair;

template<typename K, typename V>
class ChainingHash : public Hash<K, V> {
private:
    vector<list<pair<K, V>>> table;  // The hash table
    int count;                       // Number of elements

public:
    ChainingHash(int n = 11)
        : table(n), count(0) {}

    ~ChainingHash() {
        this->clear();
    }

    int size() const override {
        return count;
    }

    V& operator[](const K& key) override {
        int hashedKey = this->hash(key);
        for (auto& entry : table[hashedKey]) {
            if (entry.first == key) {
                return entry.second;
            }
        }
        throw std::runtime_error("Key not found");
    }

    bool insert(const std::pair<K, V>& pair) override {
        int hashedKey = this->hash(pair.first);
        for (auto& entry : table[hashedKey]) {
            if (entry.first == pair.first) {
                //std::cout << "Cha Insert failed for key: " << pair.first << ", hashed to: " << hashedKey << std::endl;
                return false;  // Key already exists
            }
        }
        table[hashedKey].push_back(pair);
        count++;

        if (load_factor() > 0.75) {
            rehash();
        }
        return true;
    }

    void erase(const K& key) override {
        int hashedKey = this->hash(key);
        for (auto it = table[hashedKey].begin(); it != table[hashedKey].end(); ++it) {
            if (it->first == key) {
                table[hashedKey].erase(it);
                count--;
                return;
            }
        }
    }

    void clear() override {
        for (auto& bucket : table) {
            bucket.clear();
        }
        count = 0;
    }

    int bucket_count() const override {
        return table.size();
    }

    float load_factor() const override {
        return static_cast<float>(count) / table.size();
    }

private:
    int hash(const K& key) const override {
        return std::hash<K>()(key) % table.size();
    }

    void rehash() {
        vector<list<pair<K, V>>> oldTable = table;
        table.resize(findNextPrime(2 * table.size()));

        for (auto& bucket : table) {
            bucket.clear();
        }
        count = 0;

        for (auto& oldBucket : oldTable) {
            for (auto& entry : oldBucket) {
                insert(entry);
            }
        }
    }

    int findNextPrime(int n) {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }

    bool isPrime(int n) const {
        if (n <= 1) {
            return false;
        }
        for (int i = 2; i <= static_cast<int>(std::sqrt(n)); i++) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }
};

#endif 
