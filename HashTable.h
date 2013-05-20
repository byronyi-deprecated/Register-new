#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "DoublyLinkedList.h"
#include <vector>
using namespace std;

typedef unsigned int HashVal;

template<class T>
class HashTable
{
public:
    HashTable(unsigned int num_bucket = 19) : _size(0), numBucket(num_bucket),
        buckets(vector<DoublyLinkedList<T> >(numBucket)) {}

    bool insert(const T& item)
    {
        HashVal val = hash(item);
        if(buckets[val].insert(item))
        {
            ++_size;
            return true;
        }
        else
            return false;
    }

    bool remove(const T& item)
    {
        HashVal val = hash(item);
        if(buckets[val].remove(item))
        {
            --_size;
            return true;
        }
        else
            return false;
    }

    T* search(const T& item) const
    {
        HashVal val = hash(item);
        return buckets[val].search(item);
    }

    unsigned int size() const {return _size;}

    list<T> items() const
    {
        list<T> items;
        for(unsigned int i = 0; i != numBucket; ++i)
        {
            list<T> temp = buckets[i].items();
            items.splice(items.end(), temp);
        }
        return items;
    }

private:
    HashVal hash(const T& item) const
    {
        return item.getKey() % numBucket;
    }
    unsigned int _size;
    unsigned int numBucket;
    vector<DoublyLinkedList<T> > buckets;
};

#endif // HASHTABLE_H
