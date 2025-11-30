

#include<vector>
#include<algorithm>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}

};
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

//层序遍历
class Solution {
public:
    TreeNode* que[104];
    int l = 0, r = 0;

    vector<int> rightSideView(TreeNode* root) {
        vector<int>ans;
        if (root == nullptr) { return ans; }
        que[r++] = root;
        while (l < r) {
            TreeNode* cur;
            int sz = r - l;
            for (int i = 0; i < sz; i++) {
                cur = que[i + l];
                if (cur->left != nullptr) {
                    que[r++] = cur->left;
                }
                if (cur->right != nullptr) {
                    que[r++] = cur->right;
                }
                if (i == sz - 1) {
                    ans.push_back(cur->val);
                }
            }
            l += sz;
        }
        return ans;
    }
};