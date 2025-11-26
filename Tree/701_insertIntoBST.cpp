
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
    TreeNode* insert(TreeNode* root, int val) {
        TreeNode* cur = root;
        TreeNode* last = nullptr;
        int soni = 0;//左
        while (cur != nullptr) {
            last = cur;
            if (cur->val >= val) {
                cur = cur->left;
                soni = 0;
            }
            else {
                cur = cur->right;
                soni = 1;
            }
        }
        if (last == nullptr) {
            return new TreeNode(val);
        }
        if (soni == 0) {
            last->left = new TreeNode(val);
        }
        else {
            last->right = new TreeNode(val);
        }
        return root;
    }
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        return insert(root, val);
    }
};