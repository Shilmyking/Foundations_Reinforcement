

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

//给你一个链表的头节点 head ，旋转链表，将链表每个节点向右移动 k 个位置。
class Solution {
public:
    //这题看一下数据 发现 k可能非常大  1e9 需要同余原理
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == nullptr || head->next == nullptr) { return head; }
        int Size = 1;
        ListNode* cur = head;
        while (cur->next != nullptr) {//判断next不为nullptr Size初始为1
            cur = cur->next, Size++;
        }//出来得到尾节点
        ListNode* Tail = cur;
        k %= Size;//转移到 0-Size 内
        if (k == 0) { return head; }//无需翻转

        //其实就是把后K个节点 搬到前面部分 指针改向就行
        //所以先走 Size -k
        ListNode* pre = nullptr;
        cur = head;
        for (int i = 0; i < Size - k; i++) {
            pre = cur;
            cur = cur->next;
        }
        //pre就是新的Tail 需要断链
        //cur就是开始要翻转的地方
        pre->next = nullptr;
        Tail->next = head;
        return head = cur;
    }
};