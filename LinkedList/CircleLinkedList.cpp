#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
#include<stdlib.h>

using namespace std;

struct Node {
	int data;
	Node* next;
	Node(int v = -1, Node* n = nullptr):data(v),next(n){}
};


// 约瑟夫环问题 - 不带头结点的单项循环链表应用
void Joseph(Node* head, int k, int m)
{
	Node* p = head;
	Node* q = head;

	// q指向最后一个
	while (q->next != head)
	{
		q = q->next;
	}

	// 从第k个人开始报数的
	for (int i = 1; i < k; i++)
	{
		q = p;
		p = p->next;
	}

	// p -> 第k个人
	for (;;)
	{
		for (int i = 1; i < m; i++)
		{
			q = p;
			p = p->next;
		}

		// 删除p指向的结点
		// q p node
		cout << p->data << " ";

		if (p == q)
		{
			delete p;
			break;
		}

		q->next = p->next;
		delete p;
		p = q->next;
	}
}


class circleLinkedList {
private:
	//循环链表实现
	Node* head;
	Node* tail;
public:
	circleLinkedList() {
		head = new Node();
		tail = head;
		head->next = head;
		//一个头节点 自己指向自己
	}

	~circleLinkedList() {
		//整个类析构
		Node* cur = head->next;
		while (cur != nullptr) {
			head->next = cur->next;
			delete cur;
			cur = head->next;
		}
		delete head;
	}

	bool isEmpty() {
		//都指向head节点
		return head == tail;
	}

	void insertHead(int val) {
		Node* newNode = new Node(val);
		newNode->next = head->next;
		head->next = newNode;
		// 初始化的时候 只存在一个头节点 head  
		// 做完上述之后 newNode->next = head --->需要移动尾指针
		if (newNode->next == head) {
			tail = newNode;
		}
	}

	void insertTail(int val) {
		Node* newNode = new Node(val);
		newNode->next = tail->next;
		// 倒数第二个节点指向倒数第一个节点
		tail->next = newNode;
		tail = newNode;

	}

	void Remove(int val) {
		Node* pre = head;
		Node* cur = head->next;
		if (cur == nullptr) {
			return;
		}
		while (cur != head) {
			if (cur->data == val) {
				//删除 cur节点
				pre->next = cur->next;
				delete cur;
				//如果 删除的是尾节点 把tail设置为pre
				if (pre->next == head) {
					tail = pre;
				}
				return;
			}
			pre = cur;
			cur = cur->next;
		}
	}

	bool find(int val)const {
		Node* cur = head->next;//带头结点查询
		//没有回到head
		while (cur != head) {
			if (cur->data==val) {
				return true;
			}
		}
		return false;
	}
	void show() {
		Node* cur = head->next;
		while (cur != head) {
			cout << cur->data << " ";
			cur = cur->next;
		}
	}
};