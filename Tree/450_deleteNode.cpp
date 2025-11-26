

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


class Solution {
public:
    // 以head为头的
    TreeNode* Delete(TreeNode* head, int key) {
        TreeNode* cur = head;
        TreeNode* last = head;
        int soni = 0;//0代表左孩子  1代表右孩子

        while (cur != nullptr) {
            if (cur->val == key) {//找到了
                break;
            }
            //还得往下找
            last = cur;
            if (cur->val > key) {
                cur = cur->left;
                soni = 0;
            }
            else if (cur->val < key) {
                cur = cur->right;
                soni = 1;
            }

        }//出循环 两种情况  找到key /nullptr

        TreeNode* target = nullptr;
        if (cur != nullptr) {
            //last保存好了这个cur的父节点
            //真的要去删除这个节点   
            //如果 孩子不是双全 返回那个不为空的即可 或者都是nullptr
            if (!(cur->left != nullptr && cur->right != nullptr)) {
                target = cur->left == nullptr ? cur->right : cur->left;
            }
            else {
                // 保存后继节点的父亲
                TreeNode* mostLeftLast = cur;
                //孩子双全  找后继
                TreeNode* mostLeft = cur->right;//肯定不为空
                while (mostLeft->left != nullptr) {
                    mostLeftLast = mostLeft;
                    mostLeft = mostLeft->left;
                }
                target = mostLeft;
                //右孩子就是后继节点
                if (cur == mostLeftLast) {
                    // 左孩子给后继接管
                    mostLeft->left = cur->left;
                }
                else {
                    // mostLeftLast 接管 mostLeft的右孩子
                    mostLeftLast->left = mostLeft->right;
                    //mostLeft 代替 cur
                    mostLeft->left = cur->left;
                    mostLeft->right = cur->right;
                }
            }// 设置好target(接替的节点) 和 各种情况需要改向的指针

            if (cur == head) {//一定需要考虑是否换head
                head = target;
            }
            else {
                if (soni == 0) {
                    last->left = target;
                }
                else {
                    last->right = target;
                }
            }
            delete cur;
        }
        return head;
    }

    TreeNode* deleteNode(TreeNode* root, int key) {
        return Delete(root, key);
    }
};