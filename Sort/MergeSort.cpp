
// 归并排序
// 测试链接 : https://www.luogu.com.cn/problem/P1177


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


using namespace std;
#define int long long 
#define endl "\n"

const int N = 1e5 + 5;
int nums[N];
int help[N];
int n;

void merge(int left, int mid, int right) {
	int l = left, r = mid + 1;//左右两侧起始点
	int i = left;
	while (l <= mid && r <= right) {
		help[i++] = nums[l] < nums[r] ? nums[l++] : nums[r++];
	}
	//一侧越界了
	while (l <= mid) {
		help[i++] = nums[l++];
	}
	while (r <= right) {
		help[i++] = nums[r++];
	}
	for (int i = left; i <= right; i++) {
		nums[i] = help[i];
	}
	return;
}

void MergeSort(int left, int right) {
	if (left == right) {
		return;//一个元素 无需合并
	}
	int mid = (right + left) / 2;
	MergeSort(left, mid);
	MergeSort(mid + 1, right);
	//左右两侧合并有序之后  你给我合并好整个 left 到 right范围
	merge(left, mid, right);
}

//非递归归并排序
void MergeSort1() {
	//自己做逻辑处理  每组枚举step
	for (int step = 1; step < n; step <<= 1) {
		//同样的找到你这一组的 左侧部分 和 右侧部分

		int l = 0;
		//按照递归树的结构
		//你step就正常step去吧  还是需要从数组的第一个位置到末尾 进行分组合并
		while (l < n) {
			int left = l, mid = left + step - 1;
			if (mid + 1 >= n) {//根本不存在right部分了 加上你自己已经调整有序了 回去找下一个step开始
				break;
			}
			// l+(step<<1)-1
			int right = std::min(mid + step, n - 1);//你右侧可能不够一组了  所以限界
			merge(left, mid, right);//整个边界都找好了  你合并去吧
			//这大组合并好了  去找下一组
			l = right + 1;
		}
	}
}
void printNums() {
	cout << nums[0];
	for (int i = 1; i < n; i++) {
		cout << " " << nums[i];
	}
	cout << endl;
}

//signed main() {
//	ios_base::sync_with_stdio(false);
//	cin.tie(nullptr);
//	cout.tie(nullptr);
//	cin >> n;
//	for (int i = 0; i < n; i++) {
//		cin >> nums[i];
//	}
//	//MergeSort(0, n - 1);
//	MergeSort1();
//	printNums();
//}
