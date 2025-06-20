#pragma once
#include "HashTab.h"
#include <memory>
template<class Elem>

struct ElementNode{
    Elem& element; //so this would be song
    ElementNode* parent;
    int groupId;
    ElementNode(const Elem& element, int groupId) : element(element), parent(nullptr),
                  groupId(groupId) {}
    ElementNode* findRoot();
};
template<class Group, class Elem>
struct GroupNode{
    Group& group; //so this would be song
    ElementNode<Elem>* root;
    int groupId;
    int size;
    GroupNode(const Group& group, int groupId) : group(group), root(nullptr),
                  groupId(groupId), size(0) {}
};


template<class Group, class Elem>
class UnionFind {

    HashTab<int, std::shared_ptr<ElementNode<Elem>>> elementsTable;
    HashTab<int, std::unique_ptr<GroupNode<Group,Elem>>> groupsTable;

    public:
        UnionFind();
        ~UnionFind();
        int find(int elementId);
        bool addElement(int elementId, const Elem &element, int groupId);
        bool addGroup(int groupId, const Group &group);
        bool unionGroups(int groupId1, int groupId2, int groupId3);

};

