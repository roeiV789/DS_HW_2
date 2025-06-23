#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <functional>
#include <stdexcept>

template<typename T>
class HashTable {
private:
    struct Element {
        T value;
        int id;

        // !!!!!IMPORTANT!!!!!
        // Elements are compared ONLY by their id
        bool operator==(const Element &other) const {
            return id == other.id;
        }
    };

    const int FACTOR = 2;
    const int MIN_CAPACITY = 8;

    Element *array;
    bool *present;
    int size = 0;
    int capacity = MIN_CAPACITY;

    int hash(int id, int k, int n) const {
        return (id + k * auxiliaryHash(id, n)) % n;
    }

    int auxiliaryHash(int id, int n) const {
        return (id % (n - 3) | 1);
    }

    int find(int id) const {
        int step = 0;
        while (step++ < capacity) {
            int index = hash(id, step, capacity);
            if (!present[index]) {
                return -1;
            }
            if (present[index] && array[index].id == id) {
                return index;
            }
        }

        throw std::runtime_error("Probed all elements with no result!");
    }

    void insert(const Element &value) {
        int step = 0;
        while (step++ < capacity) {
            int index = hash(value.id, step, capacity);
            if (present[index] && array[index] == value) {
                return; // Element already exists, no need to insert
            }
            if (!present[index]) {
                array[index] = value;
                present[index] = true;
                return;
            }
        }
        throw std::runtime_error("Probed all elements with no result!");
    }

    void remove(int id) {
        int step = 0;
        while (step++ < capacity) {
            int index = hash(value.id, step, capacity);
            if (!present[index]) {
                return; // Element not found, nothing to remove
            }
            if (present[index] && array[index].id == id) {
                present[index] = false; // Mark as deleted
                return;
            }
        }
        throw std::runtime_error("Probed all elements with no result!");
    }

    void rehash(int newCapacity) {
        Element *oldArray = array;
        bool *oldPresent = present;
        int oldCapacity = capacity;

        array = new Element[newCapacity];
        present = new bool[newCapacity];
        for (int i = 0; i < newCapacity; i++)
            present[i] = false;

        int oldSize = size;
        size = 0;
        capacity = newCapacity;

        for (int i = 0; i < oldCapacity; i++) {
            if (oldPresent[i]) {
                insert(oldArray[i]);
                size++;
            }
        }
        delete[] oldArray;
        delete[] oldPresent;
        size = oldSize;
    }

public:
    HashTable() {
        array = new Element[capacity];
        present = new bool[capacity];
        for (int i = 0; i < capacity; i++) {
            present[i] = false;
        }
    }

    HashTable &operator=(const HashTable<T> &other) = delete;

    HashTable(const HashTable<T> &other) = delete;

    ~HashTable() {
        delete[] array;
        delete[] present;
        size = 0;
        capacity = 0;
    }

    void set(const T &value, int id) {
        int idx = find(id);
        if (idx != -1) {
            array[idx].value = value;
            return;
        }
        if (2 * (size + 1) >= capacity) {
            rehash(capacity * FACTOR);
        }
        Element elem{value, id};
        insert(elem);
        size++;
    }

    T &get(int id) {
        int idx = find(id);
        if (idx == -1) {
            throw std::out_of_range("Element not found");
        }
        return array[idx].value;
    }

    const T &get(int id) const {
        int idx = find(id);
        if (idx == -1) {
            throw std::out_of_range("Element not found");
        }
        return array[idx].value;
    }

    void erase(int id) {
        if (find(id) == -1) {
            return;
        }

        if (4 * size <= capacity && capacity > MIN_CAPACITY) {
            rehash(capacity / FACTOR);
        }
    }
};

#endif //HASHTABLE_H
