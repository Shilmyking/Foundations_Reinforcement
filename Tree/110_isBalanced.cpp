

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
    int height(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int Left = height(root->left);
        int Right = height(root->right);

        return std::max(Left, Right) + 1;
    }
    bool balance(TreeNode* root) {
        if (root == nullptr) { return true; }
        int Left = height(root->left);
        int Right = height(root->right);
        return std::abs(Left - Right) <= 1 && 
            isBalanced(root->left)&&
            isBalanced(root->right);
    }
public:
    bool isBalanced(TreeNode* root) {
        return balance(root);
    }
};