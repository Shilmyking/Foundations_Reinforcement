#include<algorithm>
#include<cstring>

using namespace std;

const int MAXN = 1e5 + 10;
int nums[MAXN];
int n;//数组n个元素
int heapSize = 0;

void build() {
	heapSize = 0;
}

//实现大根堆
//从 i位置开始 向上进行上浮的操作
void heapInsert(int i) {
	//只要 i节点的值小于父节点的值 就一直上浮
	while (nums[i] > nums[(i - 1) / 2]) {
		std::swap(nums[i], nums[(i - 1) / 2]);
		i = (i - 1)/2;//上浮的父节点的位置 继续查看父节点的状态..
	}
}

//从 i位置开始进行 下沉的操作
void heapify(int i) {
	int leftSide = 2 * i + 1;
	// rightSide = leftSide + 1;
	//还存在左孩子的话 查看是否还需要下沉
	while (leftSide < heapSize) {
		//当前 比较出的最大值 
		// 先比较孩子节点 找到 孩子节点中较大的一方，然后再和当前节点i比较
		// 如果存在右孩子 && 右孩子更大 才选择右孩子
		int biggerSide = leftSide + 1 < heapSize && nums[leftSide] < nums[leftSide + 1]?leftSide + 1 : leftSide;
		biggerSide = nums[i] > nums[biggerSide] ? i : biggerSide;
		//如果三者之中 i位置最大  到此为止了 已经满足堆的条件了
		if (biggerSide == i) {
			break;
		}
		//还需要交换
		std::swap(nums[biggerSide], nums[i]);
		//继续更新 i 和 leftSide 继续下一组
		i = biggerSide;
		leftSide = 2 * i + 1;
	}
}

// pop堆顶 
// 因为只能操作 heapSize这一个变量 和 0位置.. 
// 实现上就是 ：0交换到heapSize-1，然后从0位置开始进行下沉调整 
void pop() {
	//堆顶 pop  heapSize需要减1
	std::swap(nums[--heapSize], nums[0]);
	heapify(0);
}

int top() {
	return  nums[0];
}

// 加入元素
void push(int val) {
	nums[heapSize] = val;
	heapInsert(heapSize++);
}

// 堆排序  
// 给到一个数组 先调整成堆结构
// 自顶上下建堆
// 自底向上建堆
void heapSort() {
	//自顶向下
	//heapSize = n;
	//for (int i = 0; i < n; i++) {
	//	heapInsert(i);
	//}
	

	//自底向上
	heapSize = n;
	// n/2 - 1
	for (int i = n-1; i >=0; i--) {
		heapify(i);
	}
	

	// 堆排序就是逐一复位 堆顶是值最大的元素 放到下标heapSize-1的位置
	// 执行复位操作 直到heapSize变为0 
	while (heapSize > 0) {
		std::swap(nums[0], nums[--heapSize]);
		heapify(0);
	}
}