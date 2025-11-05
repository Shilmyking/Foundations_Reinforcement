

#include<string>
#include<vector>
#include<algorithm>
using namespace std;

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
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) { return head; }
        ListNode* cur = head;
        ListNode*next = head->next;
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
};