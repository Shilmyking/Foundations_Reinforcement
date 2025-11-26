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
    static const int MAXN = 105;
    TreeNode* que[MAXN];
    int l = 0, r = 0;
    bool flag = false;
    //如果遇到 存在节点不是孩子双全 后续还存在有节点是存在孩子的 --->false
    bool isComTree(TreeNode* root) {
        que[r++] = root;
        TreeNode* cur;
        while (l < r) {
            cur = que[l++];
            if (flag == true && (cur->left != nullptr || cur->right != nullptr)) {
                return false;
            }
            if (cur->left == nullptr && cur->right != nullptr) {
                return false;
            }
            if (cur->left == nullptr || cur->right == nullptr) {
                flag = !flag;
            }
            if (cur->left != nullptr) {
                que[r++] = cur->left;
            }
            if (cur->right != nullptr) {
                que[r++] = cur->right;
            }
        }
        return true;
    }

    bool isCompleteTree(TreeNode* root) {
        return isComTree(root);
    }
};