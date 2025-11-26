
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

    void preSer(string& ans, TreeNode* root) {
        if (root == nullptr) {
            ans += "#,";
        }
        else {
            ans += to_string(root->val)+",";
            preSer(ans, root->left);
            preSer(ans, root->right);
        }
    }

    string serialize(TreeNode* root) {
        string ans;
        preSer(ans, root);
        return ans;
    }

    int parseInt(const string& s, int& ptr) {
        int val = 0;
        int sign = 1;

        // 处理负号  后续*-1即可
        if (s[ptr] == '-') {
            sign = -1;
            ptr++;
        }

        // 提取数字直到遇到 ','
        while (ptr < s.size() && s[ptr] != ',') {
            val = val * 10 + (s[ptr] - '0');
            ptr++;
        }
        //跳过 ,
        ptr++; 
        return val * sign;
    }

    TreeNode* dePreSer(const string& s, int& ptr) {
        if (ptr >= s.size()) { return nullptr; }

        if (s[ptr] == '#') {
            ptr += 2; 
            return nullptr;
        }

        int val = parseInt(s, ptr);
        TreeNode* node = new TreeNode(val);

        node->left = dePreSer(s, ptr);
        node->right = dePreSer(s, ptr);
        return node;
    }

    TreeNode* deserialize(string data) {
        int ptr = 0;
        return dePreSer(data, ptr);
    }
};

#if 0
// 就是 怎么序列化 怎么反序列化
int find(const string& s, int ptr) {
    while (ptr < s.size() && s[ptr] != ',') {
        ptr++;
    }
    return ptr;
}

TreeNode* dePreSer(const string& s, int& ptr) {
    if (ptr >= s.size()) { return nullptr; }
    if (s[ptr] == '#') {
        ptr += 2;
        return nullptr;
    }
    //遍历找下一个，在哪里
   // int next = s.find(',', ptr);
    int next = find(s, ptr);
    string numStr = s.substr(ptr, next - ptr);
    int val = stoi(numStr);
    TreeNode* node = new TreeNode(val);
    ptr = next + 1;
    node->left = dePreSer(s, ptr);
    node->right = dePreSer(s, ptr);
    return node;
}
#endif