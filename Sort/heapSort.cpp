
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
#define endl "\n"

const int MAXN = 1e5 + 5;
int nums[MAXN];
int heapSize = 0;
int n;
void build() {
	heapSize = 0;
}

//实现小根堆
//上浮
void heapInsert(int i) {
	//当前节点小 上浮
	while (nums[i] < nums[(i - 1) / 2]) {
		std::swap(nums[i], nums[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}

// 下沉
void heapify(int i) {
	int leftSide = 2 * i + 1;
	while (leftSide < heapSize) {
		int small = leftSide + 1 < heapSize && nums[leftSide] > nums[leftSide + 1] ? leftSide + 1 : leftSide;
		small = nums[i] > nums[small] ? small : i;
		if (small == i) {
			break;
		}
		std::swap(nums[i], nums[small]);
		i = small;
		leftSide = 2 * i + 1;
	}
}

//自顶向下  or  自底向上建堆
void heapSort() {
	//从堆顶 往上 上浮 
	// O(n*logn)
	//for (int i = 0; i < n; i++) {
	//	heapInsert(i);
	//}

	//从底向上 heapify  
	// O(n)
	for (int i = n - 1; i >= 0; i--) {
		heapify(i);
	}
	//此后的逻辑就是 和最后一个位置swap 每次确认好一个位置的值
	// heapSize = n
	while (heapSize > 1) {
		std::swap(nums[0], nums[--heapSize]);
		heapify(0);//每次堆顶 heapify
	}
}

void print() {
	// 逆序打印
	cout << nums[n-1];
	for (int i = n-2; i>=0; i--) {
		cout << " " << nums[i];
	}
	cout << endl;
}




int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	heapSort();
	print();

}