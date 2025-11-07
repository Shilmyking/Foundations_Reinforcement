#include<vector>
#include<iostream>
#include<queue>
#include<algorithm>
#include<cstring>
#include<list>
#include<vector>
#include<string>
#include<map>
#include<unordered_map>
#include<set>
#include<unordered_set>

using namespace std;
using namespace std;
#define int long long
#define endl "\n"

class LinkedList {
private:
	struct Node {
		int val;
		Node* next;
		Node(int val = 0, Node* n = nullptr) :
			val(val),
			next(n)
		{}
	};
public:
	LinkedList()
		:size(0) {
		head = nullptr;
	}

	~LinkedList() {
		Node* cur = head;
		Node* next;
		while (cur != nullptr) {
			next = cur->next;
			cur->next = nullptr;
			delete cur;
			cur = next;
		}
	}

	int getSize()const {
		return size;
	}

	bool isEmpty()const {
		return size == 0;
	}

	void insertHead(int val) {
		Node* node = new Node(val);
		node->next = head;
		head = node;//新head
		size++;
	}

	void insertTail(int val) {
		if (head == nullptr) {
			head = new Node(val);
		}
		else {
			Node* cur = head;
			//考虑 cur->next 不为nullptr 省去pre变量
			while (cur->next != nullptr) {
				cur = cur->next;
			}//cur = nullptr
			cur->next = new Node(val);
		}
		size++;
	}

	//0-based
	void insertAt(int index, int val) {
		if (index < 0 || size < index) {//index==size 就是尾插
			throw "insertAt : error index\n";
		}
		if (index == 0) {
			insertHead(val);
			return;
		}
		Node* cur = head;
		for (int i = 0; i < index - 1; i++) {
			cur = cur->next;
		}//到前一个节点
		//创建节点 + 转向
		Node* node = new Node(val);
		node->next = cur->next;
		cur->next = node;
		size++;

	}

	void removeHead() {
		if (size == 0) {
			throw "removeHead : LinkedList is empty";
		}
		Node* tmp = head;
		head = head->next;

		tmp->next = nullptr;
		delete tmp;
		size--;
	}

	void removeTail() {
		if (size == 0) {
			throw "removeTail : LinkedList is empty";
		}
		if (size == 1) {
			delete head;
			head = nullptr;
		}
		else {
			//两个节点及以上
			Node* cur = head;
			while (cur->next->next != nullptr) {
				cur = cur->next;
			}//出来之后 后面那一个就是要删除的
			Node* next = cur->next;
			delete next;
			cur->next = nullptr;
		}
		size--;
	}

	//0-base
	void removeAt(int index) {
		if (index < 0 || index >= size) {//index==size 也算越界  和nums一样
			throw "insertAt : error index\n";
		}
		if (index == 0) {
			removeHead();
		}
		else {
			Node* cur = head;
			for (int i = 0; i < index - 1; i++) {
				cur = cur->next;
			}//找到要删除的节点的上一个节点
			Node* tmp = cur->next;
			cur->next = cur->next->next;

			tmp->next = nullptr;
			delete tmp;
			size--;
		}
	}

	void removeFirstValue(int val) {
		if (size == 0) { return; }
		if (head->val == val) {
			removeHead();
			return;
		}
		Node* cur = head;//始终是检验下一个节点是不是要被删除
		while (cur->next != nullptr && cur->next->val != val) {
			cur = cur->next;
		}
		if (cur->next != nullptr) {
			//要删除一个
			Node* tmp = cur->next;
			cur->next = tmp->next;
			tmp->next = nullptr;
			delete tmp;
			size--;
		}

	}

	void removeAllValue(int val) {
		Node* cur = head;
		Node* pre = nullptr;
		while (cur != nullptr) {
			if (cur->val == val) {
				Node* tmp = cur;
				if (pre == nullptr) {//cur是head节点
					head = cur->next;//设置新head
					cur = head;
				}
				else {//后续节点
					pre->next = cur->next;//跨过这个节点
					cur = cur->next;
				}
				tmp->next = nullptr;
				delete tmp;
				size--;
			}
			else {
				pre = cur;
				cur = cur->next;
			}
		}
	}

	bool find(int val)const {
		Node* cur = head;
		while (cur != nullptr) {
			if (cur->val == val) {
				return true;
			}
			cur = cur->next;
		}
		return false;
	}

	//找索引的值
	int get(int index)const {
		if (index < 0 || index >= size) {
			throw "get: error index\n";
		}
		Node* cur = head;
		for (int i = 0; i < index; i++) {
			cur = cur->next;
		}
		return cur->val;
	}

	void printList()const {
		Node* cur = head;
		while (cur != nullptr) {
			cout << cur->val << " -> ";
			cur = cur->next;
		}
		cout << "nullptr" << endl;
	}


	Node* getHead()const {
		return head;
	}

private:
	Node* head;
	int size;
};