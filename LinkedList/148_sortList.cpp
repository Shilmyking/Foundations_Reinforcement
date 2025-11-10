
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
        if (list == nullptr || list->next == nullptr)return list;
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
        if (head == nullptr || head->next == nullptr)return head;
        ListNode* midNode = findMidNode(head);
        ListNode* rightBeginNode = midNode->next;
        midNode->next = nullptr;

        //调用递归  排序两侧的链表
        ListNode* left = sortList(head);
        ListNode* right = sortList(rightBeginNode);

        return mergeTwoLists(left, right);
    }
};

class Solution {
public:

    ListNode* sortList(ListNode* head) {
        //必须要知道head的节点个数  因为写非递归 需要枚举step
        int  n = 0;
        ListNode* cur = head;
        while (cur != nullptr) {
            ++n, cur = cur->next;
        }
        // left1 right1 每组左侧部分
        // left2 right2  右侧部分
        // next 下一组的起始节点
        // lastTeamEnd  上一组的结尾
        ListNode* left1; ListNode* right1;
        ListNode* left2; ListNode* right2;
        ListNode* next; ListNode* lastTeamEnd;

        for (int step = 1; step < n; step <<= 1) {//step*=2
            //每一次枚举的step 第一次merge必须要特殊处理  -->确认新head
            //找好节点边界
            left1 = head;
            right1 = findEnd(left1, step);//找到末尾的节点

            //两个节点的时候也正常合并 代码没问题  这里就是无需再处理边界问题了
            left2 = right1->next;
            right2 = findEnd(left2, step);
            //准备合并
            next = right2->next;
            right1->next = nullptr;
            right2->next = nullptr;
            //start作为head end作为末尾
            mergeTwoLists(left1, right1, left2, right2);
            head = start;//存在换head的可能
            lastTeamEnd = end;
            //next已经捏住了 下一组的开头部分   主要思路就是和上面一样  只是head无需重新设置等等小细节
            while (next != nullptr) {
                left1 = next;
                right1 = findEnd(left1, step);

                left2 = right1->next;
                //left2为nullptr 说明上一组不满step个节点/恰好刚满   就是没有右部分的节点了
                //无需再merge  你不有序也没办法   没有人能和你merge  反正最后一定会轮到你的
                if (left2 == nullptr) {
                    lastTeamEnd->next = left1;
                    break;
                }
                //和上面完全一样
                right2 = findEnd(left2, step);
                next = right2->next;
                right1->next = nullptr;
                right2->next = nullptr;
                mergeTwoLists(left1, right1, left2, right2);
                lastTeamEnd->next = start;//上一组末尾 接上下一组的head
                lastTeamEnd = end;//然后调整到继续的下一组
            }
        }
        return head;
    }
private:
    ListNode* start;
    ListNode* end;
private:
    //将start设置为整体的head  end设置为合并好之后的Tail
    void mergeTwoLists(ListNode* left1, ListNode* right1, ListNode* left2, ListNode* right2) {
        ListNode* pre;
        if (left1->val <= left2->val) {
            pre = left1;
            start = left1;
            left1 = left1->next;
        }
        else {
            pre = left2;
            start = left2;
            left2 = left2->next;
        }
        while (left1 != nullptr && left2 != nullptr) {
            if (left1->val <= left2->val) {
                pre->next = left1;
                pre = left1;
                left1 = left1->next;
            }
            else {
                pre->next = left2;
                pre = left2;
                left2 = left2->next;
            }
        }
        if (left1 != nullptr) {
            pre->next = left1;
            end = right1;
        }
        else {
            pre->next = left2;
            end = right2;
        }
    }
    //step
    //包括s在内往后数K个节点 返回  如果不够返回最后一个非空节点
    ListNode* findEnd(ListNode* head, int k) {
        while (--k != 0 && head->next != nullptr) {
            head = head->next;
        }
        return head;
    }
};

