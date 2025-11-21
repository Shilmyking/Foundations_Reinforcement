


#include<iostream>
#include<vector>

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
    // 1）双栈  前序：中左右   后序：左右中  
    // 2）单栈  卡位置 设置标记
    vector<int> postorderTraversal(TreeNode* root) {

    }
};