
struct Node {
	int data;
	Node* pre;
	Node* next;
	Node(int data = -1, Node* pre = nullptr, Node* next = nullptr) :data(data), pre(pre), next(next) {}
};

class doubleCircleLinkedList {
private:
	Node* head;
public:
	doubleCircleLinkedList() {
		head = new Node();
		head->pre = head;
		head->next = head;
	}

	~doubleCircleLinkedList() {

	}

	void insertHead(int val) {
		Node* newNode = new Node(val);
		newNode->next = head->next;
		newNode->pre = head;
		//if (head->pre = head) {
		//	head->pre = newNode;
		//}
		// head 此前的 next 的pre指针 ...
		head->next->pre = newNode;
		head->next = newNode;
	}

	void insertTail(int val) {
		Node* newNode = new Node(val);
		newNode->pre = head->pre;
		newNode->next = head;

		head->pre->next = newNode;//尾部指向 
		head->pre = newNode;

		head = newNode;
	}

	void remove(int val) {
		Node* cur = head;
		while (cur != nullptr) {
			if (cur->data == val) {//删除 cur
				cur->pre->next = cur->next;
				cur->next->pre = cur->pre;
				delete cur;
				break;
			}
			cur = cur->next;
		}
	}

	bool find(int val) {
		Node* cur = head;
		while (cur != nullptr) {
			if (cur->data == val) {
				return true;
			}
			cur = cur->next;
		}
		return false;
	}
};