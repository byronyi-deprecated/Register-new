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
    HashTable() : _size(0) {}

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
        for(unsigned int i = 0; i != 19; ++i)
        {
            list<T> temp = buckets[i].items();
            items.splice(items.end(), temp);
        }
        return items;
    }

private:
    HashVal hash(const T& item) const
    {
        return item.getKey() % 19;
    }
    DoublyLinkedList<T> buckets[19];
    unsigned int _size;
};

#endif // HASHTABLE_H
