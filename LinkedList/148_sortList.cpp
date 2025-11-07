
//https://leetcode.cn/problems/sort-list/description/

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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (list1 == nullptr)return list2;
        if (list2 == nullptr) return list1;

        //ListNode* head = list1->val < list2->val ? list1 : list2;
        ListNode* head;
        if (list1->val > list2->val) {
            head = list2;
            list2 = list2->next;
        }
        else {
            head = list1;
            list1 = list1->next;
        }
        ListNode* cur = head;//留下head
        ListNode* nexts = cur;

        while (list1 != nullptr && list2 != nullptr) {

            if (list1->val > list2->val) {
                nexts->next = list2;
                list2 = list2->next;
            }
            else {
                nexts->next = list1;
                list1 = list1->next;
            }
            cur = nexts->next;
            nexts = cur;
        }
        if (list1 != nullptr) {
            nexts->next = list1;
        }
        if (list2 != nullptr) {
            nexts->next = list2;
        }
        return head;
    }

    ListNode* findMidNode(ListNode* list) {
        if (list == nullptr||list->next==nullptr)return list;
        ListNode* slow = list;
        ListNode* fast = list;

        while (fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        //精准的返回中间的节点 
        return slow;//无论奇偶都是
    }

public:


    //需要 nlogn的时间复杂度
    //归并排序  快排
    ListNode* sortList(ListNode* head) {
        // nullptr or 一个节点
        if (head == nullptr||head->next==nullptr)return head;
        ListNode* midNode = findMidNode(head);
        ListNode* rightBeginNode = midNode->next;
        midNode->next = nullptr;

        //调用递归  排序两侧的链表
        ListNode* left = sortList(head);
        ListNode* right = sortList(rightBeginNode);

        return mergeTwoLists(left, right);
    }
};