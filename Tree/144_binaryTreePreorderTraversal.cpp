
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
    static const int MAXN = 102;
    TreeNode* Stack[MAXN];
    int Size = 0;

public:
    // 前序 ： 中左右
    // 因为使用栈结构  先判断 right 再 left  才能逆序正确
    void f(vector<int>&nums,TreeNode*root) {
        if (root == nullptr) { return; }
        Stack[Size++] = root;
        while (Size > 0) {
            TreeNode* cur = Stack[--Size];
            nums.push_back(cur->val);

            if(cur->right!=nullptr){
                Stack[Size++] = cur->right;
            }
            if (cur->left != nullptr) {
                Stack[Size++] = cur->left;
            }
        }
    }

    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> nums;
        nums.reserve(102);
        f(nums, root);
        return nums;
    }
};