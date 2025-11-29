
#include<algorithm>
#include<vector>
#include<unordered_map>
#include<cstring>

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
    // value  -->  index
    unordered_map<int, int >Map;
    TreeNode* build(const vector<int>& inorder, int l1, int r1,
        const vector<int>& postorder, int l2, int r2) {
        if (l2 > r2) { return nullptr; }

        TreeNode* root = new TreeNode(postorder[r2]);
        if (l2 == r2) { return root; }//不存在孩子

        int k = Map[root->val];
        // 左侧 k - l1 个数字

        root->left = build(inorder, l1, k - 1, postorder, l2, l2 + (k - l1 - 1));

        root->right = build(inorder, k + 1, r1, postorder, l2 + (k - l1), r2 - 1);
        return root;
    }

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n = inorder.size();
        //收集中序位置   当知道了root的值之后 就能知道左右子树如何划分
        for (int i = 0; i < n; i++) {
            Map[inorder[i]] = i;
        }
        return build(inorder, 0, n - 1, postorder, 0, n - 1);
    }
};