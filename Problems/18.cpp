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
	vector<int>arr;
	for (int i = 0; i < n; i++) {
		arr[i] = randomInt(minVal, maxVal);
	}
	return arr;
}

int Sort(vector<int> nums) {
	std::sort(nums.begin(),nums.end());
	int small = INF;
	for (int i = 0; i < nums.size(); i++) {
		
	}

}