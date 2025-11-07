
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};
 
#include<string>
using namespace std;

class Solution {
public:
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

    //递归：给到两个有序链表  返回将两个链表合并后的结果
    //
    ListNode* mergeTwoLists1(ListNode* list1, ListNode* list2) {
        if (list1 == nullptr)return list2;
        if (list2 == nullptr) return list1;
        //从小到大 依次串好
        if (list1->val < list2->val) {
            //递归
            list1->next = mergeTwoLists1(list1->next, list2);

            //回溯到当前调用递归的位置   返回ans
            return list1;
        }

        list2->next = mergeTwoLists1(list1, list2->next);
        return list2;
    }

};