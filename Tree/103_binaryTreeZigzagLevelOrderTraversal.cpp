
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
        while (l < r) {
            int Size = r - l;
            if (reverse == true) {

            }
            else {
                for (int i = 0; i < Size; i++) {

                }
            }
            reverse = !reverse;
        }
    }

    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>>ans;
        if (root == nullptr) { return ans; }

    }
};