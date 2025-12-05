#if 0

#include<random>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

random_device rd;
mt19937 rng(rd());

void print(vector<int>& nums) {
	int n = nums.size();
	for (int i = 0; i < n; i++) {
		cout << nums[i] << " ";
	}
	cout << endl;
}

void SelectSort(vector<int>& nums) {
	int n = nums.size();
	//选择 排序  
	// 0~n-1最小的放在 0
	// 1~n-1 最小的放在1
	for (int i = 0, minIndex; i < n; i++) {
		minIndex = i;//从i开始
		for (int j = i + 1; j < n; j++) {
			if (nums[j] < nums[minIndex]) {
				minIndex = j;
			}
		}
		std::swap(nums[i], nums[minIndex]);
	}
	print(nums);
}

void BubbleSort(vector<int>& nums) {
	int n = nums.size();
	for (int i = n-1; i >=0; i--) {
		for (int j = 0; j < i; j++) {
			if (nums[j] > nums[j + 1]) {
				std::swap(nums[j], nums[j + 1]);
			}
		}
	}
	print(nums);
}

void InsertSort(vector<int>& nums) {
	int n = nums.size();
	// 0~0 有序
	// 让 0~1 有序
	//...
	// 0~n有序
	for (int i = 0; i < n; i++) {
		// 当前要让 0~i有序  
		// 0~i-1 已经有序了 继续插排
		// 如果 j位置的数字要大 和 j+1交换
		// j+1最开始就是 i位置的数字
		for (int j = i - 1; j >= 0 && nums[j] > nums[j + 1]; j--) {
			std::swap(nums[j], nums[j + 1]);
		}
	}
	print(nums);
}

void ShellSort(vector<int>& nums) {
	int n = nums.size();
	for (int gap = n / 2; gap >= 1; gap /= 2) {
		//其实就是下面的1都变为了gap
		// 插排初始为1 这里最初始gap为 n/2 允许元素大范围挪动
		for (int i = gap; i < n; i++) { //最后gap==1 就是标准插排

			// j 每次减 gap，比较 j 和 j+gap  在这一个gap内比较
			// 每次跨gap进行比较
			for (int j = i - gap; j >= 0 && nums[j] > nums[j + gap]; j -= gap) {
				std::swap(nums[j], nums[j + gap]);
			}
		}
	}
	print(nums);
}

int randomInt(int min, int max) {
	uniform_int_distribution<int>dist(min, max);
	return dist(rng);
}

vector<int> getRandomVector(int n, int minVal, int maxVal) {
	vector<int>arr;
	for (int i = 0; i < n; i++) {
		arr.push_back(randomInt(minVal, maxVal));
	}
	return arr;
}

int main() {
	vector<int>nums = getRandomVector(14, 0, 100);
	vector<int>nums1 = nums;
	vector<int>nums2 = nums;
	vector<int>nums3 = nums;
	vector<int>nums4 = nums;
	print(nums);

	SelectSort(nums1);
	BubbleSort(nums2);
	InsertSort(nums3);
	ShellSort(nums4);
}
#endif