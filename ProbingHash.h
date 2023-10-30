#pragma once
#ifndef __PROBING_HASH_H
#define __PROBING_HASH_H

#include <vector>
#include <cmath>
#include <stdexcept>
#include "Hash.h"

using std::vector;
using std::pair;

enum EntryState {
    EMPTY = 0,
    VALID = 1,
    DELETED = 2
};

template<typename K, typename V>
class ProbingHash : public Hash<K, V> {
private:
    vector<pair<K, V>> table;
    vector<EntryState> status;
    int count;

public:
    ProbingHash(int n = 11)
        : table(n), status(n, EMPTY), count(0) {}

    ~ProbingHash() {
        this->clear();
    }

    int size() const override {
        return count;
    }

    V& operator[](const K& key) override {
        int hashedKey = this->hash(key);
        int originalHash = hashedKey;
        do {
            if (status[hashedKey] == VALID && table[hashedKey].first == key) {
                return table[hashedKey].second;
            }
            hashedKey = (hashedKey + 1) % table.size();
        } while (hashedKey != originalHash);

        throw std::runtime_error("Key not found");
    }

    bool insert(const std::pair<K, V>& pair) override {
        if (load_factor() > 0.75) {
            rehash();
        }

        int hashedKey = this->hash(pair.first);
        int originalHash = hashedKey;
        int probeCount = 0; 

        do {
            if (status[hashedKey] == EMPTY || status[hashedKey] == DELETED) {
                table[hashedKey] = pair;
                status[hashedKey] = VALID;
                count++;
                //std::cout << "Probed " << probeCount << " times for key: " << pair.first << std::endl; 
                return true;
            }
            else if (table[hashedKey].first == pair.first) {
               // std::cout << "Pro Insert failed for key: " << pair.first << ", hashed to: " << hashedKey << std::endl;
                return false; // Key already exists
            }

            hashedKey = (hashedKey + 1) % table.size();

            probeCount++;  
            if (probeCount > table.size()) {  
                std::cout << "Warning: Excessive probing detected." << std::endl;
                break;  
            }
        } while (hashedKey != originalHash);

        return false;
    }


    void erase(const K& key) override {
        int hashedKey = this->hash(key);
        int originalHash = hashedKey;

        do {
            if (status[hashedKey] == VALID && table[hashedKey].first == key) {
                //std::cout << "Deleting key: " << key << ", hashed to: " << hashedKey << std::endl;
                status[hashedKey] = DELETED;
                count--;
                return;
            }
            hashedKey = (hashedKey + 1) % table.size();
        } while (hashedKey != originalHash);
        

    }

    void clear() override {
        for (int i = 0; i < table.size(); i++) {
            status[i] = EMPTY;
        }
        count = 0;
    }

    int bucket_count() const override {
        return table.size();
    }

    float load_factor() const override {
        //std::cout << "Load factor: " << static_cast<float>(count) / table.size() << std::endl;
        return static_cast<float>(count) / table.size();
        

    }

private:
    int hash(const K& key) const override {
        return std::hash<K>()(key) % table.size();
    }

    void rehash() {
        //std::cout << "Starting rehash..." << std::endl;
        vector<pair<K, V>> oldTable = table;
        vector<EntryState> oldStatus = status;

        int newSize = findNextPrime(2 * table.size());
        table.resize(newSize);
        status.resize(newSize, EMPTY);

        count = 0;

        for (size_t i = 0; i < oldTable.size(); ++i) {
            if (oldStatus[i] == VALID) {
                int oldPosition = i;
                int newPosition = this->hash(oldTable[i].first) % table.size(); 
                //std::cout << "Moving key: " << oldTable[i].first << " from position " << oldPosition << " to position " << newPosition << std::endl;
                insert(oldTable[i]);
            }
        }

        //std::cout << "Rehash completed." << std::endl;
        //std::cout << "New table size: " << table.size() << std::endl;
    }

    int findNextPrime(int n) {
        //n = n * 3;
        while (!isPrime(n)) {
            n++;
        }
        //std::cout << "New prime found: " <<  n << std::endl;
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
