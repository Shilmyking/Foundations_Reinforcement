
// 岛屿数量
// 给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量
// 岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成
// 此外，你可以假设该网格的四条边均被水包围
// 测试链接 : https://leetcode.cn/problems/number-of-islands/


#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<string>
#include<climits>
using namespace std;



class Solution {
    //并查集
    static const int MAXN = 1e5;
    int fa[MAXN];
    int n, m;
    int sets;

    int index(int i, int j) {
        return i * m + j;
    }

    int find(int x) {
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    }

    void build(const vector<vector<char>>& grid) {
        sets = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '1') {
                    int idx = index(i, j);
                    fa[idx] = idx;
                    sets++;//初始每个位置都是一个集合
                }
            }
        }
    }

    // 传入index
    void Union(int x, int y) {
        int fx = find(x), fy = find(y);

        if (fx != fy) {
            fa[fx] = fy;
            sets--;
        }

    }

    //左和上
    const int Move[3]{ 0,-1,0 };
public:
    int numIslands(vector<vector<char>>& grid) {
        n = grid.size(), m = grid[0].size();
        build(grid);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '1') {

                    //先左后上
                    for (int k = 0, nx, ny; k < 2; k++) {
                        nx = i + Move[k];
                        ny = j + Move[k + 1];
                        //边界
                        if (nx >= 0 && ny >= 0 && grid[nx][ny] == '1') {
                            int id = index(i, j), idx = index(nx, ny);
                            Union(id, idx);
                        }
                    }

                }//只有当前位置 为'1'才去考虑
            }
        }
        return sets;
    }

};