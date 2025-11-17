
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
    bool isSame(TreeNode* left, TreeNode* right) {
        //存在nullptr 就比较是否相等 
        // 三种情况嘛..
        if (left == nullptr || right == nullptr)
        {
            return left==right;
        }

        //两边都不为nullptr
        //当前位置
        bool cur = left->val == right->val;
        //左右孩子
        bool Right = isSame(left->right, right->left);
        bool Left = isSame(left->left, right->right);
        return cur && Right && Left;


    }
public:
    bool isSymmetric(TreeNode* root) {
        if (root == nullptr) { return true; }
        return isSame(root->left, root->right);
    }
};