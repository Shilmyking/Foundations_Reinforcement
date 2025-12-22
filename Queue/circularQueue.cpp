#include<iostream>

const int N = 1e5 + 5;
int Queue[N];
int Left, Right;

void build() {
	Left = Right = 0;
}

bool isEmpty() {
	return Left == Right;
}

bool isFull() {
	return (Right + 1) % N == Left;//下一个可以添加数字的位置
}

void push(int val) {
	if (isFull()) {
		return;
	}
	Queue[Right] = val;
	Right = (Right + 1) % N;//指针 循环
}

void pop() {
	if (isEmpty()) {
		return;
	}
	Left = (Left + 1) % N;
}

int head() {
	if (isEmpty()) {
		throw "head:Empty\n";
	}
	return Queue[Left];
}

int back() {
	if (isEmpty()) {
		throw "back:Empty\n";
	}
	// Right指向待插入的位置
	return Queue[(Right - 1 + N) % N];//循环
}

int size() {
	return (Right - Left + N) % N;//同余原理
}
