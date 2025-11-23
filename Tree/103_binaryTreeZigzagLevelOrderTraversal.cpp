
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
    
    vector<vector<int>> zLevelOrder(vector<vector<int>>& ans, TreeNode* root) {
        que[r++] = root;
        bool reverse = false;
        int i = 0;
        TreeNode* cur;
        vector<int>tmp;
        while (l < r) {
            int Size = r - l;
            //下面就是 把 加入节点(收集答案)的顺序 和 bfs分开
            // 收集答案要逆序的层数就逆序  节点还是一样按照正常的bfs收集孩子
            for (int i = reverse ? r - 1 : l, j = reverse ? -1 : 1, k = 0;
                k < Size; i += j, k++) {
                cur = que[i];
                tmp.push_back(cur->val);
            }
            for (int i = 0; i < Size; i++) {
                cur = que[l++];
                if (cur->left != nullptr) {
                    que[r++] = cur->left;
                }
                if (cur->right != nullptr) {
                    que[r++] = cur->right;
                }
            }
            //错误的改变孩子进入的顺序  无法收集
            //if (reverse == true) {
            //    //这样破坏下一层孩子进入的顺序
            //    for (int i = Size - 1; i >= 0; i--) {
            //        cur = que[l + i];
            //        tmp.push_back(cur->val);
            //        if (cur->left != nullptr) {
            //            que[r++] = cur->left;
            //        }
            //        if (cur->right != nullptr) {
            //            que[r++] = cur->right;
            //        }
            //    }
            //    l += Size;
            //}
            //else {
            //    for (int i = 0; i < Size; i++) {
            //        cur = que[l++];
            //        tmp.push_back(cur->val);
            //        if (cur->left != nullptr) {
            //            que[r++] = cur->left;
            //        }
            //        if (cur->right != nullptr) {
            //            que[r++] = cur->right;
            //        }
            //    }
            //}
            ans.push_back(tmp);
            tmp.clear();
            reverse = !reverse;
        }
        return ans;
    }

    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>>ans;
        if (root == nullptr) { return ans; }
        zLevelOrder(ans, root);
        return ans;
    }
};