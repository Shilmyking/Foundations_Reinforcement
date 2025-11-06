

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

    ListNode* partition(ListNode* head, int x) {
        if (head == nullptr || head->next == nullptr) { return head; }
        //是否需要考虑 head->val 定最开始的head

        //ListNode* smallHead = head->val < x ? head : nullptr; ListNode* smallTail = smallHead;
        //ListNode* bigerHead = smallHead == nullptr ? head : nullptr; ListNode* bigerTail = bigerHead;
        ListNode* smallHead = nullptr; ListNode* smallTail = nullptr;
        ListNode* bigerHead = nullptr; ListNode* bigerTail = nullptr;
        ListNode* cur = head;
        while (cur != nullptr) {
            if (cur->val < x) {
                //如果head是nullptr
                if (smallHead == nullptr) {
                    smallHead = cur;
                    smallTail = smallHead;
                }
                else {//有head  尾巴接上去
                    smallTail->next = cur;
                    smallTail = smallTail->next;
                }
            }
            else {//大于等于放在bigerHead这一条链上
                if (bigerHead == nullptr) {
                    bigerHead = cur;
                    bigerTail = bigerHead;
                }
                else {
                    bigerTail->next = cur;
                    bigerTail = bigerTail->next;
                }
            }
            cur = cur->next;
        }
        //接好剩下的两条链

        //最后还有可能  Tail都指向链表内的其他元素 所以置nullptr
        // 可能smallTail和bigerTail存在是nullptr
        if (smallHead == nullptr) {
            return bigerHead;
        }
        smallTail->next = bigerHead;
        if (bigerTail != nullptr) {
            bigerTail->next = nullptr;
        }
        return smallHead;
    }
};