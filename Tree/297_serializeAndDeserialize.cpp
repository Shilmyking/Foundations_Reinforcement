
#include<string>
#include<cstring>
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


class Codec {
public:

    void preSer(string&ans,TreeNode* root) {
        if (root == nullptr) {
            ans += "#,";
        }
        ans += to_string(root->val);
        preSer(ans,root->left);
        preSer(ans, root->right);
    }

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string ans;
        preSer(ans, root);
        return ans;
    }

    TreeNode* dePreSer(const string& s) {

    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));