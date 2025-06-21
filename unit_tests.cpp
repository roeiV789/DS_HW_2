#include <iostream>
#include <assert.h>
#include "UnionFind.h"
#include "UnionFind.cpp"
void unit_test1();
void unit_test2();
void unit_test3();
int main() {
    unit_test1();
    std::cout << "test1 passed"<< std::endl;
    unit_test2();
    std::cout << "test2 passed"<< std::endl;
    unit_test3();
    std::cout << "test3 passed"<< std::endl;
    return 0;
}
//this test checks if the basic add,find,union work
void unit_test1() {
    UnionFind<int,int> uf;
    uf.addGroup(0,0);
    uf.addGroup(1,1);
    assert(uf.addElement(0,0,0));
    assert(uf.addElement(1,1,0));
    assert(uf.addElement(2,2,0));
    assert(uf.addElement(3,3,1));
    assert(uf.find(2)==0);
    assert(uf.find(3)==1);
    assert(uf.groupSize(0)==3);
    assert(uf.groupSize(1)==1);
    uf.unionGroups(0,1,2);
    assert(uf.groupSize(0)==0);
    assert(uf.groupSize(1)==0);
    assert(uf.groupSize(2)==4);
    assert(uf.find(2)==2);
    assert(uf.find(3)==2);
}
//this test checks if false is returned for bad inputs
void unit_test2() {
    UnionFind<int,int> uf;
    uf.addGroup(0,0);
    uf.addGroup(1,1);
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
}

//this test checks if groupsChange function works
void unit_test3() {
    UnionFind<int,int> uf;
    uf.addGroup(0,0);
    uf.addGroup(1,1);
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
    uf.addGroup(3,3);
    uf.addElement(5,5,3);
    uf.addElement(6,6,3);
    uf.unionGroups(3,2,4);
    assert(uf.getDifferentGroupsNumber(5)==2);
    assert(uf.getDifferentGroupsNumber(6)==2);
    //single element check
    uf.addElement(7,7,4);
    assert(uf.getDifferentGroupsNumber(7)==1);
    assert(uf.unionGroups(0,1,8)==true);
    assert(uf.groupSize(8)==0);
    uf.unionGroups(4,8,9);

}