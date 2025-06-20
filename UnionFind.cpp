#include "UnionFind.h"


template<class Group, class Elem>
typename UnionFind<Group,Elem>::Node* UnionFind<Group,Elem>::Node::findRoot(Node* current) {
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
int UnionFind<Group,Elem>::find(int elementId){
    auto nodePtr = elementsTable.hash(elementId);
    if(!nodePtr) {
        return -1;
    }
    auto rootPtr= std::make_shared<Node>(Node::findRoot(nodePtr.get()));
    return rootPtr->groupId;
}
template<class Group, class Elem>
bool UnionFind<Group,Elem>::makeSet(int elementId, int groupId, const Elem& newElement) {
    auto groupPtr = groupsTable.hash(groupId);
    if(!groupPtr||elementsTable.hash(elementId)) {
        return false;
    }
    auto nodePtr = make_shared<Node>(newElement,groupId);
    nodePtr->parent = groupPtr->srcPtr;
    elementsTable.insert(elementId, nodePtr);
    return true;

}
//groupId1 should house the bigger group
template<class Group, class Elem>
bool UnionFind<Group,Elem>::unionGroups(int groupId1, int groupId2, int groupId3) {
    auto rootPtr1 = groupsTable.hash(groupId1);
    auto rootPtr2 = groupsTable.hash(groupId2);
    if(!groupsTable.hash(groupId1)||!groupsTable.hash(groupId2)||groupsTable.hash(groupId3)) {
        return false;
    }
    if(rootPtr1==rootPtr2) {
        return false;
    }
    groupsTable.insert(groupId3,rootPtr1);
    rootPtr2->parent = rootPtr1;
    //should change this based on how hash table is implemented
    groupsTable.hash(groupId1)=nullptr;
    groupsTable.hash(groupId2)=nullptr;
    return true;
}
