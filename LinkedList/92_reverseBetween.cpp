

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


class Solution {
private:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) { return head; }
        ListNode* cur = head;
        ListNode* next = head->next;
        ListNode* pre = nullptr;
        while (next != nullptr) {
            cur->next = pre;//转头

            pre = cur;//pre紧跟当前node ，因为当前node将变成下一个pre

            cur = next;//到下一个

            next = next->next;
        }
        cur->next = pre;
        return cur;
    }
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (left == right) { return head; }

        ListNode* dummy = new ListNode(0, head);

        ListNode* startPre = dummy;
        for (int i = 0; i < left - 1; ++i) {
            startPre = startPre->next;
        }
        ListNode* reverseStartNode = startPre->next;

        ListNode* tail = reverseStartNode;
        for (int i = 0; i < right - left;++i) {
            tail = tail->next;
        }
        ListNode* tailNext = tail->next;
        //tail 和 tailNext间需要断开  
        tail->next = nullptr;

        //reverseStartNode 到 tail这个范围reverse
        ListNode*newSubHead = reverseList(reverseStartNode);

        //tail变为这段的head  reverStartNode变为结尾
        startPre->next = newSubHead;//startPre不可能为nullptr  所以无需讨论
        reverseStartNode->next = tailNext;
        return dummy->next;//存在换头的可能
    }


    ListNode* reverseBetween_1(ListNode* head, int left, int right) {
        if (left == right || head == nullptr || head->next == nullptr) { return head; }

        ListNode* startPre = nullptr;
        ListNode* reverseStartNode = head;

        for (int i = 0; i < left - 1; i++) {
            startPre = reverseStartNode;
            reverseStartNode = reverseStartNode->next;
        }

        ListNode* tail = reverseStartNode; //继续去找
        for (int i = 0; i < right - left; i++) {
            tail = tail->next;
        }
        ListNode* tailNext = tail->next;
        //tail 和 tailNext间需要断开  startPre和StartNode也是
        //startPre->next = nullptr;
        tail->next = nullptr;

        //reverseStartNode 到 tail这个范围reverse
        ListNode* newSubHead = reverseList(reverseStartNode);
        //tail变为这段的head  reverStartNode变为结尾
        //接回去
        reverseStartNode->next = tailNext;

        //就是需要注意一下这里面的一个小细节
        if (startPre == nullptr) {
            return newSubHead;
        }
        startPre->next = newSubHead;
        return head;
    }

};
