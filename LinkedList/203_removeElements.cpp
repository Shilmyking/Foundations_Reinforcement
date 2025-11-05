


struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        if (head == nullptr)return head;
        ListNode* dummy = new ListNode(-1, head);
        ListNode* cur = head;
        ListNode* pre = dummy;
        ListNode* nexts = cur->next;
        while (cur != nullptr) {
            if (cur->val == val) {
                pre->next = nexts;
            }//跨过cur节点  这个时候pre无需更新
            else{
                pre = cur;
            }//
            cur = nexts;
            if (nexts != nullptr){
                nexts = nexts->next;
            }
        }
        return dummy->next;
    }
};