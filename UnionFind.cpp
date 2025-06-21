#include "UnionFind.h"


template<class Elem>
ElementNode<Elem> *ElementNode<Elem>::findRoot() {
    if (!parent) {
        return this;
    }
    parent = parent->findRoot(); //path compression optimization
    return parent;
}

template<class Group, class Elem>
UnionFind<Group, Elem>::UnionFind() = default;

template<class Group, class Elem>
UnionFind<Group, Elem>::~UnionFind() = default;

template<class Group, class Elem>
int UnionFind<Group, Elem>::find(int elementId) {
    //check if element is in the structure
    auto elementPtr = elementsTable.hash(elementId);
    if (!elementPtr) {
        return -1;
    }
    //find the root of the group
    return elementPtr->findRoot()->groupId;
}

//creates an empty group
template<class Group, class Elem>
bool UnionFind<Group, Elem>::addGroup(int groupId, const Group &group) {
    if (groupsTable.hash(groupId)) {
        return false;
    }
    std::shared_ptr<GroupNode<Group, Elem> > newGroup = make_shared<GroupNode<Group, Elem> >(group, groupId);
    groupsTable.insert(groupId,newGroup);
    return true;
}

template<class Group, class Elem>
bool UnionFind<Group, Elem>::addElement(int elementId, const Elem &element, int groupId) {
    if (elementsTable.hash(elementId)) {
        return false;
    }
    auto groupPtr = groupsTable.hash(groupId);
    if (!groupPtr) {
        return false;
    }
    std::shared_ptr<ElementNode<Elem> > newElement = make_shared<ElementNode<Elem> >(element, groupId);
    if (groupPtr->size == 0) {
        groupPtr->root = newElement.get();
    } else {
        newElement->parent = groupPtr->root;
    }
    groupPtr->size++;
    elementsTable.insert(elementId,newElement);
    return true;
}

template<class Group, class Elem>
bool UnionFind<Group, Elem>::unionGroups(int groupId1, int groupId2, int groupId3) {
    auto rootPtr1 = groupsTable.hash(groupId1);
    auto rootPtr2 = groupsTable.hash(groupId2);
    if (!groupsTable.hash(groupId1) || !groupsTable.hash(groupId2) || groupsTable.hash(groupId3)) {
        return false;
    }
    if (rootPtr1->groupId == rootPtr2->groupId) {
        return false;
    }
    std::shared_ptr<GroupNode<Group, Elem> > mergedGroup = make_shared<GroupNode<Group, Elem> >(Group(), groupId3);
    mergedGroup->size = rootPtr1->size + rootPtr2->size;
    groupsTable.insert(groupId3, mergedGroup);
    if (rootPtr1->size >= rootPtr2->size) {
        mergedGroup->root = rootPtr1->root;
        mergedGroup->root->groupId = groupId3;
        rootPtr2->root->parent = mergedGroup->root;
    } else {
        mergedGroup->root = rootPtr2->root;
        mergedGroup->root->groupId = groupId3;
        rootPtr1->root->parent = mergedGroup->root;
    }
    //the groups are now empty
    rootPtr1->size=0;
    rootPtr2->size=0;
    //should change this based on how hash table is implemented
    groupsTable.hash(groupId1) = nullptr;
    groupsTable.hash(groupId2) = nullptr;
    return true;
}

template<class Group, class Elem>
int UnionFind<Group, Elem>::groupSize(int groupId) const {
    auto groupPtr = groupsTable.hash(groupId);
    if (!groupPtr) {
        return -1;
    }
    return groupPtr->size;
}
