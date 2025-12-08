

#if 0

//特殊点尾 p->next==head 指向头结点
#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;

struct Node {
	Node(int data = 0) :data(data), next(nullptr) {}
	int data;
	Node* next;
};

class CircleLink {

	Node* head;//指向头结点
	Node* tail;//指向尾节点
	int size;
public:
	CircleLink(int size = 0) :size(size) {
		head = new Node();
		tail = head;
		//最初 为自己指向直接自己的环
		head->next = head;
	}
	//~CircleLink() {
	//	/*Node* p = head;
	//	while (p != nullptr) {
	//		head = head->next;
	//		delete p;
	//		p = head;
	//	}*/
	//	Node* p = head->next;
	//	while (p != head) {
	//		head->next = p->next;
	//		delete p;
	//		p = head->next;
	//	}
	//	delete head;
	//}
	//最初head 和tail 均指向头结点
	//尾插法
	void InsertTail(int val) {
		Node* node = new Node(val);
		node->next = head;//node->next->tail->next;
		tail->next = node;
		tail = node;//更新tail 指向尾结点
		size++;
	}
	//头插法
	void InsertHead(int val) {
		Node* node = new Node(val);
		node->next = head->next;
		head->next = node;
		//空链表下增加 需要将tail指向新加入的结点
		if (node->next == head) {
			tail = node;
		}
		size++;
	}
	void Remove(int val) {
		Node* q = head;
		Node* p = head->next;
		while (p != head) {
			if (p->data == val) {
				q->next = p->next;
				delete p;
				//维护
				//若删除尾结点，则q->next指向head
				if (q->next == head) {
					tail = q;
				}
				return;
			}
			else {
				p = p->next;
				q = q->next;
			}
		}
		size--;
	}
	//是否存在某个数
	bool Find(int val) const {
		Node* p = head->next;
		while (p != head) {
			if (p->data == val) {
				return true;
			}
		}
		return false;
	}
	void show()const {
		Node* p = head->next;
		while (p != head) {
			if (p->next != head)
				cout << p->data << " ";
			else
				cout << p->data << endl;
			p = p->next;
		}
	}
};
////约瑟夫环问题
////n个人围在圆桌编号为k的人开始报数数到m的人出列，然后下一个人从一开始
////数到m的出列，重复直到全部人出列输出人出列的顺序(编号)
////不带头结点单项循环链表输出
//	void Joseph(int k, int m) {//size 为n
//		Node* p = head->next;
//		Node* q = head;
//		for (int i = 0; i < k; i++) {
//			p = p->next;
//			q = q->next;
//		}
//		for (;;) {
//			for (int i = 0; i < m; i++) {
//				p = p->next;
//				q = q->next;
//			}
//			if (p == q) {
//				break;
//			}
//			cout << p->data << " ";
//			if (p == q) {
//				break;
//			}
//			q->next = p->next;
//			delete p;
//			p = q->next;
//			
//		}
//	}
//};
//int main() {
//	CircleLink clink;
//	srand(time(nullptr));
//	for (int i = 0; i < 10; i++) {
//		int val = rand() % 100;
//		clink.InsertHead(val);
//		cout << val << " ";
//	}
//	cout << endl;
//	clink.show();	
//	clink.Joseph( 1, 3);
//}
//

void Joseph(Node* head, int k, int m) {
	Node* p = head;
	Node* q = head;
	while (q->next != head) {//不带头结点则让q指向末尾结点
		q = q->next;
	}
	//从第k个人开始报数
	for (int i = 1; i < k; i++)//无头结点从头Ⅰ开始
	{
		q = p;
		p = p->next;
	}
	for (;;) {
		for (int i = 1; i < m; i++) {
			q = p;
			p = p->next;
		}
		//删除p指向的结点
		//q p node
		cout << p->data << " ";
		if (p == q) {
			delete p;
			break;
		}
		q->next = p->next;
		delete p;
		p = q->next;
	}
	return;
}
int main() {
	Node* head = new Node(1);
	Node* n2 = new Node(2);
	Node* n3 = new Node(3);
	Node* n4 = new Node(4);
	Node* n5 = new Node(5);
	Node* n6 = new Node(6);
	Node* n7 = new Node(7);
	Node* n8 = new Node(8);
	head->next = n2;
	n3->next = n4;
	n4->next = n5;
	n5->next = n6;
	n6->next = n7;
	n7->next = n8;
	n8->next = head;
	Joseph(head, 1, 3);
}
#endif
