
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
    //删除倒数第n个节点
    //需要找到倒数第n个节点的前一个节点
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (head == nullptr || head->next == nullptr && n == 1) {
            return nullptr;
        }
        ListNode* dummy = new ListNode(-1, head);

        ListNode* fast = dummy;
        for (int i = 0; i < n; i++) {
            fast = fast->next;
        }
        ListNode* slow = dummy;
        while (fast->next != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }
        //slow 到达要删除的节点的前一个
        ListNode* nexts = slow->next;
        slow->next = nexts->next;
        nexts->next = nullptr;
        delete nexts;
        //存在删除的节点就是head的可能性
        // 节点为 1 2   删除倒数第2个
        return dummy->next;
    }
};