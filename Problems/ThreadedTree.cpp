#include<queue>
#include<algorithm>
#include<iostream>
#include<functional>

using namespace std;

enum Tag {
	Link,
	Thread,
};

struct Node {
	char data;
	Node* left;
	Node* right;
	Tag lTag;
	Tag rTag;
	Node(char data, Node* left = nullptr, Node* right = nullptr)
		:data(data),
		left(left),
		right(right),
		lTag(Link),
		rTag(Link)
	{}
};

class ThreadedBinaryTree {
private:
	Node* root;

public:

};

