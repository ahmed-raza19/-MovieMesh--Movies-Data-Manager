#pragma once
#include "MovieNode.h"
#include <iostream>
#include <algorithm>
using namespace std;

// AVL NODE
struct AVLNode
{
    MovieNode *data; // Pointer to actual data (MovieNode)
    AVLNode *left;   // Left child
    AVLNode *right;  // Right child
    int height;      // Height of this node (for balancing)

    // Constructor
    AVLNode(MovieNode *val)
    {
        this->data = val;
        this->left = nullptr;
        this->right = nullptr;
        this->height = 1;
    }
};

// AVL TREE CLASS
class AVLTree
{
private:
    AVLNode *root;

    // Getter for height
    int height(AVLNode *node)
    {
        // if node is null, height is 0
        if (node == nullptr)
            return 0;
        return node->height;
    }

    // Getter for balancing factor
    int calculateBF(AVLNode *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return height(node->left) - height(node->right);
    }

    // RIGHT ROTATION (for LL case)
    AVLNode *rightRotate(AVLNode *k1)
    {

        AVLNode *k2 = k1->left;
        k1->left = k2->right;
        k2->right = k1;

        // Update heights
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->left), height(k2->right)) + 1;

        return k2; // New root
    }

    // LEFT ROTATION (for RR case)
    AVLNode *leftRotate(AVLNode *k1)
    {

        AVLNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;

        // Update heights
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->left), height(k2->right)) + 1;

        return k2; // New root
    }

    // LEFT-RIGHT ROTATION (for LR case)
    AVLNode *LeftRightRotation(AVLNode *k1)
    {
        k1->left = leftRotate(k1->left);
        return rightRotate(k1);
    }

    // RIGHT-LEFT ROTATION (for RL case)
    AVLNode *RightLeftRotation(AVLNode *k1)
    {
        k1->right = rightRotate(k1->right);
        return leftRotate(k1);
    }

    // INSERT function recursively
    AVLNode *insertNode(AVLNode *node, MovieNode *data)
    {
        // if node is null, creating a new node
        if (node == nullptr)
        {
            AVLNode *nn = new AVLNode(data);
            return nn;
        }

        if (data->title < node->data->title)
            node->left = insertNode(node->left, data);

        else if (data->title > node->data->title)
            node->right = insertNode(node->right, data);

        else
            return node; // Duplicate node

        // Updating height
        node->height = max(height(node->left), height(node->right)) + 1;

        // Calculating balancing factor
        int bal = calculateBF(node);

        // Left-Left Case
        if (bal > 1 && data->title < node->left->data->title)
            return rightRotate(node);

        // Right-Right Case
        if (bal < -1 && data->title > node->right->data->title)
            return leftRotate(node);

        // Left-Right Case
        if (bal > 1 && data->title > node->left->data->title)
        {
            return LeftRightRotation(node);
        }

        // Right-Left Case
        if (bal < -1 && data->title < node->right->data->title)
        {
            return RightLeftRotation(node);
        }

        return node;
    }

    // SEARCH recursively
    MovieNode *searchNode(AVLNode *node, const string &name)
    {
        if (node == nullptr)
            return nullptr;

        else if (name > node->data->title)
            return searchNode(node->right, name);

        else if (name < node->data->title)
            return searchNode(node->left, name);

        else
            return node->data;
    }

    // INORDER traversal
    void inorder(AVLNode *node)
    {
        if (node==nullptr)
            return;

        inorder(node->left);
        node->data->display();
        inorder(node->right);
    }

    // Helper: Search by Year (Inorder Traversal)
    void searchYearHelper(AVLNode* node, int year, bool &found, int &count)
    {
        if (node == nullptr)
            return;

        searchYearHelper(node->left, year, found, count);

        // Check the condition
        if (node->data->year == year)
        {
            node->data->display();
            found = true;
            count++;
        }

        searchYearHelper(node->right, year, found, count);
    }

    // Helper: Search by Rating Range (Inorder Traversal)
    void searchRatingHelper(AVLNode* node, double minR, double maxR, bool &found, int &count)
    {
        if (node == nullptr)
            return;

        searchRatingHelper(node->left, minR, maxR, found, count);

        // Check the condition
        if (node->data->rating >= minR && node->data->rating <= maxR)
        {
            node->data->display();
            found = true;
            count++;
        }
        searchRatingHelper(node->right, minR, maxR, found, count);
    }

public:
    AVLTree() : root(nullptr) {}

    // Insert with custom compare function
    void insert(MovieNode *data)
    {
        root = insertNode(root, data);
    }

    // Search with string key
    MovieNode *search(const string &key)
    {
        return searchNode(root, key);
    }

    // Display all in sorted order
    void displayAll()
    {
        inorder(root);
    }

    // Public Function: Search by Year
    void searchByYear(int year)
    {
        bool found = false;
        int count = 0;
        cout << "\033[1;35m\n--- Search Results for Year: \033[36m" << year << "\033[1;35m ---\033[0m\n";
        searchYearHelper(root, year, found, count);
        
        cout << "\033[1;33m" << endl << count << "\033[0m";

        if (!found) 
            cout << "\033[1;31mNo movies found for this year.\033[0m\n";
        cout << "\033[1;35m--------------------------------------\033[0m\n";
    }

    // Public Function: Search by Rating
    void searchByRating(double minR, double maxR)
    {
        bool found = false;
        int count = 0;
        cout << "\033[1;35m\n--- Search Results for Rating [\033[36m" << minR << "\033[1;35m - \033[36m" << maxR << "\033[1;35m] ---\033[0m\n";
        searchRatingHelper(root, minR, maxR, found, count);
        
        cout << "\033[1;33m" << endl << count << "\033[0m";
        if (!found) 
            cout << "\033[1;31mNo movies found in this range.\033[0m\n";
        cout << "\033[1;35m---------------------------------------------\033[0m\n";
    }
};