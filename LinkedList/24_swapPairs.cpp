

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
    //bool operator<(const ListNode* node)const {
    //    return this->val < node->val;
    //}//本地可以这样写  然后比较ListNode*  不对不对是比较了地址值的大小
};
/*
给你一个链表，两两交换其中相邻的节点，并返回交换后链表的头节点。
*/

class Solution {
public:

    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr || head->next == nullptr) { return head; }
        ListNode* pre = nullptr;
        ListNode* cur = head;
        ListNode* next = head->next;
        //两个节点就翻转一次
        //head 需要改变  特殊处理
        ListNode* nextNext = next->next;
        next->next = cur;
        cur->next = nextNext;
        head = next;
        //Swap后续的内容
        pre = cur;
        cur = nextNext;
        //需要注意后面可能没有了  也就是只有两个节点的情况
        next = cur != nullptr ? cur->next : nullptr;
        while (cur != nullptr && next != nullptr) {
            nextNext = next->next;
            //三条指针改向
            pre->next = next;
            next->next = cur;
            cur->next = nextNext;
            //继续下一组
            pre = cur;
            cur = nextNext;
            next = cur != nullptr ? cur->next : nullptr;
        }
        return head;
    }

};