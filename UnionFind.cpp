#include "UnionFind.h"


template<class Elem>
ElementNode<Elem> *ElementNode<Elem>::findRoot() {
    if (!parent) {
        return this;
    }
    ElementNode* root = parent->findRoot();
    groupChanges += parent->groupChanges; //path compression optimization
    parent = root;
    return root;
}

template<class Group, class Elem>
UnionFind<Group, Elem>::UnionFind() = default;

template<class Group, class Elem>
UnionFind<Group, Elem>::~UnionFind() = default;

template<class Group, class Elem>
int UnionFind<Group, Elem>::find(int elementId) {
    //check if element is in the structure
    //auto elementPtr = elementsTable.hash(elementId);
    auto elementPtr = elementsTable[elementId];
    if (!elementPtr) {
        return -1;
    }
    //find the root of the group
    return elementPtr->findRoot()->groupId;
}

//creates an empty group
template<class Group, class Elem>
bool UnionFind<Group, Elem>::addGroup(int groupId, const Group &group) {
    if (groupsTable[groupId]) {
        return false;
    }
    std::shared_ptr<GroupNode<Group, Elem> > newGroup = std::make_shared<GroupNode<Group, Elem> >(group, groupId);
    groupsTable[groupId]=newGroup;
    return true;
}

template<class Group, class Elem>
bool UnionFind<Group, Elem>::addElement(int elementId, const Elem &element, int groupId) {
    if (elementsTable[elementId]) {
        return false;
    }
    auto groupPtr = groupsTable[groupId];
    if (!groupPtr) {
        return false;
    }
    std::shared_ptr<ElementNode<Elem> > newElement = std::make_shared<ElementNode<Elem> >(element, groupId);
    if (groupPtr->size == 0) {
        groupPtr->root = newElement.get();
    } else {
        newElement->parent = groupPtr->root;
    }
    groupPtr->size+=1;
    elementsTable[elementId]=newElement;
    return true;
}

template<class Group, class Elem>
bool UnionFind<Group, Elem>::unionGroups(int groupId1, int groupId2, int groupId3) {
    auto rootPtr1 = groupsTable[groupId1];
    auto rootPtr2 = groupsTable[groupId2];
    if (!rootPtr1|| !rootPtr2 || groupsTable[groupId3]) {
        return false;
    }
    if (rootPtr1->groupId == rootPtr2->groupId) {
        return false;
    }
    std::shared_ptr<GroupNode<Group, Elem> > mergedGroup = std::make_shared<GroupNode<Group, Elem> >(Group(), groupId3);
    mergedGroup->size = rootPtr1->size + rootPtr2->size;
    groupsTable[groupId3] = mergedGroup;
    if (rootPtr1->size >= rootPtr2->size) {
        mergedGroup->root = rootPtr1->root;
        mergedGroup->root->groupId = groupId3;
        rootPtr2->root->parent = mergedGroup->root;
        mergedGroup->root->groupChanges = 1;
    } else {
        mergedGroup->root = rootPtr2->root;
        mergedGroup->root->groupId = groupId3;
        rootPtr1->root->parent = mergedGroup->root;
        mergedGroup->root->groupChanges = 1;
    }
    //the groups are now empty
    rootPtr1->size=0;
    rootPtr2->size=0;
    return true;
}

template<class Group, class Elem>
int UnionFind<Group, Elem>::groupSize(int groupId) const {
    auto groupPtr = groupsTable[groupId];
    if (!groupPtr) {
        return -1;
    }
    return groupPtr->size;
}

template<class Group, class Elem>
int UnionFind<Group, Elem>::getDifferentGroupsNumber(int elementId) const {
    auto elementPtr = elementsTable[elementId];
    if (!elementPtr) {
        return -1;
    }
    ElementNode<Elem>* current=elementPtr.get();
    int sum=0;
    while(current->parent) {
        sum+=current->groupChanges;
        current=current->parent;
    }
    return sum;
}