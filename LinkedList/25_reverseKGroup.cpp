

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
    //翻转链表
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
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == nullptr || head->next == nullptr) { return head; }
        ListNode* dummy = new ListNode(-1, head);

        ListNode* startPreNode = dummy;
        ListNode* startNode = head;

        while (startNode != nullptr) {
            ListNode* endNode = startPreNode;
            //check 是否还需要翻转
            for (int i = 0; i < k; i++) {
                endNode = endNode->next;
                if (endNode == nullptr) {
                    return dummy->next;
                }
            }//出循环说明就是需要翻转
            ListNode* endNextNode = endNode->next;
            endNode->next = nullptr;//需要断链

            reverseList(startNode);

            //翻转之后 endNode变为 NewSubNode  startNode变为末尾的Node
            startPreNode->next = endNode;//前面部分
            startNode->next = endNextNode;//翻转之后的末尾节点接上 上一次反转之前节点的

            startPreNode = startNode;//下一次翻转的节点的前一个节点
            startNode = endNextNode;//下一次翻转的新head
        }
        return dummy->next;
    }
};