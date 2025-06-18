#include "UnionFind.h"


template<class Group, class Elem>
typename UnionFind<Group,Elem>::Node* findRoot(typename UnionFind<Group,Elem>::Node* current) {
    if(!current->parent) {
        return current;
    }
    current->parent = findRoot(current->parent);
    return current->parent; //path compression optimization
}
template<class Group, class Elem>
UnionFind<Group,Elem>::UnionFind() = default;

template<class Group, class Elem>
UnionFind<Group,Elem>::~UnionFind() = default;

template<class Group, class Elem>
Group* UnionFind<Group,Elem>::find(int elementId){
    auto nodePtr = elementsTable.hash(elementId);
    if(nodePtr) {
        return nullptr;
    }
    Node* rootPtr= findRoot(nodePtr.get());
    return elementsTable.hash(*rootPtr).get();
}
template<class Group, class Elem>
bool UnionFind<Group,Elem>::makeSet(int elementId, int groupId, const Elem& newElement) {
    auto groupPtr = groupsTable.hash(groupId);

    if(!groupsTable.hash(groupId)||elementsTable.hash(elementId)) {
        return false;
    }
    auto nodePtr = make_shared<Node>(newElement,groupId);

}
//groupId1 should house the bigger group
template<class Group, class Elem>
bool UnionFind<Group,Elem>::unionGroups(int groupId1, int groupId2, int groupId3) {
    if(groupId1==groupId2 || groupId2==groupId3 || groupId3==groupId1) {
        return false;
    }
    auto rootPtr1 = groupsTable.hash(groupId1);
    auto rootPtr2 = groupsTable.hash(groupId2);
    if(!groupsTable.hash(groupId1)||!groupsTable.hash(groupId2)||groupsTable.hash(groupId3)) {
        return false;
    }
    if(this->find(rootPtr1)==this->find(rootPtr2)) {
        return false;
    }
    groupsTable.insert(groupId3,rootPtr1);
    rootPtr2->parent = rootPtr1;
    groupsTable.hash(groupId1)=nullptr;
    groupsTable.hash(groupId2)=nullptr;
}
