
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
    // Morris 中序 相当于是 要找逆序对
    // 逆序对可能是 1次出现  --> 相邻两个位置的数值下降
    //  2次出现？

    void Morris(TreeNode* root) {
        TreeNode* cur = root;
        TreeNode* last = nullptr;
        // 查找违规处  逆序对
        TreeNode* first = nullptr;
        TreeNode* second = nullptr;
        while (cur != nullptr) {
            TreeNode* mostRight = cur->left;

            if (mostRight != nullptr) {
                while (mostRight->right != nullptr && mostRight->right != cur) {
                    mostRight = mostRight->right;
                }
                if (mostRight->right != cur) {
                    mostRight->right = cur;
                    cur = cur->left;
                    continue;
                }
                else {
                    //指向cur的指针 置空
                    mostRight->right = nullptr;
                }
            }
            //逆序对出现
            if (last != nullptr && last->val >= cur->val) {
                // first如果更新过  那就是第一个需要被交换的
                first = first == nullptr ? last : first;
                //只要出现 second就变为cur
                second = cur;
            }
            last = cur;
            cur = cur->right;
        }
        std::swap(first->val, second->val);
    }
    void recoverTree(TreeNode* root) {
        Morris(root);
    }
};