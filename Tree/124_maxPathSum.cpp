

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
    const int INF = 0x3f3f3f3f;
    //至少一个节点
    int maxpathSum=-INF;//无需每个节点都返回 自己这颗子树内的最长路径

    // 标准树型DP的话 
    // 1） 最长路径和root无关 ---> 子孩子最大
    // 2） 最长路径和root有关 --->经过root
    struct Info {
        int maxPath;//遇到的最大maxPath
        //每个节点 给父节点返回 自己为head在内最大的MAX路径
        
        int maxPathFromHead;//head为头 最大的路径值
        Info(int mP,int mPFH):maxPath(mP),maxPathFromHead(mPFH){}
    };
    Info* pathSum1(TreeNode* root) {
        if (root == nullptr) {
            // maxPath 设为系统最小值（不能是0，因为节点值可能是负数）
            // maxPathFromHead 设为0（贡献值为0）
            return new Info(-INF, 0);
        }
        Info* Left = pathSum1(root->left);
        Info* Right = pathSum1(root->right);
        //不能为负数，让选择...
        int LeftSum = std::max(Left->maxPathFromHead, 0);
        int RightSum = std::max(Right->maxPathFromHead, 0);

        int maxPath = std::max({ Left->maxPath,Right->maxPath,
            root->val + LeftSum+RightSum });
        //要去除 负数值  不要那些..
        int maxPathFromHead = std::max(LeftSum, RightSum) + root->val;

        return new Info(maxPath, maxPathFromHead);
    }

    int pathSum(TreeNode* root) {
        if (root == nullptr) { return 0; }

        int Left = std::max(pathSum(root->left),0);//限制孩子不要返回负的值？？
        int Right = std::max(pathSum(root->right),0);


        maxpathSum = std::max({Left + Right + root->val, maxpathSum });


        return std::max(Left, Right) + root->val;
    }

    int maxPathSum(TreeNode* root) {
        //pathSum(root);
        //return maxpathSum;
        return pathSum1(root)->maxPath;
    }
};