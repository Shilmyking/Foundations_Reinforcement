
// 有序数组中是否存在一个数字

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

#include <ctime>      // 包含 time()

using namespace std;

#if 0
// 为了验证（"对数器"的正确方法）
// 保证 arr 有序
bool linearSearch(const std::vector<int>& arr, int num) {
	for (int cur : arr) {
		if (cur == num) {
			return true;
		}
	}
	return false;
}

bool binarySearch(const std::vector<int>& arr, int num) {
	if (arr.empty()) { // 检查数组是否为空
		return false;
	}

	int l = 0;
	int r = arr.size() - 1; // 正确获取数组大小
	int m = 0;

	while (l <= r) {
		// m = (l + r) / 2; // 这种写法在 l 和 r 都非常大时，(l + r) 可能会溢出 int 范围
		m = l + (r - l) / 2; // 这是更安全的写法，可以防止溢出

		if (arr[m] == num) {
			return true;
		}
		else if (arr[m] > num) {
			r = m - 1;
		}
		else { // arr[m] < num
			l = m + 1;
		}
	}

	return false;
}

//查找数组是否存在target  需要传入数组长度n
bool FindNumber(int arr[],int n , int target) {
	//int n = sizeof(arr);//退化为指针  这里错误的写法
	if (n == 0) { return false; }
	//二分
	int left = 0, right = n - 1, mid;
	while (left <= right) {
		mid = (left + right) / 2;
		if (arr[mid] == target) {
			return true;
		}
		else if (arr[mid] > target) {
			right = mid - 1;
		}
		else if (arr[mid] < target) {
			left = mid + 1;
		}
		
	}
	return false;
}

// 生成随机数组
std::vector<int> generateRandomVector(int n, int v) {
	std::vector<int> arr(n);
	for (int i = 0; i < n; i++) {
		arr[i] = (rand() % v) + 1; // 生成 [1, v] 范围内的随机数
	}
	return arr;
}

int main() {
	// 初始化随机数种子
	srand((unsigned int)time(NULL));

	int N = 100;
	int V = 1000;
	int testTime = 500000;
	std::cout << "测试开始" << std::endl;

	for (int i = 0; i < testTime; i++) {
		int n = rand() % N; // 随机生成数组长度 [0, N-1]
		std::vector<int> arr = generateRandomVector(n, V);

		// 排序
		std::sort(arr.begin(), arr.end());

		int num = rand() % V; // 随机生成要查找的数 [0, V-1]

		if (linearSearch(arr, num) != binarySearch(arr, num)) {
			std::cout << "出错了!" << std::endl;
			// 可以在这里打印出错的数组和数字，方便调试
			// std::cout << "Array: ";
			// for(int val : arr) std::cout << val << " ";
			// std::cout << "\nTarget: " << num << std::endl;
			break; // 出错即停止
		}
	}

	std::cout << "测试结束" << std::endl;
	return 0;
}
#endif 