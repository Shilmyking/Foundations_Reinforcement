#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
#include<stdlib.h>

using namespace std;

struct Node {
	int val;
	Node* next;
	Node(int v = -1, Node* n = nullptr):val(v),next(n){}
};

class circleLinkedList {
private:
	//循环链表实现
	Node* front;
	Node* rear;
public:
	circleLinkedList() :front(nullptr), rear(nullptr) {

	}

	bool isEmpty() {
		return front == rear;
	}

	bool isFull() {//
		//为 nullptr ---> front == rear 啥也没有
		// 否则就是...
		return (rear == nullptr) || (rear->next == front);
	}

	void insertHead(int val) {

	}

	void insertTail(int val) {

	}

	void removeHead(int val) {

	}

	void removeTail(int val) {

	}
};