

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
    int target;

    //void PathSum(TreeNode* head, vector<vector<int>>& ans, vector<int>& nums, int Sum) {
    //    if (head == nullptr) {
    //        return;
    //    }
    //    nums.push_back(head->val);//来到一个节点向下递归

    //    if (Sum + head->val == target) {
    //        ans.push_back(nums);
    //    }
    //    PathSum(head->left, ans, nums, Sum + head->val);

    //    PathSum(head->right, ans, nums, Sum + head->val);

    //    nums.pop_back();//往上回溯
    //}

    //需要到达叶子节点
    void PathSum(TreeNode* head, vector<vector<int>>& ans, vector<int>& nums, int Sum) {
        if (head == nullptr) { return; }
        if (head->left == nullptr && head->right == nullptr) {

            if (Sum+head->val == target) {
                nums.push_back(head->val);
                ans.emplace_back(nums);
                nums.pop_back();
            }
            return;
        }
        nums.push_back(head->val);//来到一个节点向下递归

        PathSum(head->left, ans, nums, Sum + head->val);

        PathSum(head->right, ans, nums, Sum + head->val);

        nums.pop_back();//往上回溯
    }
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> ans;
        if (root == nullptr) { return ans; }
        target = targetSum;
        vector<int>nums;
        PathSum(root, ans, nums, 0);
        return ans;
    }
};