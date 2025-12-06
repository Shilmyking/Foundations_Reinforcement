
// 牛牛的背包问题 & 世界冰球锦标赛
// 牛牛准备参加学校组织的春游, 出发前牛牛准备往背包里装入一些零食, 牛牛的背包容量为w。
// 牛牛家里一共有n袋零食, 第i袋零食体积为v[i]。
// 牛牛想知道在总体积不超过背包容量的情况下,他一共有多少种零食放法(总体积为0也算一种放法)。
// 输入描述：
// 输入包括两行
// 第一行为两个正整数n和w(1 <= n <= 30, 1 <= w <= 2 * 10^9),表示零食的数量和背包的容量
// 第二行n个正整数v[i](0 <= v[i] <= 10^9),表示每袋零食的体积
// 输出描述：
// 输出一个正整数, 表示牛牛一共有多少种零食放法。
// 测试链接 : https://www.luogu.com.cn/problem/P4799
#if 0 

#include<iostream>
#include<vector>
#include<queue>
#include<functional>
#include<list>
#include<map>
#include<unordered_map>
#include<set>
#include<unordered_set>
#include<algorithm>
#include<cstring>
#include<string>

using namespace std;
#define int long long 
#define endl "\n"

const int MAXN = 41+3;
const int MAXM = (1 << 20) + 5;

int nums[MAXN];
// 存储 分解为左右两侧递归
// 最后合并
int lsum[MAXM],lsize=0;
int rsum[MAXM],rsize=0;
int n,w;

//双向广搜
void build() {
	memset(nums, 0, sizeof(nums));
	lsize = rsize = 0;
}
// i是遍历当前数组 到达了什么位置
//  当前的累加sum  不超过 w
//  j 拿来记录当前的递归 下标使用到了那里 --->最后需要知道有多少展开的数字  +  排序  
// 返回当前递归最后填入的j的下标
int f(int i,int start, int end,int sum, int ans[], int j ) {
	if (sum > w) {//已经超了 违规情况
		return j;
	}
	if (i == end) {//end 是不能选择的一个位置
		// 到达了末尾都没有违规  说明符合条件
		ans[j++] = sum;
	}
	else {
		// 不选择当前位置
		j = f(i + 1, start, end, sum, ans, j);

		//选择i位置
		j = f(i + 1, start, end, sum + nums[i], ans, j);
	}
	return j;//最后返回当前位置 填写到j的位置  回溯
}

int compute() {
	//求出 lsum + rsum ---> 排好序  进行组合统计答案
	int lsize = f(0, 0, n >> 1, 0, lsum, 0);
	int rsize = f(n>>1, n >> 1, n, 0, rsum, 0);

	std::sort(lsum, lsum + lsize);
	std::sort(rsum, rsum + rsize);
	int i = 0, j = rsize - 1;
	int ans = 0;

	for (; i < lsize; i++) {

		//一直减到符合条件为止
		while (j >= 0 && lsum[i] + rsum[j] > w) {
			j--;
		}
		ans += j+1;
	}
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	build();

	cin >> n >> w;
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}

	cout << compute() << endl;

}
#endif