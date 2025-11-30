
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


// 递归 非递归 都需要 空间 
// Morris遍历？？
class Solution {
public:
    void Morris(TreeNode* root) {
        TreeNode* cur = root;
        while (cur != nullptr) {
            TreeNode* mostRight = cur->left;
            if (mostRight != nullptr) {
                
                while (mostRight->right != nullptr) {
                    mostRight = mostRight->right;
                }
                // mostRight就是前驱  此刻右孩子为nullptr  接上cur的右孩子
                mostRight->right = cur->right;

                // cur右孩子改为指向左孩子
                cur->right = cur->left;
                cur->left = nullptr;//这里恰好 退出if再次遇到if --->走right了
            }
            else {
                cur = cur->right;//就是此前原树的左孩子
            }

        }
    }

    void flatten(TreeNode* root) {
        if (root != nullptr) {
            root = f1(root);
        }
        //Morris(root);
    }


    //后序  左右根
    TreeNode* prev = nullptr;//记录上一个遍历到的节点
    void flt(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        flt(root->right);
        flt(root->left);
        //先右 后左 
        // 每个节点都保证 prev就是自己的左孩子

    }
    TreeNode* f1(TreeNode* root) {
        if (root == nullptr) {
            return root;
        }
        //左孩子的右指针 指向自己  自己的右指针指向 右孩子的f1
        TreeNode* Left = f1(root->left);
        TreeNode* Right = f1(root->right);
        if (Left != nullptr) {
            Left->right = root;
        }
        root->right = Right;
        if (Left != nullptr) {
            Left->left = nullptr;
        }
        if(Right!=nullptr)
        {
            Right->left = nullptr;
        }
        return Left != nullptr ? Left : root;
    }

    //非递归
    //// 当前子树为head 执行flatten 当前树变为棒状
    //// 怎么感觉是非递归的思路
    //TreeNode* f(TreeNode* root) {
    //    if (root->left == nullptr) {
    //        //没有左树了
    //    }
    //    TreeNode* cur = root;
    //    TreeNode* Right = root->right;
    //    TreeNode* Left = f(root);//执行flatten 
    //    //如果还存在右树的话 还得右树flattn 然后再连接


    //}


};