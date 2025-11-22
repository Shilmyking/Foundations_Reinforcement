


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
    // 1）双栈  前序：中左右   后序：左右中  
    static const int MAXN = 105;
    TreeNode* stk1[MAXN];
    int sz1 = 0;
    TreeNode* stk2[MAXN];
    int sz2 = 0;
    vector<int>post(TreeNode* root) {

        stk1[sz1++] = root;
        TreeNode* cur;
        while (sz1 > 0) {
            cur = stk1[--sz1];
            // 前序 中左右  
            stk2[sz2++] = cur;//中
            //  左右 逆序-->右左
            if (cur->left != nullptr) {
                stk1[sz1++] = cur->left;
            }
            if (cur->right != nullptr) {
                stk1[sz1++] = cur->right;
            }
        }
        vector<int>nums;
        while (sz2 > 0) {
            nums.push_back(stk2[--sz2]->val);
        }
        return nums;
    }

    // 2）单栈  卡位置 设置标记
    // 左右中 
    vector<int>post1(TreeNode* root) {
        TreeNode* cur;
        // 如果nums内没有加入过节点 head就一直是root
        // 此后head就是上一次 pop的节点
        // 也就是head作为哨兵 标识孩子是否处理过
        TreeNode* head = root;
        stk1[sz1++] = root;
        vector<int>nums;
        while (sz1 > 0) {
            cur = stk1[sz1 - 1];
            if (cur->left != nullptr &&
                //如果 head是cur的左孩子/右孩子-->左孩子处理过了
                head != cur->left &&
                head != cur->right) {
                stk1[sz1++] = cur->left;
            }
            else if (cur->right != nullptr &&
                // 判断是否处理过右树
                     cur->right != head) {
                stk1[sz1++] = cur->right;
            }
            else {
                // cur为叶子节点 or 孩子都处理过了
                nums.push_back(cur->val);
                head = stk1[--sz1];
            }
        }
        return nums;
    }
    
    vector<int> postorderTraversal(TreeNode* root) {
        if (root == nullptr) { return vector<int>(); }
        return post1(root);
    }
};