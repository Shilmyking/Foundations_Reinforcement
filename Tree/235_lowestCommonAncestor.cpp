

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

//BSTree 下
class Solution {
    //利用BSTree性质
    TreeNode* f(TreeNode*root,TreeNode*p,TreeNode*q) {
        if (root == nullptr || root == p || root == q) {
            return root;
        }
        int Min = p->val > q->val ? q->val:p->val;
        int Max = Min == p->val ? q->val : p->val;
        if()
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return f(root, p, q);
    }
};
