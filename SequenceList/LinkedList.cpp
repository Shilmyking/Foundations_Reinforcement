
#include<vector>
#include<algorithm>

#include<cstring>
using namespace std;

struct Node {
	Node* next;
	int data;
	Node(int data = -1,Node* next = nullptr) :next(next), data(data) {}
};

//1
void _1removeAll(Node* head,int x) {
	if (head == nullptr) { return; }
	Node* cur = head->next;//带头结点
	Node* pre = head;
	while (cur != nullptr) {
		if (cur->data == x) {
			pre->next = cur->next;
			delete cur;
			cur = pre->next;
		}
		else {
			pre = cur;
			cur = cur->next;
		}
	}
}

//2
void _2removeSmallest(Node* head, int x) {
	if (head == nullptr|| head->next == nullptr) { return; }
	if(head->next->next==nullptr){//一个节点
		Node* node = head->next;
		delete node;
		head->next = nullptr;
		return;
	}
	Node* cur = head->next;
	int Min = cur->data;
	//先找节点
	while (cur != nullptr) {
		Min = std::min(Min, cur->data);
		cur = cur->next;
	}
	//Min 就是最小值
	cur = head->next;
	while (cur->next->data != Min) {
		cur = cur->next;
	}//cur的下一个就是要删除的节点
	Node* node = cur->next;
	cur->next = node->next;
	delete node;
}

//3 链表反转 不带头节点
Node* reverse(Node* head) {
	if (head == nullptr) { return nullptr; }
	Node* pre = nullptr;
	Node* cur = head;
	Node* next = head->next;
	while (cur != nullptr) {
		next = cur->next;// 比较好防止 nullptr的出现
		cur->next = pre;
		pre = cur;
		cur = next;
	}
	return pre;
}
void _3reverse(Node* head) {
	Node* trueHead = head->next;
	head->next = reverse(trueHead);
}

//4 
void _4removeBetween(Node* head, int s, int b) {
	if (head == nullptr || head->next == nullptr) { return; }
	Node* cur = head->next;
	Node* pre = head;
	while (cur != nullptr) {
		if (cur->data >= s && cur->data <= b) {
			pre->next = cur->next;
			delete cur;
			cur = pre->next;
		}
		else {
			pre = cur;
			cur = cur->next;
		}
	}
}

//5
// 两个链表的公共节点  
// 由于是单链表 节点一旦从一个地方共享，后续的所有节点都是共享的
Node* _5find(Node* list1,Node*list2) {
	//假设都是带头结点
	Node* cur1 = list1->next; int length1 = 0;
	Node* cur2 = list2->next; int length2 = 0;
	while (cur1 != nullptr) {
		length1++, cur1 = cur1->next;
	}
	while (cur2 != nullptr) {
		length2++, cur2 = cur2->next;
	}
	int sub;
	if (length1 > length2) {
		cur1 = list1;//长链表
		cur2 = list2;
		sub = length1 - length2;
	}
	else {
		cur1 = list2;
		cur2 = list1;
		sub = length2 - length1;
	}
	for (int i = 0; i < sub; i++) {
		cur1 = cur1->next;
	}
	while (cur1 != cur2) {
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	return cur1;
}

vector<Node*> _6remove(Node* head) {
	Node* trueHead = head->next;
	//带头结点
	Node* list1=new Node();//奇数项
	Node* list2=new Node();//偶数项
	Node* cur=trueHead;
	Node* cur1 = list1;
	Node* cur2 = list2;
	int cnt = 0;
	while (cur != nullptr) {
		if ((cnt & 1) == 1) {//cnt为奇数
			cur1->next = trueHead;
			trueHead->next = nullptr;
			cur1 = cur1->next;
		}
		else {//偶数
			cur2->next = trueHead;
			trueHead->next = nullptr;
			cur2 = cur2->next;
		}
		cnt++;
	}
	// list1 list2
	return { list1,list2 };
}

Node* _7remove(Node* head) {
	Node* cur = head->next;
	while (cur->next != nullptr) {
		if (cur->data == cur->next->data) {
			cur = cur->next;
		}
		else {
			Node* tmp = cur->next;
			cur->next = cur->next->next;
			cur = cur->next;
			delete tmp;
		}
	}
	return head;
}

// 题意？ 公共元素 链表相交后的内容 --> 6
Node* _8generate(Node* list1, Node* list2) {
	Node* ans = new Node();
	Node* cur = ans;
	Node* cur1 = list1->next;
	Node* cur2 = list2->next;
	while (cur1 != nullptr && cur2 != nullptr) {
		if (cur1->data == cur2->data) {
			cur->next = new Node(cur1->data);
		}
		else if (cur1->data > cur2->data) {
			cur2 = cur2->next;
		}
		else {
			cur1 = cur1->next;
		}
	}
	return ans;
}

// 9 -->8代码


// 10 链表B是否为链表A的连续子序列  -->子串问题
// KMP 
int linkedListKMP(Node* list1, Node* list2) {
	//遍历得到list2长度
	int len2 = 0,len1=0;
	Node* cur = list2->next;
	Node* tmp = list1->next;
	while (tmp != nullptr) {
		tmp = tmp->next, len1++;
	}
	while (cur != nullptr) {
		len2++, cur = cur->next;
	}
	int* nums = new int[len2];
	cur = list2->next;
	int i = 0, j = 0;
	while (cur != nullptr) {
		nums[i] = cur->data, cur = cur->next;
	}
	int* nexts = new int[len2];
	nexts[0] = -1, nexts[1] = 0;
	int cn = nexts[1];//cn = 0
	i = 0;
	
	while (i < len1 && j < len2) {

	}
}