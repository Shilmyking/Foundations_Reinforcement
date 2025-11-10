
#include<iostream>

using namespace std;

const int N = 1e5 + 4;
int Stack[N];
int Size = 0;//始终指向需要加入元素的位置

void build() {
	Size = 0;
}

bool isEmpty() {
	return Size == 0;
}

void push(int val) {
	Stack[Size++] = val;
}

void pop() {
	Size--;
}

int top() {
	return Stack[Size-1];
}

int size() {
	return Size;
}
