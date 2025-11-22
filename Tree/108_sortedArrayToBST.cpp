
#include<algorithm>
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
    TreeNode* build(const vector<int>& nums, int l, int r) {
        if (l > r) {
            return nullptr; 
        }
        int mid = (l + r) / 2;
        TreeNode* cur = new TreeNode(nums[mid]);
        cur->left = build(nums, l, mid - 1);
        cur->right = build(nums, mid + 1, r);
        return cur;
    }

    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return build(nums, 0, nums.size() - 1);
    }
};