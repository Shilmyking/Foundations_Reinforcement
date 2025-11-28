

#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<string>
#include<climits>
using namespace std;




class Solution {
public:
    int ans = 0;
    // 左上右下
    const int Move[5]{ 0,-1,0,1,0 };
    int islandPerimeter(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        for (int i = 0; i < n; i++) {
            for (int j=0; j < m; j++) {
                //当前位置 如果是1 考察左和上 就行
                if (grid[i][j] == 1) {
                    ans += 4;
                    //左
                    if (j - 1 >= 0 && grid[i][j-1] == 1) {
                        ans -= 2;
                    }
                    if (i - 1 >= 0 && grid[i - 1][j] == 1) {
                        ans -= 2;
                    }
                }
            }

        }
        return ans;
    }

};