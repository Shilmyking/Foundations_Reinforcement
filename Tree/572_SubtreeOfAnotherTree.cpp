
// 另一棵树的子树
// 给你两棵二叉树root和subRoot
// 检验root中是否包含和subRoot具有相同结构和节点值的子树
// 如果存在，返回true
// 否则，返回false
// 测试链接 : https://leetcode.cn/problems/subtree-of-another-tree/

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
 
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

class Solution {

    // 检查以root 和 subRoot为head的树能不能成功配对
    bool checkIsSame(TreeNode* root, TreeNode* subRoot) {
        //root为nullptr subroot为nullptr  true
        //      nullptr         不为nullptr  false
        //     不为nullptr       为nullptr  false
        if (root == nullptr) { return subRoot == nullptr; }
        //root不nullptr
        if (subRoot == nullptr) { return false; }
        if (root == nullptr || subRoot == nullptr) {
            return root == subRoot;
        }
        //都不为nullptr
        bool lt = checkIsSame(root->left, subRoot->left);
        bool rt = checkIsSame(root->right, subRoot->right);
        bool cur = root->val == subRoot->val;
        return lt && rt && cur;
    }
    //当前为head的子树是否能配对出..
    bool isSame(TreeNode* root, TreeNode* subRoot) {
        if (checkIsSame(root, subRoot)) {
            //成功配对出  
            return true;
        }
        bool lt = false;
        if (root->left != nullptr) {
            // root->left 为head的子树 能不能配对出 subRoot
            lt = isSame(root->left, subRoot);
        }

        bool rt = false;
        if (root->right != nullptr) {
            rt = isSame(root->right, subRoot);
        }

        return  lt || rt;
    }


public:
    bool isSubtree1(TreeNode* root, TreeNode* subRoot) {
        return isSame(root, subRoot);
    }

    //序列化

    bool isSubtree2(TreeNode* root, TreeNode* subRoot) {
        preSeries(root);
        preSeries1(subRoot);
        getNext();
        return KMP2() > -1 ? true : false;
    }
    static const int MAXN = 5e3 + 2;
    static const int MAXM = 3e3 + 3;
    string str[MAXN];
    int Size = 0;
    string subStr[MAXM];
    int subSize = 0;
    int nexts[MAXM];

    void preSeries(TreeNode* root) {
        if (root == nullptr) {
            str[Size++] = "#";
        }
        else {
            str[Size++] = to_string(root->val);
            preSeries(root->left);
            preSeries(root->right);
        }
    }

    void preSeries1(TreeNode* root) {
        if (root == nullptr) {
            subStr[subSize++] = "#";
        }
        else {
            subStr[subSize++] = to_string(root->val);
            preSeries1(root->left);
            preSeries1(root->right);
        }
    }
    void getNext() {
        nexts[0] = -1;
        nexts[1] = 0;
        int i = 2, cn = nexts[1];
        while (i < subSize) {
            if (subStr[i - 1] == subStr[cn]) {
                nexts[i++] = ++cn;
            }
            else if (cn > 0) {
                cn = nexts[cn];
            }
            else {
                nexts[i++] = 0;
            }
        }
    }
    int KMP2() {
        int i = 0, j = 0;
        while (i < Size && j < subSize) {
            if (str[i] == subStr[j]) {
                i++, j++;
            }
            else if (j > 0) {
                j = nexts[j];
            }
            else {
                //此时j == 0;
                i++;
            }
        }
        return j == subSize ? i - j : -1;
    }



    const int INF = 0x3f3f3f3f;

    void preOrder(TreeNode* root, vector<int>& nums) {
        if (root == nullptr) {
            nums.push_back(-INF);
        }
        else {
            nums.push_back(root->val);
            preOrder(root->left, nums);
            preOrder(root->right, nums);
        }
    }

    vector<int>getNext(const vector<int>& nums) {
        int n = nums.size();
        vector<int>nx(n, 0);
        nx[0] = -1;
        //nx[1] = 0;
        int i = 2, cn = 0;
        while (i < n) {
            if (nums[i - 1] == nums[cn]) {
                nx[i++] = ++cn;
            }
            else if (cn > 0) {
                cn = nx[cn];
            }
            else {
                nx[i++] = 0;
            }
        }
        return nx;
    }

    //NextVal 数组 优化next
    //如果失配的情况下，s[i] == s[cn]，不跳转到cn 跳转到 next[cn]
    // 如果你之前都正确设置 next[cn]了 根本轮不到你去担心前面的 nx[cn]有没有设置成最优
    // 也就是根本不用再次往前跳  只跳一步就行了
    // 如果不是最优 getNext函数就是写错了
    vector<int>getNext1(const vector<int>& nums) {
        int n = nums.size();
        vector<int>nx(n, 0);
        nx[0] = -1;
        //nx[1] = 0;
        if (n == 1) { return nx; }

        int i = 2, cn = 0;
        while (i < n) {
            if (nums[i - 1] == nums[cn]) {
                //配对上了
                // cn  cn+1     i-1  i
                // 当前设置 i位置的 nx
                // 那就是考虑前面的前后缀最大匹配  nums[cn] nums[i-1]
                // 优化的点就是 nx[i]在i位置和主串进行匹配的时候，如果失配 会跳转到nextCn
                // 但是这时候在求nexts数组的时候就知道 nums[i] == nums[nextCn] -->注定继续失配
                // 为何不直接告诉我最优跳转点呢？？？
                int nextCn = ++cn;
                nx[i] = nums[i] == nums[nextCn] ? nx[nextCn] : nextCn;
                i++;
            }
            else if (cn > 0) {
                cn = nx[cn];
            }
            else {
                nx[i++] = 0;
            }
        }
        return nx;
    }

    bool KMP(const vector<int>& s, const vector<int>& t, const vector<int>& nx) {
        int i = 0, j = 0, n = s.size(), m = t.size();
        while (i < n && j < m) {
            // j 有可能跳转到 -1 了 直接不经过 j == 0 这一步
            if (j == -1 || (s[i] == t[j])) {
                // j == -1 -->无法配对  i去下一个位置 刚好 j也需要为0开始 
                // 代码复用
                i++, j++;
            }
            else {
                j = nx[j];
            }
        }
        return j == m;
    }

    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        vector<int>Str, subStr;
        Str.reserve(MAXN), subStr.reserve(MAXM);
        preOrder(root, Str);
        preOrder(subRoot, subStr);
        vector<int>nx = getNext1(subStr);
        return KMP(Str, subStr, nx);
    }
};