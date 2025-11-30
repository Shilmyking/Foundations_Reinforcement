


#include<algorithm>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}

};
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
    //传回中点 + 中点前一个节点 pre 必须使用引用 否则局部变量改不了
    ListNode* midNode(ListNode* head,ListNode* &pre) {
        ListNode* cur = head;
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            pre = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    //将 单链表head 调整为一颗BSTree
    TreeNode* f(ListNode* head) {
        if (head == nullptr) {
            return nullptr;
        }
        // 应该是要给个地址 保存 不能直接nullptr
        ListNode* pre = new ListNode(-INF);
        ListNode* mid = midNode(head, pre);
        // 一个节点的时候 pre才返回nullptr
        TreeNode* root = new TreeNode(mid->val);
        if (pre->val != -INF) {
            pre->next = nullptr;
            ListNode* Right = mid->next;
            root->left = f(head);
            root->right = f(Right);
        }
        return root;
    }

    //找中点 + 递归
    // 更好的方案是  先遍历一遍知道链表长度
    // 然后 拿到 left right 进行递归 
    // 无需每次都总是遍历  给出的链表其实就是 BSTree中序遍历的结果了
    // 我们反着...
    /*
        int mid = (left + right + 1) / 2;
        TreeNode* root = new TreeNode();
        root->left = buildTree(head, left, mid - 1);
        root->val = head->val;
        head = head->next;
        root->right = buildTree(head, mid + 1, right);
    */

    int getLength(ListNode* head) {
        int cnt = 0;
        ListNode* cur = head;
        while (cur != nullptr) {
            cur = cur->next, cnt++;
        }
        return cnt;
    }

    //也必须是引用
    TreeNode* f2(ListNode*& head, int left, int right) {
        if (left > right||head==nullptr) {
            return nullptr;
        }
        int mid = (left + right+1) / 2;
        TreeNode* root = new TreeNode();
        root->left = f2(head, left, mid - 1);

        //当前head 来到的位置就是mid
        root->val = head->val;
        head = head->next;//指针移动

        root->right = f2(head, mid + 1, right);
        return root;
    }

    TreeNode* sortedListToBST(ListNode* head) {
       // return f(head);
        return f2(head, 0, getLength(head) - 1);
    }
};