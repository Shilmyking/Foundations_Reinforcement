

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};
#if 0
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
#endif
//不要使用 dummy

class Solution {
private:
    // start--->  a-->b -->c -->d -->end -->endNext
    // end---> d -->c --->b --->a --->start --> endNext
    void reverse(ListNode* start, ListNode* end) {
        ListNode* pre = nullptr;
        ListNode* cur = start;
        ListNode* next = cur->next;

        end = end->next;// end变为边界  等效于那个nullptr
        while (cur != end) {
            next = cur->next;
            cur->next = pre;

            pre = cur;

            cur = next;
        }
        //调整完之后 传参进来的end的节点的指向之前他原本的pre 
        // start变为末尾节点  指向 end节点
        start->next = end;
    }
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == nullptr||head->next==nullptr) { return head; }
        ListNode* start = head;
        ListNode* end = findEnd(head, k);
        if (end == nullptr) {
            return head;
        }
        head = end;//真正的head
        reverse(start, end);
        ListNode* lastTeamEnd = start;//你是end 需要拿来接下一组的start
        //这里start已经再reverse函数接上 原本end的下一个节点了
        while (lastTeamEnd->next != nullptr) {
            start = lastTeamEnd->next;//下一组的start
            end = findEnd(start, k);
            if (end == nullptr) {//不够k个 无需继续翻转了
                return head;
            }
            reverse(start, end);
            lastTeamEnd->next = end;
            lastTeamEnd = start;
        }
        return head;
    }

    //包括当前节点head在内，往后找k个节点  可能返回nullptr  代表不够 那就不用翻转了
    ListNode* findEnd(ListNode*head,int k) {
        while (--k != 0 && head != nullptr) {
            head = head->next;
        }
        return head;
    }
};