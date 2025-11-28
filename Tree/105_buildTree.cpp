

#include<algorithm>
#include<vector>
#include<unordered_map>
#include<cstring>

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
    // 3 9 20 15 7  pre
    // 9 3 15 20 7  in

    // 传参  前序的范围 prel  prer
    //       中序的范围 inl   inr

    // 给到值  找到下标
    unordered_map<int, int>Map;//存储的是前序的 部分下标

    TreeNode* f(const vector<int>& preorder, int prel, int prer, const  vector<int>& inorder, int inl, int inr) {
        if (prel > prer) {  // 前序第一个就是 root
            return nullptr;
        }
        // 当前位置的 遍历的第一位
        TreeNode* root = new TreeNode(preorder[prel]);
        if (prel == prer) {
            return root;
        }
        int k = Map[preorder[prel]];//pre 部分
        // pre : prel(..........)[.........prer]
        // in:  (inl...........)k[..........inr]
        root->left = f(preorder, prel + 1, prel + k - inl, inorder, inl, k - 1);
        root->right = f(preorder, prel + k - inl + 1, prer, inorder, k + 1, inr);
        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();
        for (int i = 0; i < n; i++) {
            Map[inorder[i]] = i;
        }
        // n-1
        return f(preorder, 0, n - 1, inorder, 0, n - 1);
    }
};