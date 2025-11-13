
#include<string>
#include<vector>

using namespace std;

#if 0
class Solution {
    static const int N = 2e4 + 5;
    const int INF = 0x3f3f3f3f;
    //非常直白的解法：直接遍历找一下当前位置左/右侧的最大高度
    int Left[N];
    int Right[N];
public:
    int trap(vector<int>& height) {
        int n = height.size();
        //注意边界设置  你也可以设置成-INF  但是就必须特殊处理 1/n-2位置了  所以没必要
        // 这样下面的通式还更好计算结果
        Left[0] = height[0];
        for (int i = 1; i < n; i++) {
            Left[i] =std::max(Left[i-1], height[i]);
        }
        //一样的思路   求出当前位置右侧最大的
        Right[n - 1] = height[n-1];
        for (int i = n - 2; i >= 0; i--) {
            Right[i] = std::max(Right[i+1], height[i]);
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
};

class Solution {
public:
    //根据上面的辅助数组解法，优化掉 造成O(N)空间复杂度的数组
    //为什么能优化掉：左右两侧分别求解Max的过程中， Max只依赖于上一次求解的一项/当前位置的height[i]
    // 而且只需要保存整个过程出现的最大值即可  无需整个数组
    
    //得到最大值 当前位置的水量如何计算呢？？ 
    // leftMax和rightMax的关系无非三种情况  leftMax > rightMax  leftMax == rightMax  leftMax < rightMax
    //相等的话 左右两侧谁先更新无所谓   
    // leftMax大的话  先更新right
    int trap(vector<int>& height) {
        int n = height.size();
        int leftMax = height[0], rightMax = height[n - 1];
        int left = 1, right = n - 2;
        while (left < right) {

        }
    }
};
#endif