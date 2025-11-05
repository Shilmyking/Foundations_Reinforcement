
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
public:
    
    ListNode* detectCycle(ListNode* head) {
        if (head == nullptr || head->next == nullptr)return nullptr;
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {//第一次相遇
                //break;
                ListNode* cur = head;
                //int cnt = 0;
                while (cur != slow) {
                    //++cnt;
                    cur = cur->next;
                    slow = slow->next;
                }
                return cur;
            }
        }
        return nullptr;
    }
};