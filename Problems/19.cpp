#include<random>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

random_device rd;
mt19937 rng(rd());

typedef struct node
{
    int data;
    struct node* next;
} NODE;

// 设线性表 $L=(a_1,a_2,a_3,\cdots,a_{n-2},a_{n-1},a_n)$ 采用带头结点的单链表保存，链表中的结点定义如下：
//请设计一个空间复杂度为 $O(1)$ 且时间上尽可能高效的算法，重新排列 $L$ 中的各结点，得到线性表 $L'=(a_1,a_n,a_2,a_{n-1},a_3,a_{n-2},\cdots)$

//return mid node
NODE* findMidNode(NODE* head) {
    NODE* slow = head;
    NODE* fast = head;
    while (fast->next != nullptr && fast->next->next != nullptr) {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

//返回reverse之后的head
NODE* Reverse(NODE* head) {
    NODE* pre = nullptr;
    NODE* cur = head;
    NODE* nexts=nullptr;
    while (cur != nullptr) {
        nexts = cur->next;
        cur->next = pre;
        pre = cur;
        cur = nexts;
    }
    return pre;
}

NODE* f(NODE* head) {
    NODE* midNode = findMidNode(head);
    NODE* midNodeNext = midNode->next;
    //断尾
    midNode->next = nullptr;
    NODE* secondPart = Reverse(midNodeNext);

    //固定head
    NODE* cur1 = head;
    NODE* cur2 = secondPart;
    
    NODE* nexts1 = cur1->next;
    NODE* nexts2 = cur2->next;
    //穿针引线
    while (cur1 != nullptr && cur2 != nullptr) {
        //当cur1&&cur2不为nullptr的时候   获取下一个节点
        nexts1 = cur1->next;
        nexts2 = cur2->next;
        //串
        cur1->next = cur2;
        cur2->next = nexts1;
        //去下一轮
        cur1 = nexts1;
        cur2 = nexts2;
    }
    return head;
}