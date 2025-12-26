#include<algorithm>

using namespace std;
const int INF = 0x3f3f3f3f;

struct Node {
	Node* next;
	int data;
	Node(int data = -1, Node* next = nullptr) :next(next), data(data) {}
};

// Top  -> node -> node -> node --> bottomNode

class LinkedListStack {
private:
	Node* Top;
	int size;


	void copyFrom(const LinkedListStack& other) {
		if (other.Top == nullptr) {
			Top = nullptr;
			size = 0;
			return;
		}
		Top = new Node(other.Top->data);
		Node* cur = Top;
		Node* otherCur = other.Top->next;

		while (otherCur != nullptr) {
			cur->next = new Node(otherCur->data);
			cur = cur->next;
			otherCur = otherCur->next;
		}
		size = other.size;
	}

public:

	LinkedListStack() :Top(nullptr),size(0) {}

	~LinkedListStack() {
		clear();
	}

	LinkedListStack(const LinkedListStack& other) {
		copyFrom(other);
	}

	LinkedListStack& operator=(const LinkedListStack& other) {
		if (this != &other) {
			clear();
			copyFrom(other);
		}
		return *this;
	}

	void push(int val) {
		Node* node = new Node(val, Top);
		Top = node;
		size++;
	}
	
	void pop() {
		if (Top == nullptr) {
			return;
		}
		Node* tmp = Top;
		Top = Top->next;
		delete tmp;
		size--;
	}

	int top() const {
		if (Top == nullptr) {
			return INF;
		}
		return Top->data;
	}
	bool empty()const {
		return Top == nullptr;
	}

	int Size() {
		return size;
	}

	void clear() {
		while (Top != nullptr) {
			Node* tmp = Top;
			Top = Top->next;
			delete tmp;
		}
		Top = nullptr;
		size = 0;
	}

};