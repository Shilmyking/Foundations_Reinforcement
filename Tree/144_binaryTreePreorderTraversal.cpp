
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


char cnt = 'a';

void dfs(TreeNode* root) {
    if (root == nullptr) {
        cout << cnt++ << endl;
        return;
    }

    cout << "pre:" << root->val << endl;
    dfs(root->left);
    cout << "in:" << root->val << endl;
    dfs(root->right);
    cout << "post:" << root->val << endl;

}

signed main() {
  

    TreeNode* llt = new TreeNode(4);
    TreeNode* lrt = new TreeNode(5);
    TreeNode* lt = new TreeNode(2, llt, lrt);

    TreeNode* rlt = new TreeNode(6);
    TreeNode* rrt = new TreeNode(7);
    TreeNode* rt = new TreeNode(3,rlt,rrt);

    TreeNode* root = new TreeNode(1, lt, rt);

    dfs(root);
    cout << sizeof(long long);

    cout << sizeof(long);
}
