
#include<vector>
#include<cstring>
#include<iostream>
#include<string>
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
    static const int MAXN = 1e2 + 5;
    TreeNode* Stack[MAXN];
    int Size = 0;

    //中序遍历  左中右
    void f(vector<int>&nums,TreeNode* root) {
        if (root == nullptr) { return; }
        TreeNode* cur = root;
        while (Size>0||cur!=nullptr) {

            if (cur != nullptr) {
                //一直往左
                Stack[Size++] = cur;
                cur = cur->left;
            }
            else {//左边为空了  处理自己 再去自己的右孩子
                // cur 为空
                cur = Stack[--Size];
                nums.push_back(cur->val);
                // 去右树  右树处理完 就往上回溯..
                cur = cur->right;
            }

        }
    }

public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int>nums;
        nums.reserve(101);
        f(nums, root);
        return nums;
    }
};