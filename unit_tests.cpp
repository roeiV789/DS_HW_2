#include <iostream>
#include <assert.h>

#include "HashTable.h"
#include "UnionFind.h"

void unitTest1();

void unitTest2();

void unitTest3();

void unitTestHashTable1();

void unitTestHashTable2();
int main() {
    unitTest1();
    unitTest2();
    unitTest3();
    unitTestHashTable1();
    unitTestHashTable2();
    return 0;
}

//this test checks if the basic add,find,union work
void unitTest1() {
    UnionFind<int, int> uf;
    uf.addGroup(0, 0);
    uf.addGroup(1, 1);
    assert(uf.addElement(0,0,0));
    assert(uf.addElement(1,1,0));
    assert(uf.addElement(2,2,0));
    assert(uf.addElement(3,3,1));
    assert(uf.find(2)==0);
    assert(uf.find(3)==1);
    assert(uf.groupSize(0)==3);
    assert(uf.groupSize(1)==1);
    uf.unionGroups(0, 1, 2);
    assert(uf.groupSize(0)==0);
    assert(uf.groupSize(1)==0);
    assert(uf.groupSize(2)==4);
    assert(uf.find(2)==2);
    assert(uf.find(3)==2);
    std::cout << "test1 passed" << std::endl;
}

//this test checks if false is returned for bad inputs
void unitTest2() {
    UnionFind<int, int> uf;
    uf.addGroup(0, 0);
    uf.addGroup(1, 1);
    assert(uf.addElement(0,0,0));
    assert(uf.addElement(1,1,0));
    assert(uf.addElement(2,2,0));
    assert(uf.addElement(3,3,1));
    assert(uf.find(4)<0);
    assert(uf.find(0)>=0);
    assert(uf.addGroup(0,0)==false);
    assert(uf.addElement(2,2,0)==false);
    assert(uf.addElement(3,3,4)==false);
    assert(uf.unionGroups(3,0,5)==false);
    assert(uf.unionGroups(1,3,5)==false);
    assert(uf.unionGroups(0,0,4)==false);
    assert(uf.groupSize(4)==-1);
    std::cout << "test2 passed" << std::endl;
}

//this test checks if groupsChange function works
void unitTest3() {
    UnionFind<int, int> uf;
    uf.addGroup(0, 0);
    uf.addGroup(1, 1);
    assert(uf.addElement(0,0,0));
    assert(uf.addElement(1,1,0));
    assert(uf.addElement(2,2,0));
    assert(uf.addElement(3,3,1));
    assert(uf.addElement(4,4,1));
    //let's check if the starting value of each node is correct
    assert(uf.getDifferentGroupsNumber(0)==1);
    assert(uf.getDifferentGroupsNumber(1)==1);
    assert(uf.getDifferentGroupsNumber(2)==1);
    assert(uf.getDifferentGroupsNumber(3)==1);
    assert(uf.unionGroups(0,1,2)==true);
    assert(uf.getDifferentGroupsNumber(0)==2);
    assert(uf.getDifferentGroupsNumber(1)==2);
    assert(uf.getDifferentGroupsNumber(2)==2);
    assert(uf.getDifferentGroupsNumber(3)==2);
    assert(uf.getDifferentGroupsNumber(4)==2);
    uf.addGroup(3, 3);
    uf.addElement(5, 5, 3);
    uf.addElement(6, 6, 3);
    uf.unionGroups(3, 2, 4);
    assert(uf.getDifferentGroupsNumber(5)==2);
    assert(uf.getDifferentGroupsNumber(6)==2);
    //single element check
    uf.addElement(7, 7, 4);
    assert(uf.getDifferentGroupsNumber(7)==1);
    assert(uf.unionGroups(0,1,8)==true);
    assert(uf.groupSize(8)==0);
    uf.unionGroups(4, 8, 9);
    std::cout << "test3 passed" << std::endl;
}

void unitTestHashTable1() {
    HashTable<int> ht;
    ht.set(10, 1);
    ht.set(20, 2);
    ht.set(30, 3);
    assert(ht.get(1) == 10);
    assert(ht.get(2) == 20);
    assert(ht.get(3) == 30);
    assert(ht.getSize() == 3);
    assert(ht.getCapacity() == 8);
    ht.erase(2);
    try {
        ht.get(2); // Should throw an exception
        assert(false); // If we reach here, the test failed
    } catch (const std::out_of_range &) {
        // Expected exception
    }
    assert(ht.getSize() == 2);
    assert(ht.getCapacity() == 8);
    std::cout << "unitTestHashtable1 passed" << std::endl;
}

void unitTestHashTable2() {
    // write a test that checks if the rehashing works correctly
    HashTable<int> ht;
    for (int i = 0; i < 20; ++i) {
        ht.set(i, i + 1);
    }
    assert(ht.getSize() == 20);
    assert(ht.getCapacity() == 64);
    for (int i = 0; i < 20; ++i) {
        assert(ht.get(i + 1) == i);
    }
    ht.erase(20);
    ht.erase(19);
    ht.erase(18);
    ht.erase(17);
    ht.erase(16);
    ht.erase(15);

    for (int i = 0; i < 14; ++i) {
        assert(ht.get(i + 1) == i);
    }

    for (int i = 14; i < 20; ++i) {
        try {
            ht.get(i + 1); // Should throw an exception
            assert(false); // If we reach here, the test failed
        } catch (const std::out_of_range &) {
            // Expected exception
        }
    }
    assert(ht.getSize() == 14);
    assert(ht.getCapacity() == 32);

    std::cout << "unitTestHashtable2 passed" << std::endl;
}
