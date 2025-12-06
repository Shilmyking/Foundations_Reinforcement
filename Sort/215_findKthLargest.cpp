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
int heap[MAXN];
int heapSize = 0;

// 前K大 
// 维持小根堆  先进入k个元素  如果后续元素比堆顶还小 那肯定不属于前K大

void build() {
    heapSize = 0;
}

//上浮
void heapInsert(int i) {
    // 自己比堆顶小 -->上浮
    while (heap[i] < heap[(i - 1) / 2]) {
        std::swap(heap[i], heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

//下沉
void heapify(int i) {
    int leftSide = 2 * i + 1;
    while (leftSide < heapSize) {
        int small = leftSide + 1 < heapSize && heap[leftSide+1] < heap[leftSide] ? leftSide + 1 : leftSide;
        small = heap[i] < heap[small] ? i : small;
        if (i == small) {
            break;
        }
        std::swap(heap[i], heap[small]);
        i = small;
        leftSide = 2 * i + 1;
    }
}

void add(int num) {
    //加入数字num  
    heap[heapSize] = num;
    heapInsert(heapSize++);
}

void heapPop() {
    std::swap(heap[0], heap[--heapSize]);
    heapify(0);
}

int top() {
    return heap[0];
}

class Solution {
public:
    //第k大
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        build();
        for (int i = 0; i < k; i++) {
            add(nums[i]);
        }
        for (int i = k; i < n; i++) {
            if (top() < nums[i]) {
                heapPop();//或者直接换堆顶  heap[0] = nums[i]  heapify(0)
                add(nums[i]);
            }
        }
        return top();
    }
};

class Solution1 {
    // 
    void partition(vector<int>& nums,int &first, int &last, int x) {
        int i = first;
        //必须取等  i<=last  这个位置也需要处理  可能还是和first 位置swap!
        while (i <= last) {
            if (nums[i] == x) {
                i++;
            }
            else if (nums[i] < x) {
                std::swap(nums[first++], nums[i++]);
            }
            else {
                std::swap(nums[i], nums[last--]);
            }
        }
    }

    int quickSort(vector<int>& nums, int k) {
        int ans = 0;
        for (int first = 0, last = nums.size() - 1; first <= last;) {
            int pivot = nums[first + rand() % (last - first + 1)];
            //还需要复用原本的 first 和 last
            int l = first, r = last;
            partition(nums, l, r, pivot);
            // 缩小范围继续查找
            // 其实这里该 这么想
            //  <first first - last >last
            // first~last 都是一种数字
            if (l > k) {
                last = l - 1;
            }
          
            else if (k > r) {
                first = r+1;
            }
            else {
                ans = nums[k];
                break;
            }
        }
        return ans;
    }

public:
    int findKthLargest(vector<int>& nums, int k) {
        return quickSort(nums, nums.size() - k);
    }
};

//计数排序
//基数排序 
//BFPRT

#endif