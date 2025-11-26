
#include<string>
#include<cstring>
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
    TreeNode* find(TreeNode* root, int val) {
        TreeNode* cur = root;
        while (cur != nullptr) {
            if (cur->val == val) {
                break;
            }
            else if (cur->val > val) {
                cur = cur->left;
            }
            else {
                cur = cur->right;
            }
        }
        return cur;
    }

    TreeNode* searchBST(TreeNode* root, int val) {
        return find(root, val);
    }
};