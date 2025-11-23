
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
public:
    int target;
    bool PathSum(TreeNode* head, int Sum) {
        
        if (head->left==nullptr&&head->right==nullptr) {
            return Sum + head->val == target;
        }
        bool Left = false, Right = false;
        if (head->left != nullptr) {
            Left = PathSum(head->left, Sum + head->val);
        }

        if (head->right != nullptr) {
            Right = PathSum(head->right, Sum + head->val);
        }
        return Left || Right;
    }

    bool hasPathSum(TreeNode* root, int targetSum) {
        if (root == nullptr) { return false; }
        target = targetSum;
        return PathSum(root, 0);
    }
};