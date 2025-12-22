
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;


int Moore(vector<int>& nums) {
	int cand = 0;
	int hp = 0;
	for (int i = 0; i < nums.size(); i++) {
		if (hp == 0) {//当前没有候选
			cand = nums[i];
			hp = 1;
		}
		else if (nums[i] != cand) {
			//敌人
			hp--;
		}
		else {//友军
			hp++;
		}
	}
	//偶数长度的数组 
	if (hp == 0) {
		return -1;
	}
	int check = 0;//现在验证cand
	for (int i = 0; i < nums.size(); i++) {
		check += nums[i] == cand ? 1 : 0;
	}
	return hp > nums.size() / 2 ? cand : -1;
}