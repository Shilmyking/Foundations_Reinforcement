#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

const int MAXN = 1e5 + 5;
int n;
vector<int>Bucket[MAXN];

void insertSort(vector<int>& arr) {
    // 每一趟确保 0~i有序
    for (int i = 1; i < arr.size(); i++) {
        int key = arr[i];//当前的值  让这个值插入到前面
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];// 相当于j位置的值 挪到了j+1  往后移
            --j;
        }
        //当找到合适的位置就是 将key覆盖到的位置
        //现在 arr[j]<=key了  后面那些更大的值都正常往后挪好了 j+1放入key
        arr[j + 1] = key;
    }
}

void BucketSort(vector<int>& nums) {
    int minVal = nums[0], maxVal = nums[0];
    for (int i = 0; i < n; i++) {
        minVal = std::min(minVal, nums[i]);
        maxVal = std::max(maxVal, nums[i]);
    }
    if (minVal == maxVal) { return; }

    long long range = maxVal - minVal;// 处理负数

    int bucketNum = n;//要的桶的个数

    // +1 其实是要向上取整  (range+n)/n   
    // 计算每个桶负责的数值范围
    int bucketSize = range / bucketNum + 1;//确保bucketSize至少为1

    //清空bucket
    for (int i = 0; i <= bucketNum; i++) {
        Bucket[i].clear();
    }

    //处理负数偏移的同时入桶
    for (int i = 0; i < n; i++) {
        // 每个桶处理 bucketSize 数据范围的数字
        int idx = (nums[i] - minVal) / bucketSize;
        Bucket[idx].push_back(nums[i]);
    }
    //填表
    int filled = 0;
    //有 bucketNum个桶
    for (int i = 0; i <= bucketNum; i++) {
        if (Bucket[i].empty()) { continue; }
        insertSort(Bucket[i]);//排序

        for (int val : Bucket[i]) {
            nums[filled++] = val;
        }
    }
}



class Solution {
public:
    int maximumGap(vector<int>& nums) {
        n = nums.size();
        if (n < 2) {
            return 0;
        }
        BucketSort(nums);
        int maxGap = 0;
        for (int i = 1; i < n; i++) {
            maxGap = std::max(maxGap, nums[i] - nums[i - 1]);
        }
        return maxGap;
    }
};