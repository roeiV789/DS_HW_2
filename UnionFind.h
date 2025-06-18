#pragma once
#include "HashTab.h"
#include <memory>
    template<class Group, class Elem>
    class UnionFind {
        struct Node{
            Elem element; //so this would be song
            Node* parent;
            int groupId;
            explicit Node(const Elem& element, int groupId) : element(element), parent(nullptr), groupId(groupId) {}
            Node* findRoot(Node* current);
        };
        HashTab<int, std::shared_ptr<Node>> elementsTable;
        HashTab<int, std::unique_ptr<Group>> groupsTable;

    public:
        UnionFind();
        ~UnionFind();
        Group* find(int elementId);
        bool makeSet(int elementId, int groupId, const Elem& newElement, const Elem& group);
        bool unionGroups(int groupId1, int groupId2, int groupId3);
    };


