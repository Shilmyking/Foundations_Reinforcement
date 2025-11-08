

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

/*
给定一个已排序的链表的头 head ， 删除所有重复的元素，使每个元素只出现一次 。返回 已排序的链表 。
*/
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr || head->next == nullptr) { return head; }
        ListNode* cur = head;
        ListNode* nexts = head->next;
        //这这样的写法你最后没办法去除哪些再重复的值...  
        while (nexts != nullptr) {
            if (cur->val == nexts->val) {//等值跳过
                //释放内存 不影响整体逻辑
                    nexts = nexts->next;
            }
            else {
                cur->next = nexts;
                cur = nexts;
            }
        }
        //最后还存在一些重复的值(没有做释放内存的话) 你直接丢掉就行
        cur->next = nullptr;
        return head;
    }
    //当然可以写一个 free内存的版本   or  不要nexts变量  cur->next表示就行
    ListNode* deleteDuplicates_1(ListNode* head) {
        if (head == nullptr || head->next == nullptr) { return head; }

        ListNode* cur = head;
        while (cur != nullptr && cur->next != nullptr) {
            if (cur->val == cur->next->val) {
                ListNode* tmp = cur->next;     
                cur->next = cur->next->next;

                tmp->next = nullptr; 
                delete tmp;              
                //无需移动cur 因为可能存在多个重复项  一直把重复的释放
            }
            else {
                //不等就移动
                cur = cur->next; 
            }
        }

        return head;
    }
};