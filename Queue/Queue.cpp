#include<iostream>



//const int N = 1e5 + 5;
//int Queue[N];
//int Left, Right;
//
//void build() {
//	Left = Right = 0;
//}
//
//bool isEmpty() {
//	return Left == Right;
//}
//
//void push(int val) {
//	Queue[Right++] = val;
//}
//
//
//int back() {
//	return Queue[Right-1];
//}
//
//int pop() {//队头弹出
//	Left++;
//}
//
//int head() {
//	return Queue[Left];
//}
//
//int size() {
//	return Right - Left;
//}
//
//int front() {
//	return Queue[Left];
//}

class Queue {
	struct Node {
		Node* next;
		int data;
		Node(Node*next=nullptr,int data=-1):next(next),data(data){}
	};
};