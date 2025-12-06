
// 地图分析
// 你现在手里有一份大小为 n x n 的 网格 grid
// 上面的每个 单元格 都用 0 和 1 标记好了其中 0 代表海洋，1 代表陆地。
// 请你找出一个海洋单元格，这个海洋单元格到离它最近的陆地单元格的距离是最大的
// 并返回该距离。如果网格上只有陆地或者海洋，请返回 -1。
// 我们这里说的距离是「曼哈顿距离」（ Manhattan Distance）：
// (x0, y0) 和 (x1, y1) 这两个单元格之间的距离是 |x0 - x1| + |y0 - y1| 。
// 测试链接 : https://leetcode.cn/problems/as-far-from-land-as-possible/
#if 0
#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<math.h>

using namespace std;

struct Node {
    int row;
    int col;
    int dis;
    Node(int r = -1, int c = -1, int d = -1) :row(r), col(c), dis(d) {}
};
const int MAXN = 1e2+5;
const int MAXM = 2e4 + 3;
int n, m;

Node que[MAXM];
int l, r;
bool visited[MAXN][MAXN];

void build() {
    l = r = 0;
    memset(visited, false, sizeof(visited));
}
static int Move[5]{ 0,-1,0,1,0 };

class Solution {
public:

    int ans = -1;
    int maxDistance(vector<vector<int>>& grid) {
        n = grid.size(), m = grid[0].size();
        build();
        //先把全部1入队列
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    que[r++] = Node(i, j, 0);
                    visited[i][j] = true;
                }
            }
        }
        //特判
        if (r - l == 0 || r - l == n * m) {
            return -1;
        }
        while (l < r) {
            Node top = que[l++];
            int row = top.row, col = top.col, dis = top.dis;
            ans = std::max(ans, dis);
            for (int k = 0,nx,ny; k < 4; k++) {
                nx = row + Move[k];
                ny = col + Move[k + 1];
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny]) {
                    visited[nx][ny] = true;
                    que[r++] = Node(nx, ny, dis + 1);
                }
            }
        }
        return ans;
    }
};

#endif