
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


    //void f(vector<int>& nums, TreeNode* root) {
    //    TreeNode* cur = root;
    //    Size = 0; // 初始化栈大小

    //    // 循环条件：栈不为空（还有回头路） 或者 cur不为空（还有新路要探索）
    //    while (Size > 0 || cur != nullptr) {

    //        // 步骤1：一直往左走，沿途将节点压栈
    //        while (cur != nullptr) {
    //            Stack[Size++] = cur;
    //            cur = cur->left;
    //        }

    //        // 步骤2：左边走到头了，弹出栈顶节点（这就是中序遍历的“中”）
    //        cur = Stack[--Size]; // 弹栈

    //        // 步骤3：处理当前节点
    //        nums.push_back(cur->val);

    //        // 步骤4：转向右子树（如果右边为空，下一轮循环会继续弹栈处理更上层的父节点）
    //        cur = cur->right;
    //    }
    //}




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