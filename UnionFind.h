#pragma once
#include "HashTable.h"
#include <memory>
template<class Elem>

struct ElementNode {
    Elem element; //so this would be song
    ElementNode *parent;
    int groupId;
    int groupChanges;

    ElementNode(const Elem &element, int groupId) : element(element), parent(nullptr),
                                                    groupId(groupId), groupChanges(0) {
    }

    ElementNode *findRoot();
};

template<class Group, class Elem>
struct GroupNode {
    Group group; //so this would be song
    ElementNode<Elem> *root;
    int groupId;
    int size;

    GroupNode(const Group &group, int groupId) : group(group), root(nullptr),
                                                 groupId(groupId), size(0) {
    }
};


template<class Group, class Elem>
class UnionFind {
    HashTable<std::shared_ptr<ElementNode<Elem> > > elementsTable;
    HashTable<std::shared_ptr<GroupNode<Group, Elem> > > groupsTable;

public:
    UnionFind();

    ~UnionFind();

    int findElementGroup(int elementId);

    bool addElement(int elementId, const Elem &element, int groupId);

    bool addGroup(int groupId, const Group &group);

    bool uniteGroups(int groupId1, int groupId2, int groupId3);

    int groupSize(int groupId) const;

    int getNumberOfGroupChanges(int elementId) const;
};

template<class Elem>
ElementNode<Elem> *ElementNode<Elem>::findRoot() {
    if (!parent) {
        return this;
    }
    //path compression optimization
    ElementNode *root = parent->findRoot();
    if (parent != root) {
        groupChanges += parent->groupChanges;
    }
    parent = root;
    return root;
}

template<class Group, class Elem>
UnionFind<Group, Elem>::UnionFind() = default;

template<class Group, class Elem>
UnionFind<Group, Elem>::~UnionFind() = default;

template<class Group, class Elem>
int UnionFind<Group, Elem>::findElementGroup(int elementId) {
    //check if element is in the structure
    //auto elementPtr = elementsTable.hash(elementId);
    if (!elementsTable.isPresent(elementId)) {
        return -1;
    }
    auto elementPtr = elementsTable[elementId];
    //find the root of the group
    return elementPtr->findRoot()->groupId;
}

//creates an empty group
template<class Group, class Elem>
bool UnionFind<Group, Elem>::addGroup(int groupId, const Group &group) {
    if (groupsTable.isPresent(groupId)) {
        return false;
    }
    std::shared_ptr<GroupNode<Group, Elem> > newGroup = std::make_shared<GroupNode<Group, Elem> >(group, groupId);
    groupsTable.set(newGroup, groupId);
    return true;
}

template<class Group, class Elem>
bool UnionFind<Group, Elem>::addElement(int elementId, const Elem &element, int groupId) {
    if (elementsTable.isPresent(elementId) ||
        !groupsTable.isPresent(groupId)) {
        return false;
    }
    auto groupPtr = groupsTable[groupId];
    std::shared_ptr<ElementNode<Elem> > newElement = std::make_shared<ElementNode<Elem> >(element, groupId);
    if (groupPtr->size == 0) {
        groupPtr->root = newElement.get();
    } else {
        newElement->parent = groupPtr->root;
        newElement->groupChanges -= groupPtr->root->groupChanges;
    }
    groupPtr->size += 1;
    elementsTable.set(newElement, elementId);
    return true;
}

template<class Group, class Elem>
bool UnionFind<Group, Elem>::uniteGroups(int groupId1, int groupId2, int groupId3) {
    if (!groupsTable.isPresent(groupId1) ||
        !groupsTable.isPresent(groupId2) ||
        groupsTable.isPresent(groupId3)) {
        return false;
    }
    auto rootPtr1 = groupsTable[groupId1];
    auto rootPtr2 = groupsTable[groupId2];
    if (rootPtr1->groupId == rootPtr2->groupId) {
        return false;
    }
    std::shared_ptr<GroupNode<Group, Elem> > mergedGroup = std::make_shared<GroupNode<Group, Elem> >(Group(), groupId3);
    mergedGroup->size = rootPtr1->size + rootPtr2->size;
    groupsTable.set(mergedGroup, groupId3);
    if (rootPtr1->size >= rootPtr2->size) {
        //updating the pointers of the new group
        mergedGroup->root = rootPtr1->root;
        mergedGroup->root->groupId = groupId3;
        rootPtr2->root->parent = mergedGroup->root;
        //updating groupChanges field - big tree increases, small tree will hold the difference for sum up the tree
        mergedGroup->root->groupChanges += 1;
        rootPtr2->root->groupChanges += 1;
        rootPtr2->root->groupChanges -= mergedGroup->root->groupChanges;
    } else {
        //updating the pointers of the new group
        mergedGroup->root = rootPtr2->root;
        mergedGroup->root->groupId = groupId3;
        rootPtr1->root->parent = mergedGroup->root;
        //updating groupChanges field - big tree increases, small tree will hold the difference for sum up the tree
        mergedGroup->root->groupChanges += 1;
        rootPtr1->root->groupChanges += 1;
        rootPtr1->root->groupChanges -= mergedGroup->root->groupChanges;
    }

    //the groups are now empty
    rootPtr1->size = 0;
    rootPtr2->size = 0;
    return true;
}

template<class Group, class Elem>
int UnionFind<Group, Elem>::groupSize(int groupId) const {
    if (!groupsTable.isPresent(groupId)) {
        return -1;
    }
    auto groupPtr = groupsTable[groupId];
    return groupPtr->size;
}

// Returns -1 if the element does not exist
template<class Group, class Elem>
int UnionFind<Group, Elem>::getNumberOfGroupChanges(int elementId) const {
    if (!elementsTable.isPresent(elementId)) {
        return -1;
    }
    auto elementPtr = elementsTable[elementId];
    elementPtr->findRoot(); //path compression and groupChanges update
    int sum = 0;
    if (!elementPtr->parent) {
        sum = elementPtr->groupChanges;
    } else {
        sum = elementPtr->groupChanges + elementPtr->parent->groupChanges;
    }
    return sum + 1;
}
