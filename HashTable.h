#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdexcept>

template<typename T>
class HashTable {
private:
    struct Element {
        T value;
        int id;

        bool operator==(const Element &other) const;
    };

    const int FACTOR = 2;
    const int MIN_CAPACITY = 8;

    Element *array;
    bool *present;
    int size = 0;
    int capacity = MIN_CAPACITY;

    int hash(int id, int k, int n) const;

    int auxiliaryHash(int id, int n) const;

    int find(int id) const;

    void insert(const Element &value);

    void remove(int id);

    void rehash(int newCapacity);

public:
    HashTable();

    HashTable(const HashTable<T> &other) = delete;

    HashTable &operator=(const HashTable<T> &other) = delete;

    ~HashTable();

    void set(const T &value, int id);

    T &get(int id);

    const T &get(int id) const;

    T &operator[](int index);

    const T &operator[](int index) const;

    bool isPresent(int id) const;

    void erase(int id);

    int getSize() const;

    int getCapacity() const;
};

// ==== Implementation ====

template<typename T>
bool HashTable<T>::Element::operator==(const Element &other) const {
    return id == other.id;
}

template<typename T>
int HashTable<T>::hash(int id, int k, int n) const {
    return (id + k * auxiliaryHash(id, n)) % n;
}

template<typename T>
int HashTable<T>::auxiliaryHash(int id, int n) const {
    return (id % (n - 3) | 1);
}

template<typename T>
int HashTable<T>::find(int id) const {
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

template<typename T>
void HashTable<T>::insert(const Element &value) {
    int step = 0;
    while (step++ < capacity) {
        int index = hash(value.id, step, capacity);
        if (present[index] && array[index] == value) {
            return;
        }
        if (!present[index]) {
            array[index] = value;
            present[index] = true;
            return;
        }
    }
    throw std::runtime_error("Probed all elements with no result!");
}

template<typename T>
void HashTable<T>::remove(int id) {
    int step = 0;
    while (step++ < capacity) {
        int index = hash(id, step, capacity);
        if (!present[index]) {
            return;
        }
        if (present[index] && array[index].id == id) {
            present[index] = false;
            return;
        }
    }
    throw std::runtime_error("Probed all elements with no result!");
}

template<typename T>
void HashTable<T>::rehash(int newCapacity) {
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

template<typename T>
HashTable<T>::HashTable() {
    array = new Element[capacity];
    present = new bool[capacity];
    for (int i = 0; i < capacity; i++) {
        present[i] = false;
    }
}

template<typename T>
HashTable<T>::~HashTable() {
    delete[] array;
    delete[] present;
    size = 0;
    capacity = 0;
}

template<typename T>
void HashTable<T>::set(const T &value, int id) {
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

template<typename T>
T &HashTable<T>::get(int id) {
    int idx = find(id);
    if (idx == -1) {
        throw std::out_of_range("Element not found");
    }
    return array[idx].value;
}

template<typename T>
const T &HashTable<T>::get(int id) const {
    int idx = find(id);
    if (idx == -1) {
        throw std::out_of_range("Element not found");
    }
    return array[idx].value;
}

template<typename T>
void HashTable<T>::erase(int id) {
    if (find(id) == -1) {
        return;
    }
    if (4 * size <= capacity && capacity > MIN_CAPACITY) {
        rehash(capacity / FACTOR);
    }
    remove(id);
    size--;
}

template<typename T>
int HashTable<T>::getSize() const {
    return size;
}

template<typename T>
int HashTable<T>::getCapacity() const {
    return capacity;
}

template<typename T>
T &HashTable<T>::operator[](int index) { return get(index); }

template<typename T>
const T &HashTable<T>::operator[](int index) const { return get(index); }

template<typename T>
bool HashTable<T>::isPresent(int id) const {
    return find(id) != -1;
}
#endif // HASHTABLE_H
