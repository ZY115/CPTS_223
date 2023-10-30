#pragma once
/*
 *  Yet another Hash table interface
 *
 *  Contributors:
 *      Aaron S. Crandall <acrandal@wsu.edu> - 2019
 *      Sean Kallaher <seanp@kallaher.org> - 2019
 *
 */

#ifndef __Hash_H
#define __Hash_H

#include <math.h>

 // Hash class interface notes
 // ******************PUBLIC OPERATIONS*********************
 // int size( )                              --> Quantity of (non-deleted) elements in hash
 // V& operator[]( const K& k )              --> Returns the value with key k
 // bool insert( const pair<K, V>& pair )    --> Adds pair to hash, true if successful
 // void erase( const K& k )                 --> Removes all any (if any) entries with key k
 // void clear( )                            --> Empties the hash
 // int bucket_count()                       --> Returns the number of buckets allocated (size of the hash vector)
 // float load_factor( )                     --> Returns the load factor of the hash

 // void ~Hash( )       --> Destructor
 // Hash( )             --> Basic constructor

template <typename K, typename V>
class Hash
{
public:
    virtual ~Hash() = 0;

    virtual int size() const = 0;

    virtual V& operator[](const K& key) = 0;

    virtual bool insert(const std::pair<K, V>& pair) = 0;

    virtual void erase(const K& key) = 0;

    virtual void clear() = 0;

    virtual int bucket_count() const = 0;

    virtual float load_factor() const = 0;

protected:
    virtual int hash(const K& key) const = 0;
};

template <typename K, typename V>
Hash<K, V>::~Hash() {}

#endif
