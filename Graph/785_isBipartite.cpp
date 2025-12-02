

#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<string>
#include<climits>
using namespace std;

const int MAXN = 102;
int visited[MAXN];
int que[MAXN*10], l = 0, r = 0;


static const int RED = 1;
static const int BLACK = 2;
// 最开始都是0，然后第一次访问0的时候--->改1，
// 如果相邻节点和这个值一样-->false

void build() {
    memset(visited, 0, sizeof(visited));
    l = r = 0;
}
class Solution {
public:
   
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        build();
        // 一次考察每个节点
        for (int i = 0; i < n; i++) {
            //第一次访问 涂成RED
            if (visited[i] == 0) {
                que[r++] = i;
                visited[i] = RED;
                // 遍历所有相邻节点
                while (l < r) {
                    int node = que[l++];
                    int nextColor = (visited[node] == RED ? BLACK : RED);
                    for (int v : graph[node]) {
                        if (visited[v] == 0) {
                            que[r++] = v;
                            visited[v] = nextColor;
                        }
                        else if (visited[v] != nextColor) {
                            return false;
                        }
                    }
                }

            }
        }
        return true;
    }
};