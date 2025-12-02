

#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<string>
#include<climits>
using namespace std;

static const int Move[5]{ 0,-1,0,1,0 };
class Solution {
public:
    int same;
    int colors;
    int n, m;
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        n = image.size(), m = image[0].size();
        same = image[sr][sc];
        colors = color;
        if (colors == same) {
            return image;
        }
        //如果 colors == same 直接return  否则一致递归死循环
        dfs(image, sr, sc);
        return image;
    }

    void dfs(vector<vector<int>>& image, int i, int j) {
        //如果当前颜色和 same一致 涂色为color  然后递归去找
        if (i < 0 || i >= n || j < 0 || j >= m || image[i][j] != same) {
            return;
        }
        image[i][j] = colors;
        for (int k = 0; k < 4; k++) {
            dfs(image, i + Move[k], j + Move[k + 1]);
        }
    }
};