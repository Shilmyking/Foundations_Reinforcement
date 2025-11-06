


// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};


class Solution {
public:
    //三步走：
    //  先生成复制节点 
    //  然后设置好random指针  
    // random指针设置为 cur->random->next(cur->random指向的就是要复制的节点的上一个)
    // 原链表和新生成的节点分离 
    Node* copyRandomList(Node* head) {
        if (head == nullptr) { return head; }
        Node* cur = head;
        Node* next = cur->next;
        //创建新节点
        while (cur != nullptr) {
            Node* node = new Node(cur->val);
            cur->next = node;
            node->next = next;
            cur = next;

            next = cur != nullptr ? cur->next : nullptr;
        }
        //设置random节点
        cur = head;
        while (cur != nullptr) {
            next = cur->next;
            next->random = cur->random != nullptr ? cur->random->next : nullptr;
            cur = next;
        }
        //分离 cur 和 nexts
        cur = head;
        Node* copyHead = cur->next;
        while (cur != nullptr) {
            next = cur->next;
            cur->next = next->next;
            
            next->next = cur->next;
        }
        return copyHead;
    }
};