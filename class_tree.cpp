/*
Balanced binary search tree written during class.
AVL balancing algo:
R - height of the right subtree is more than the height of the left one.
L - vice versa.
R - R = 1 l turn
L - L = 1 r turn
R - L = 1 r 1 l 
L - R = 1 l 1 r
*/
// template <typename T>
#include <algorithm>
#include <cmath>
#include <iostream>

struct TreeNode
{
    TreeNode* left;
    TreeNode* right;
    int tree_height;
    int value;
};

unsigned int compute_height(TreeNode*);

TreeNode* left_rotation(TreeNode* node)
{
    auto right_node { node->right };
    node->right = right_node->left;
    right_node->left = node;
    node->tree_height = compute_height(node);
    right_node->tree_height = compute_height(right_node);
    return right_node;
}

TreeNode* right_rotation(TreeNode* node)
{
    auto left_node { node->left };
    node->left = left_node->right;
    left_node->right = node;
    node->tree_height = compute_height(node);
    left_node->tree_height = compute_height(left_node);
    return left_node;
}

unsigned int compute_height(TreeNode* node)
{
    return std::max( node->left->tree_height, node->right->tree_height ) + 1;
}

bool contains(TreeNode* node, int value)
{
    if (!node) return false;
    else if(node->value == value) {
        return true;
    } else if (value < node->value) {
        return contains(node->left, value);
    } else {
        return contains(node->right, value);
    } 
}

void print(TreeNode* node) 
{
    if (!node) return;
    else {
        print(node->left);
        std::cout << node->value << ' ';
        print(node->right);
    } 
}

TreeNode* balance(TreeNode* root)
{
    if (!root->right || !root->left) return root;
    int diff { root->right->tree_height - root->left->tree_height };
    if (std::abs(diff) <= 1) 
    {
        return root;
    } else if(diff > 0) {
        if (root->right->left->tree_height < root->right->right->tree_height) {
            return left_rotation(root);
        } else {
            // auto right_left = root->right->left;
            // right_rotation(root->right);
            root->right = right_rotation(root->right);
            return left_rotation(root);
        }   
    } else {
        if (root->left->right->tree_height < root->left->left->tree_height) {
            right_rotation(root);
        } else {
            // auto left_right = root->left->right;
            // left_rotation(root->left);
            root->left = left_rotation(root->left);
            return right_rotation(root);
        }   
    }
}

TreeNode* insert_inner(TreeNode* root, int value) 
{
    root->tree_height++;

    if (value <= root->value) {
        if (!root->left) {
            auto new_node = new TreeNode{};
            new_node->value = value;
            new_node->left = new_node->right = nullptr;
            root->left = new_node;
        } else {
            return insert_inner(root->left, value);
        }
    } else {
        if (!root->right) {
            auto new_node = new TreeNode{};
            new_node->value = value;
            new_node->right = new_node->left = nullptr;
            root->right = new_node;
        } else {
            return insert_inner(root->right, value);
        }
    }
}

TreeNode* insert(TreeNode* root, int value) {
    return balance(insert_inner(root, value));
}

int main()
{
    TreeNode root{};
    root.left  = new TreeNode{};
    root.right = new TreeNode{};
    root.value = 1;
    

    return 0;
}