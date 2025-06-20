#pragma once
#include "HashTab.h"
#include <memory>
    template<class Group, class Elem>
    class UnionFind {
        struct Node{
            Elem element; //so this would be song
            Node* parent;
            Node* srcPtr;
            int groupId;
            explicit Node(const Elem& element, int groupId) : element(element), parent(nullptr),
                          srcPtr(nullptr) ,groupId(groupId) {}
            Node* findRoot(Node* current);
        };
        HashTab<int, std::shared_ptr<Node>> elementsTable;
        HashTab<int, std::unique_ptr<Group>> groupsTable;

    public:
        UnionFind();
        ~UnionFind();
        int find(int elementId);
        bool makeSet(int elementId, int groupId, const Elem& newElement);
        bool unionGroups(int groupId1, int groupId2, int groupId3);
    };


