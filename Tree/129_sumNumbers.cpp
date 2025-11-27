

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
    int ans = 0;

    void sumPath(TreeNode* root, int num) {
        if (root == nullptr) {
            return;
        }
        // 不对诶...
        if (root->left == nullptr&&root->right==nullptr) {
            //就是这样
            ans += num*10+root->val;
        }
        else {
            sumPath(root->left, num * 10 + root->val);
            sumPath(root->right, num * 10 + root->val);
        }

    }

    int sumNumbers(TreeNode* root) {
        sumPath(root, 0);
        return ans;
    }
};