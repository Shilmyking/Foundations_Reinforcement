
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
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        if (headA == nullptr || headB == nullptr) { return nullptr; }

        int sizeA = 0, sizeB = 0;
        ListNode* cur = headA;
        while (cur != nullptr) {
            cur = cur->next, ++sizeA;
        }
        cur = headB;
        while (cur != nullptr) {
            cur = cur->next, ++sizeB;
        }
        //看谁更大  然后先走大的那一部分
        ListNode* bigSizeHead = sizeA > sizeB ? headA : headB;
        ListNode* smallSizeHead = bigSizeHead == headA ? headB : headA;
        for (int i = 0; i < std::abs(sizeA - sizeB); i++) {
            bigSizeHead = bigSizeHead->next;
        }

        while (bigSizeHead!=nullptr&&bigSizeHead != smallSizeHead) {
            bigSizeHead = bigSizeHead->next;
            smallSizeHead = smallSizeHead->next;
        }

        //nullptr or 相交节点
        return bigSizeHead;

    }
};