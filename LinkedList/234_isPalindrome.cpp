

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

    //reverse  &&  return newHead;
    ListNode* reverseLinkedList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) { return head; }
        ListNode* pre = nullptr;
        ListNode* cur = head;
        ListNode* nexts = head->next;
        while (cur != nullptr) {
            cur->next = pre;
            pre = cur;
            cur = nexts;
            if (nexts != nullptr) {
                nexts = nexts->next;
            }
        }
        return pre;
    }
    ListNode* findMidNode(ListNode* head) {
        if (head == nullptr || head->next == nullptr) { return head; }
        ListNode* slow = head;
        ListNode* fast = head;
        //ListNode* pre;
        while (fast->next != nullptr && fast->next->next != nullptr) {
            
            //pre = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        //return fast->next == nullptr ? pre : slow;
        //没用 就是需要一个信息要知道 是奇数节点个数  还是偶数节点
        return slow;//返回中点
    }
public:
    //需要找到中点
    //反转链表
    //然后一一比对
    bool isPalindrome(ListNode* head) {
        if (head == nullptr || head->next == nullptr) { return true; }
        if (head->next != nullptr&&head->next->next==nullptr) { return head->val == head->next->val; }

        ListNode* midNode = findMidNode(head);
        ListNode* startReverseNode = midNode->next;
        //断链
        midNode->next = nullptr;
        ListNode* newHead = reverseLinkedList(startReverseNode);
        ListNode* cur1 = head;
        ListNode* cur2 = newHead;

        bool ans = true;
        while (cur1 != nullptr&&cur2!=nullptr) {
            if (cur1->val != cur2->val) {
                ans = false;
                break;
            }
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
        //还原链表
        newHead = reverseLinkedList(newHead);
        midNode->next = newHead;
        return ans;
    }
};