#include<random>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

random_device rd;
mt19937 rng(rd());

const int MAXN = 5e5 + 5;
const int INF = 0x3f3f3f3f;
const int Min = -INF;
const int Max = INF;
int nums[MAXN];


int randomInt(int min, int max) {
	uniform_int_distribution<int>dist(min, max);
	return dist(rng);
}

void getRandomNums(int n, int minVal, int maxVal) {
	for (int i = 0; i < n; i++) {
		nums[i] = randomInt(minVal, maxVal);
	}
}

vector<int> getRandomVector(int n, int minVal, int maxVal) {
	vector<int>arr(n);
	for (int i = 0; i < n; i++) {
		arr[i] = randomInt(minVal, maxVal);
	}
	return arr;
}

// 打印数组的辅助函数（出错时用）
void printVector(const vector<int>& nums) {
	cout << "[ ";
	for (int x : nums) {
		cout << x << " ";
	}
	cout << "]" << endl;
}


int solve_check(vector<int> nums) {
	sort(nums.begin(), nums.end());

	// 从小到大 一定不会错过
	int expected = 1; 
	for (int x : nums) {
		if (x <= 0) continue; 
		if (x == expected) {//存在这个数字
			expected++;
		}
		else if (x > expected) {
			// 如果缺了 expected  --->就是答案
			return expected;
		}
	}
	return expected;
}


// 返回 在范围 l 到 r的最小正整数
//int dfs(vector<int>&nums,int l,int r) {
//	if (l == r) {
//		return nums[l] > 0 ? nums[l] : INF;
//	}
//	int mid = (l + r) / 2;
//	int left = dfs(nums, l, mid - 1);
//	int right = dfs(nums, mid + 1, r);
//	//整合得到区间内的最小正整数 
//	return std::min({ left,right,nums[mid] });
//}


int f(vector<int>&nums) {
	// 没有给出 数值的范围 只给出了 nums个数
	// 答案一定出现在 1-n这个范围内
	int n = nums.size();
	if (n == 0) {
		return 1;
	}
	vector<int>Map(n+1,0);//作为统计
	// 可以不用管  
	for (int i = 0; i < n; i++) {
		if (nums[i] <= 0 || nums[i] > n) { continue; }
		Map[nums[i]]++;
	}
	int i = 1;
	// 从1开始如果找到没有出现的 直接return
	for (; i <= n; i++) {
		if (Map[i] == 0) {
			return i;
		}
	}
	//最后check 1-n都出现了 return i  此时就是n+1
	return n+1 ;
}




int main() {
	cout << "开始测试..." << endl;

	int testTime = 50000;   // 测试次数：5万次
	int maxSize = 100;      // 数组最大长度
	int maxVal = 200;       // 数组元素最大值（包含负数范围）

	bool success = true;

	for (int i = 0; i < testTime; i++) {
		// 1. 生成随机参数
		int n = randomInt(0, maxSize); // 长度 0 ~ 100
		// 生成包含负数、0、正数的随机数组
		vector<int> arr = getRandomVector(n, -maxVal, maxVal);

		// 2. 拷贝数组 (因为 solve_check 会排序改变数组顺序，为了公平对比)
		vector<int> arr1 = arr;
		vector<int> arr2 = arr;

		// 3. 获取两个算法的结果
		int ans1 = solve_check(arr1);
		int ans2 = f(arr2);

		// 4. 比对结果
		if (ans1 != ans2) {
			success = false;
			cout << "【测试失败】" << endl;
			cout << "出错的数组: ";
			printVector(arr);
			cout << "暴力解(正确): " << ans1 << endl;
			cout << "你的解(错误): " << ans2 << endl;
			break; // 一旦出错，立刻停止
		}
	}

	if (success) {
		cout << "Nice! 通过了 " << testTime << " 组随机测试。" << endl;
	}
	else {
		cout << "Fucking fucked! 请检查代码逻辑。" << endl;
	}

	return 0;
}