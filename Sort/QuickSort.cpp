#if 0
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
#include<time.h>
#include<random>

using namespace std;
#define endl "\n"

const int MAXN = 1e5 + 5;
int nums[MAXN];
int n;

int partition1(int l, int r, int x) {
	// 最后的效果需要的是 <leftSide部分都是 <=x的值
	int leftSide = l;
	//需要特别记录最后一个等于x的值的下标
	int last = l;
	for (int i = l; i <= r; i++) {
		if (nums[i] <= x) {
			swap(nums[i], nums[leftSide]);

			if (nums[leftSide] == x) {
				last = leftSide;
			}
			leftSide++;
		}

	}
	//leftSide 始终指向下一个存放<=x值的位置(如果还有的话)
	// 所以最后leftSide也就是第一个 >x的位置
	//最后需要的效果是 leftSide-1位置就是 x值
	swap(nums[last], nums[leftSide-1]);
	return leftSide-1;
}

void quickSort1(int l,int r) {
	if (l >= r) {
		return;
	}
	int pivot = nums[l + (rand() % (r - l + 1))];
	int mid = partition1(l, r, pivot);
	quickSort1(l, mid - 1);
	quickSort1(mid + 1, r);
}

int first, last;
void partition2(int l, int r,int x) {
	first = l, last = r;
	int pt = l;
	// 最后指针撞到last就停下  
	// last后的都是>x的部分
	// pt+last 走过的就是 r-l这个范围
	while (pt <= last) {
		if (nums[pt] == x) {
			pt++;
		}
		else if (nums[pt] < x) {
			//first 和 pt都++
			swap(nums[pt++], nums[first++]);
		}
		else {
			//注意这里把后面的数字换过来 三种情况都可能中
			// 不能 pt++  相当于这个位置的数字还没有考察
			// 后续如果数字小  交换 first++ pt++
			// 始终保持 first都是小于x的
			// 最终整个流程下来
			// first指向 == x 部分的最左侧边界
			// last指向  == x 部分的最右侧边界
			swap(nums[pt], nums[last--]);
		}
	}
}

//  5  1  4  6  8  9  2  3  6  9  1  2

//  5  1  4  2  1  2  3  6  6  9  9  8
//  f		             f
//  i		                   i  r
//									 r

void quickSort2(int l, int r) {
	if (l >= r) {
		return;
	}
	int pivot = nums[l + rand() % (r - l + 1)];
	partition2(l, r, pivot);

	int ls = first;
	int rs = last;
	quickSort2(l, ls - 1);
	quickSort2(rs + 1, r);
}

void print() {
	cout << nums[0];
	for (int i = 1; i < n; i++) {
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
	quickSort2(0, n - 1);
	print();

}
#endif