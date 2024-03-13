//
// Created by portes on 12/03/2024.
//

#include "BTree.h"

void BTree::insertInternal(BTreeNode *node, const Review &key, long long filePos)
{
    if (node->isLeaf)
    {
        int i = node->keys.size() - 1;
        while (i >= 0 && key < node->keys[i])
        {
            node->keys[i + 1] = node->keys[i];
            node->filePositions[i + 1] = node->filePositions[i];
            i--;
        }
        node->keys.insert(node->keys.begin() + i + 1, key);
        node->filePositions.insert(node->filePositions.begin() + i + 1, filePos);
    }
    else
    {
        int i = node->keys.size() - 1;
        while (i >= 0 && key < node->keys[i])
            i--;
        i++;

        if (node->children[i]->keys.size() == 2 * order - 1)
        {
            splitChild(node, i, node->children[i]);
            if (key > node->keys[i])
                i++;
        }
        insertInternal(node->children[i], key, filePos);
    }
}

void BTree::splitChild(BTreeNode *parent, int childIndex, BTreeNode *child)
{
    BTreeNode *newNode = new BTreeNode(child->isLeaf);
    newNode->keys.resize(order - 1);
    newNode->filePositions.resize(order - 1);

    for (int i = 0; i < order - 1; i++)
    {
        newNode->keys[i] = child->keys[i + order];
        newNode->filePositions[i] = child->filePositions[i + order];
    }

    if (!child->isLeaf)
    {
        newNode->children.resize(order);
        for (int i = 0; i < order; i++)
            newNode->children[i] = child->children[i + order];
    }

    child->keys.resize(order - 1);
    child->filePositions.resize(order - 1);

    parent->children.insert(parent->children.begin() + childIndex + 1, newNode);
    parent->keys.insert(parent->keys.begin() + childIndex, child->keys[order - 1]);
    parent->filePositions.insert(parent->filePositions.begin() + childIndex, child->filePositions[order - 1]);

    child->keys.resize(order - 1);
    child->filePositions.resize(order - 1);
}

Review* BTree::searchInternal(BTreeNode* node, const std::string& id) {
    if (node == nullptr)
        return nullptr;

    int i = 0;
    while (i < node->keys.size() && id > node->keys[i].id) {
        comparisons++;
        i++;
    }

    comparisons++;
    if (i < node->keys.size() && id == node->keys[i].id)
        return &(node->keys[i]);

    if (node->isLeaf)
        return nullptr;

    return searchInternal(node->children[i], id);
}

void BTree::insert(const Review &key, long long filePos)
{
    if (root == nullptr)
    {
        root = new BTreeNode(true);
        root->keys.push_back(key);
        root->filePositions.push_back(filePos);
    }
    else
    {
        if (root->keys.size() == 2 * order - 1)
        {
            BTreeNode *newRoot = new BTreeNode(false);
            newRoot->children.push_back(root);
            splitChild(newRoot, 0, root);
            root = newRoot;
        }
        insertInternal(root, key, filePos);
    }
}

void BTree::inorderTraversal(BTreeNode *node)
{
    if (node != nullptr)
    {
        int i;
        for (i = 0; i < node->keys.size(); i++)
        {
            if (!node->isLeaf)
                inorderTraversal(node->children[i]);
            std::cout << "ID: " << node->keys[i].id << ", File Position: " << node->filePositions[i] << std::endl;
        }
        if (!node->isLeaf)
            inorderTraversal(node->children[i]);
    }
}

void BTree::inorder()
{
    inorderTraversal(root);
}