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

// k最大为1e4(1W) 
// 每个链表长度不超过500
//所有链表节点总和不超过 1e4
class Solution {

    //暴力
    ListNode* f1(const vector<ListNode*>& lists) {
        int n = lists.size();
        if (n == 0)return nullptr;
        ListNode* cur = lists[0];
        //ListNode* head = cur;
        for (int i = 1; i < n; i++) {
            //返回的新head给到cur  因为存在换head的可能性
            cur = mergeTwoLists(cur, lists[i]);
        }
        return cur;
    }

    ListNode* f2(const vector<ListNode*>& lists, int left, int right) {
        if (left > right) {
            //这句甚至不用  不存在这种可能  
            // 递归调用的的隐含条件是left <= right left==right才会出现left > right
            // 当left == right 时直接return 不调用递归了
            return nullptr;
        }
        if (left == right) {
            return lists[left];
        }
        int mid = (left + right) / 2;
        ListNode* head;

        ListNode* leftNode = f2(lists, left, mid);
        ListNode* rightNode = f2(lists, mid + 1, right);

        return head = mergeTwoLists(leftNode, rightNode);

        //return mergeTwoLists(f2(lists, left, mid), f2(lists, mid + 1, right));
    }

    //非递归 + queue
private:
    static const int queSize = 1e5 + 5;
    //大小 设置为两倍 lists.size()多一点 足够了  二叉树最底层和上面所有节点间的关系可以推断出
    ListNode* que[queSize];
public:
    ListNode* f2_1(const vector<ListNode*>& lists) {
        if (lists.size() == 0)return nullptr;
        int left = 0, right = 0;
        for (ListNode* v : lists) {
            if (v != nullptr) {
                que[right++] = v;
            }
        }

        while (left < right) {
            ListNode* pre = que[left++];
            ListNode* cur = que[left++];
            que[right++] = mergeTwoLists(pre, cur);
        }
        //最后一个就是ans
        return right != 0 ? que[right - 1] : nullptr;
    }
public:
    ListNode* f2_2(vector<ListNode*>& lists) {
        int n = lists.size();
        if (n == 0) { return nullptr; }

        //step 步长
        for (int step = 1; step < n; step <<= 1) {
            int i = 0;
            while (i + step < n) {
                // i 位置 和 i+step 位置 merge
                lists[i] = mergeTwoLists(lists[i], lists[i + step]);
                i += (step << 1);
            }
        }
        return lists[0];
    }

public:
    ListNode* f3(const vector<ListNode*>& lists) {
        if (lists.size() == 0) { return nullptr; }
        build();
        int n = lists.size();
        for (ListNode* v : lists) {
            if (v != nullptr) {
                push(v);
            }
        }
        if (isEmpty()) {//存在 lists就是 []的情况
            return nullptr;
        }
        ListNode* head = pop();//拿堆顶
        //只要pop了 就需要 把堆顶的下一个元素放进小根堆
        ListNode* pre = head;
        if (pre != nullptr && pre->next != nullptr) {
            push(pre->next);
        }
        ListNode* cur;
        while (!isEmpty()) {
            cur = pop();
            pre->next = cur;
            pre = pre->next;//去下一个位置继续串
            if (cur->next != nullptr) {
                push(cur->next);
            }
        }
        return head;
    }

private:
    // k最大为1e4(1W) 
    // 每个链表长度不超过500
    //所有链表节点总和不超过 1e4
    static const int MAXN = 1e4 + 5;
    ListNode* heap[MAXN];
    int heapSize = 0;

    //需要维持一个小根堆
    void build() {
        heapSize = 0;
    }

    //上浮操作
    void heapInsert(int i) {
        //如果当前节点
        while (heap[i]->val < heap[(i - 1) / 2]->val) {
            std::swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    //下沉操作  小根堆
    void heapify(int i) {
        int left = 2 * i + 1;
        while (left < heapSize) {
            //找到孩子节点较小的 
            int smallLeaf = left + 1 < heapSize && heap[left + 1]->val < heap[left]->val ? left + 1 : left;
            smallLeaf = heap[smallLeaf]->val < heap[i]->val ? smallLeaf : i;
            if (smallLeaf == i) {
                break;
            }
            std::swap(heap[smallLeaf], heap[i]);
            i = smallLeaf;
            left = 2 * i + 1;
        }
    }
    // 如果push Or pop  一般是栈帧
    // Insert
    void push(ListNode* node) {
        //heapSize 指向要加入的位置
        heap[heapSize] = node;
        heapInsert(heapSize++);//维持小根堆
    }
    //
    ListNode* pop() {
        if (heapSize == 0) {
            return nullptr;
        }
        ListNode* ans = heap[0];
        //把堆底换上来
        std::swap(heap[0], heap[--heapSize]);
        heapify(0);
        return ans;
    }

    bool isEmpty() {
        return heapSize == 0;
    }

private:
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
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        //return f1(lists);
        //return f2(lists, 0, lists.size() - 1);
        //return f3(lists);
        //return f2_1(lists);
        return f2_2(lists);
    }
};