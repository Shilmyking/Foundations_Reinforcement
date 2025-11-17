

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
   // int depth = 0;
    int Deep(TreeNode* node,int deep) {
        if (node == nullptr) { 
            //depth = std::max(deep, depth);
            return 0; // nullptr  没有高度
        }
        //问左右孩子
        int Left = Deep(node->left,deep+1) ;
        int Right = Deep(node->right, deep + 1);

        return std::max(Left, Right) + 1;
    }

    int maxDepth(TreeNode* root) {
        if (root == nullptr) { return 0; }
        return Deep(root, 0);
    }
};