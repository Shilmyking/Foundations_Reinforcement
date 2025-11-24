
#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
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
    using ll = long long;
    ll ans = 0;
    ll target;
public:
    unordered_map<ll, ll> Map;
    // 前缀和长度  需要知道当前路径下 preSum的大小 对应的路径条数
    // 需要及时更新Map  如果往下递归增加条数
    // 递归回来了 先去更新路径
    // 必须知道当前的Sum值
    void f(TreeNode* root, ll Sum) {
        if (root == nullptr) { return; }

        Sum += root->val;//此前的Sum加上当前节点 
        ans += Map[Sum - target];//查找当前节点为结尾下  此前累加和为Sum-target的路径数

        Map[Sum] += 1;//需要往下走了 那你给到当前的信息到Map里面
        f(root->left, Sum);
        f(root->right, Sum);

        //需要往上回溯了  需要把之前加入的信息去除  带路径的递归
        Map[Sum] -= 1;

    }

    int pathSum(TreeNode* root, int targetSum) {
        Map.clear();
        Map[0] = 1;//初始状况下 一定是存在1的
        target = targetSum;
        f(root, 0);
        return ans;
    }
};