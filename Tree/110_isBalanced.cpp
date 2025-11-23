

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};


class Solution {
    int deep(TreeNode* root) {
        return (root != nullptr ? 1 + std::max(deep(root->left), deep(root->right)) : 0);
    }
    bool balance(TreeNode* root) {
        if (root == nullptr) { return true; }
        int Left = deep(root->left);
        int Right = deep(root->right);
        return std::abs(Left - Right) <= 1;
    }
public:
    bool isBalanced(TreeNode* root) {
        return balance(root);
    }
};