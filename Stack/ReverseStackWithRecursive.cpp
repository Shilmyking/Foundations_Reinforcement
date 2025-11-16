
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
#include<stack>

using namespace std;

#if 0
//递归函数逆序一个栈
#define int long long
#define endl "\n"

const int N = 1e5+5;
int Stack[N];
int Size = 0;

// 递归实现获取栈底元素
int bottomOut() {
	//拿出栈顶元素
	int ans = Stack[--Size];
	//如果全部元素都被取出了
	if (Size==0) {
		return ans;
	}

	//栈还未空 继续递归  一直拿出栈顶元素
	//如果真的就只有一个元素了 ，马上就能拿到栈底元素  下一次就要栈空了  
	int last = bottomOut();
	Stack[Size++]=ans;//你不是真真的栈底元素  回溯的时候需要维持栈原有顺序不变
	return last;//我的上一级还需要这个栈底元素  一直返回到第一次调用bottomOut函数

}

//reverse 实现的是 逆序当前栈   
// 那取出栈底元素 然后reverse一下这个栈 再把栈底元素push到栈顶 是不是就实现了栈的reverse
void reverse(){
	//栈空 reverse返回
	if (Size==0) {
		return;
	}
	//栈底元素
	int num = bottomOut();
	//逆序当前栈
	reverse();
	//此前的栈底元素放到栈顶
	Stack[Size++] = num;
}


signed main() {

	for (int i = 0; i < 6; i++) {
		Stack[Size++] = i;
	}

	reverse();
	while (Size>0) {
		cout << Stack[--Size] << " ";
	}
	cout << endl;
}
#endif