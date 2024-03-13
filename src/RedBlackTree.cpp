//
// Created by portes on 12/03/2024.
//

#include "RedBlackTree.h"

#include <iostream>


void RedBlackTree::rotateLeft(Node*&node) {
    Node* rightChild = node->right;
    node->right = rightChild->left;

    if (node->right != nullptr)
        node->right->parent = node;

    rightChild->parent = node->parent;

    if (node->parent == nullptr)
        root = rightChild;
    else if (node == node->parent->left)
        node->parent->left = rightChild;
    else
        node->parent->right = rightChild;

    rightChild->left = node;
    node->parent = rightChild;
}

void RedBlackTree::rotateRight(Node*&node) {
    Node* leftChild = node->left;
    node->left = leftChild->right;

    if (node->left != nullptr)
        node->left->parent = node;

    leftChild->parent = node->parent;

    if (node->parent == nullptr)
        root = leftChild;
    else if (node == node->parent->left)
        node->parent->left = leftChild;
    else
        node->parent->right = leftChild;

    leftChild->right = node;
    node->parent = leftChild;
}

void RedBlackTree::fixViolation(Node*&node) {
    Node* parentNode = nullptr;
    Node* grandParentNode = nullptr;

    while ((node != root) && (node->color != BLACK) && (node->parent->color == RED)) {
        parentNode = node->parent;
        grandParentNode = node->parent->parent;

        if (parentNode == grandParentNode->left) {
            Node* uncleNode = grandParentNode->right;

            if (uncleNode != nullptr && uncleNode->color == RED) {
                grandParentNode->color = RED;
                parentNode->color = BLACK;
                uncleNode->color = BLACK;
                node = grandParentNode;
            }
            else {
                if (node == parentNode->right) {
                    rotateLeft(parentNode);
                    node = parentNode;
                    parentNode = node->parent;
                }

                rotateRight(grandParentNode);
                std::swap(parentNode->color, grandParentNode->color);
                node = parentNode;
            }
        }
        else {
            Node* uncleNode = grandParentNode->left;

            if ((uncleNode != nullptr) && (uncleNode->color == RED)) {
                grandParentNode->color = RED;
                parentNode->color = BLACK;
                uncleNode->color = BLACK;
                node = grandParentNode;
            }
            else {
                if (node == parentNode->left) {
                    rotateRight(parentNode);
                    node = parentNode;
                    parentNode = node->parent;
                }

                rotateLeft(grandParentNode);
                std::swap(parentNode->color, grandParentNode->color);
                node = parentNode;
            }
        }
    }

    root->color = BLACK;
}

Review* RedBlackTree::searchInternal(Node* node, const std::string&id) {
    if (node == nullptr)
        return nullptr;

    comparisons++;
    if (id == node->data.id)
        return &(node->data);
    else if (id < node->data.id)
        return searchInternal(node->left, id);
    else
        return searchInternal(node->right, id);
}

void RedBlackTree::insert(const Review&data, long long filePos) {
    Node* newNode = new Node(data, filePos);
    Node* node = root;
    Node* parentNode = nullptr;

    while (node != nullptr) {
        parentNode = node;
        if (data.id < node->data.id)
            node = node->left;
        else
            node = node->right;
    }

    newNode->parent = parentNode;

    if (parentNode == nullptr)
        root = newNode;
    else if (data.id < parentNode->data.id)
        parentNode->left = newNode;
    else
        parentNode->right = newNode;

    fixViolation(newNode);
}

void RedBlackTree::inorderTraversal(Node* node) {
    if (node == nullptr)
        return;

    inorderTraversal(node->left);
    std::cout << "ID: " << node->data.id << ", File Position: " << node->filePos << std::endl;
    inorderTraversal(node->right);
}

void RedBlackTree::inorder() {
    inorderTraversal(root);
}
