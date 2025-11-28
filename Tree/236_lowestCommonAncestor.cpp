

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


/*
如果当前节点是 null 或者是目标节点之一（p 或 q），直接返回当前节点。
递归左右子树：
左子树返回值为 l，右子树返回值为 r。
根据左右子树的返回值判断：
如果左子树返回 null，说明 p 和 q 都在右子树中，返回右子树的结果。
如果右子树返回 null，说明 p 和 q 都在左子树中，返回左子树的结果。
如果左右子树都不为 null，说明当前节点就是最近公共祖先，返回当前节点。
*/


// 二叉树的
class Solution {
    TreeNode* f(TreeNode* root, TreeNode* p, TreeNode* q) {
        // 只要搜到其中一方 --->直接返回了  
        // 因为另一个一定是自己的后代 或者 根本不在同一颗子树上
        if (root == p || root == q || root == nullptr) {
            return root;
        }
        TreeNode* left = f(root->left, p, q);
        TreeNode* right = f(root->right, p, q);
        //左右孩子都没有找到
        if (left == nullptr && right == nullptr) {
            return nullptr;
        }
        //左右孩子都搜索到了 --->自己就是最近公共祖先
        if (left != nullptr && right != nullptr) {
            return root;
        }
        //剩下的就是一个搜到一个没搜到
        return left == nullptr ? right : left;
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return f(root, p, q);
    }
};