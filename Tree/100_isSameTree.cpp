
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
    bool isSame(TreeNode* p, TreeNode* q) {
        if (p == nullptr || q == nullptr) {
            return p == q;
        }
        bool Left = isSame(p->left, q->left);
        bool Right = isSame(p->right, q->right);
        bool cur = p->val == q->val;
        return Left && Right && cur;
    }
    bool isSameTree(TreeNode* p, TreeNode* q) {
        return isSame(p, q);
    }
};