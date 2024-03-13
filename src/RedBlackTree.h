//
// Created by portes on 12/03/2024.
//

#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#include <utility>

#include "Review.h"

enum Color { RED, BLACK };

struct Node
{
    Review data;
    long long filePos;
    Color color;
    Node *left, *right, *parent;

    Node(Review data, long long filePos, Color color = RED)
        : data(std::move(data)), filePos(filePos), color(color), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree
{
private:
    long long comparisons;
    Node *root{nullptr};

    void rotateLeft(Node *&node);
    void rotateRight(Node *&node);
    void fixViolation(Node *&node);
    void inorderTraversal(Node *node);

public:
    RedBlackTree() : root(nullptr), comparisons(0) {}

    long long getComparisons() const {
        return comparisons;
    }

    void resetComparisons() {
        comparisons = 0;
    }

    Review* searchInternal(Node* node, const std::string& id);

    Review* search(const std::string& id) {
        return searchInternal(root, id);
    }
    void insert(const Review &data, long long filePos);
    void inorder();
};



#endif //REDBLACKTREE_H
