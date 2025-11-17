
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
#include<algorithm>

class Solution {
public:
    const int INF = 0x3f3f3f3f;
    int Min = INF;

    int Deep(TreeNode*node,int deep) {
        //需要避免下面.. 可能有nullptr节点
        if (node == nullptr) { return deep; }
        // 不能nullptr节点去结算  因为可能 根本没有左树-->一条岔道 
        if (node->left == nullptr&&node->right==nullptr) {
            Min = std::min(Min, deep);
            return deep;
        }
        int Left = Deep(node->left, deep + 1);
        int Right = Deep(node->right, deep + 1);
        return std::min(Left, Right) + 1;
    }
    int minDepth(TreeNode* root) {
        if (root == nullptr) { return 0; }
        Deep(root, 1);
        return Min;
    }

    // 一样的设计 如果设计成 不使用全局Min
    int minDepth1(TreeNode* root) {
        if (root == nullptr) { return 0; }
        if (root->left == nullptr && root->right == nullptr) { return 1; }
        
        int MinDepth = INF;
        if (root->left != nullptr) {
            MinDepth = std::min(minDepth1(root->left), MinDepth);
        }
        if (root->right != nullptr) {
            MinDepth = std::min(minDepth1(root->right), MinDepth);
        }
        return MinDepth + 1;//如果没有前面... 
        //就是root + 下面的高度
    }
};