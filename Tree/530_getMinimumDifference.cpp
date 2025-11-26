
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
    const int INF = 0x3f3f3f3f;
    //中序  or  前序(累加和数组 -->也可以优化为一个变量)
    int last = -INF;
    int Min = INF;
    void inOrder(TreeNode* root) {
        if (root != nullptr) {
            inOrder(root->left);
            if (last != -INF) {
                Min = std::min(Min, root->val - last);
            }
            last = root->val;
             inOrder(root->right);
        }

    }

    int getMinimumDifference(TreeNode* root) {
        inOrder(root);
        return Min;
    }
};