//
// Created by portes on 12/03/2024.
//

#ifndef BTREE_H
#define BTREE_H
#include <vector>

#include "Review.h"


struct BTreeNode
{
    std::vector<Review> keys;
    std::vector<long long> filePositions;
    std::vector<BTreeNode*> children;
    bool isLeaf;

    BTreeNode(bool isLeaf)
        : isLeaf(isLeaf) {}
};

class BTree
{
private:
    long long comparisons;

    BTreeNode *root;
    int order;

    void insertInternal(BTreeNode *node, const Review &key, long long filePos);
    void splitChild(BTreeNode *parent, int childIndex, BTreeNode *child);
    void inorderTraversal(BTreeNode *node);

public:
    BTree(int order) : root(nullptr), order(order), comparisons(0) {}

    long long getComparisons() const {
        return comparisons;
    }

    void resetComparisons() {
        comparisons = 0;
    }

    Review* searchInternal(BTreeNode* node, const std::string& id);

    Review* search(const std::string& id) {
        return searchInternal(root, id);
    }

    void insert(const Review &key, long long filePos);
    void inorder();
};


#endif //BTREE_H
