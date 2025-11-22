
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
public:
    static const int MAXN = 2e3 + 2;
    TreeNode* que[MAXN];
    int l = 0, r = 0;
    void levelOrder(vector<vector<int>>& ans, TreeNode* root) {
        que[r++] = root;
        vector<int>tmp;
        while (l < r) {
            int Size = r - l;
            TreeNode* cur;
            for (int i = 0; i < Size; i++) {
                cur = que[l++];
                tmp.push_back(cur->val);
                if (cur->left != nullptr) {
                    que[r++] = cur->left;
                }
                if (cur->right != nullptr) {
                    que[r++] = cur->right;
                }
            }
            ans.push_back(tmp);
            tmp.clear();
        }

    }
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>>ans;
        if (root == nullptr) { return ans; }
        levelOrder(ans, root);
        return ans;
    }
};