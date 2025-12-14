
#include<iostream>
using namespace std;

struct Node {
	int data;
	Node* pre;
	Node* next;
	Node(int data=-1,Node*pre=nullptr,Node*next):data(data),pre(pre),next(next){}
};

class doubleLinkedList {
private:
	Node* head;//头节点
public:
	doubleLinkedList() {
		head = new Node();
	}

	~doubleLinkedList() {
		Node* cur = head;
		while (cur != nullptr) {
			head = head->next;
			delete cur;
			cur = head->next;
		}
	}

	void insertHead(int val) {
		Node* newNode = new Node(val);
		newNode->next = head->next;
		newNode->pre = head;
		if (newNode->next != nullptr){
			newNode->next->pre = newNode;
		}
		head->next = newNode;
	}
	
	void insertTail(int val) {
		Node* newNode = new Node(val);
		Node* cur = head;
		while(cur->next!=nullptr){
			cur = cur->next;
		}
		cur->next = newNode;
		newNode->pre = cur;
	}
	
	void Remove(int val) {
		Node* cur = head->next;
		while (cur != nullptr) {
			if (cur->data == val) {
				// 前一个节点
				Node* pre = cur->pre;
				pre->next = cur->next;
				if (cur->next != nullptr) {
					cur->next->pre = pre;
				}
				delete cur;
				return;
			}
			cur = cur->next;
		}
	}
	bool find(int val) {
		Node* cur = head->next;
		while (cur != nullptr) {
			if (cur->data == val) {
				return true;
			}
			cur = cur->next;
		}
		return false;
	}
};