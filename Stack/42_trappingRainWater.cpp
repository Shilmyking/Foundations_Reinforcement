
#include<string>
#include<vector>

using namespace std;

#if 0
class Solution {
private:
    static const int N = 2e4 + 5;
    const int INF = 0x3f3f3f3f;
    //非常直白的解法：直接遍历找一下当前位置左/右侧的最大高度
    int Left[N];
    int Right[N];
public:
    int trap1(vector<int>& height) {
        int n = height.size();
        //注意边界设置  你也可以设置成-INF  但是就必须特殊处理 1/n-2位置了  所以没必要
        // 这样下面的通式还更好计算结果
        Left[0] = height[0];
        for (int i = 1; i < n; i++) {
            Left[i] = std::max(Left[i - 1], height[i]);
        }
        //一样的思路   求出当前位置右侧最大的
        Right[n - 1] = height[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            Right[i] = std::max(Right[i + 1], height[i]);
        }
        //找到每个位置的左/右最大值，那就再次遍历 收集i位置的数值
        int ans = 0;
        //最左和最右 认为收集不到  边界无穷低
        for (int i = 1; i < n - 1; i++) {
            //取小
            ans += std::min(Left[i] - height[i], Right[i] - height[i]);
        }
        return ans;
    }

private:
    static const int N = 2e4 + 5;
    const int INF = 0x3f3f3f3f;
    int Stack[N];
    int Size = 0;
    //单调栈解法  每个位置找到自己左侧和右侧 比自己大的
    // 栈的组织  从栈底到栈顶  从大到小  遇到比栈顶大的情况 栈顶pop 结算水量
    int trap2(vector<int>& height) {
        int n = height.size();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            //  相等的时候不结算也无法结算
            //   等来到大的值 一起计算
            while (Size > 0 && height[Stack[Size - 1]] < height[i]) {
                int top = Stack[--Size];
                //计算水量的直方图
                int left = Size != 0 ? Stack[Size - 1] : -INF;
                // i - left -1 宽度
                ans += left >= 0 ? (std::min(height[left], height[i]) - height[top])*(i-left-1) : 0;
            }
            Stack[Size++] = i;
        }
        // 最后还可能存在留在栈内的数据
        // 没办法计算 因为右边界找不到 比自己大的  水量都是0
        return ans;
    }

    //根据上面的辅助数组解法，优化掉 造成O(N)空间复杂度的数组
    //为什么能优化掉：左右两侧分别求解Max的过程中， Max只依赖于上一次求解的一项/当前位置的height[i]
    // 而且只需要保存整个过程出现的最大值即可  无需整个数组

    //得到最大值 当前位置的水量如何计算呢？？ 
    // leftMax和rightMax的关系无非三种情况  leftMax > rightMax  leftMax == rightMax  leftMax < rightMax
    //相等的话 左右两侧谁先更新无所谓   
    // leftMax大的话  先更新right
    int trap3(vector<int>& height) {
        int n = height.size();
        int leftMax = height[0], rightMax = height[n - 1];
        int left = 1, right = n - 2;
        while (left < right) {

        }
    }
};

#endif