
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
    static const int MAXN = 1e4 + 5;
    int ans[MAXN], ansi = 0;
    void inOrder(TreeNode*root) {
        if (root != nullptr) {
            inOrder(root->left);
            ans[ansi++] = root->val;
            inOrder(root->right);
        }
    }
    TreeNode* build(int l, int r) {
        if (l > r) {
            return nullptr;
        }
        int mid = (l + r) / 2;
        TreeNode* root = new TreeNode(ans[mid]);
        if (l < mid) {
            root->left = build(l, mid - 1);
        }
        if (r > mid) {
            root->right = build(mid + 1, r);
        }
        
        return root;
    }
    TreeNode* balanceTree(TreeNode* root) {
        inOrder(root);
        return build(0, ansi-1);
    }

    TreeNode* balanceBST(TreeNode* root) {
        if (root == nullptr) { return nullptr; }
        return balanceTree(root);
    }
};