
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<cstring>

using namespace std;


class Solution {
public:
    static const int INF = 0x3f3f3f3f;
    using PII = pair<int, int>;
    struct Node {
        int row;
        int col;
        int dis;
        Node(int r=-1,int c=-1,int d=INF):row(r),col(c),dis(d){}
        // 必须 const
        bool operator<(const Node& n)const {
            return dis > n.dis;
        }
    };
    const int Move[5]{ 0,-1,0,1,0};
    //一条路径耗费的 体力值 是路径上相邻格子之间 高度差绝对值 的 最大值 决定的
    //返回从左上角走到右下角的最小 体力消耗值
    int minimumEffortPath(vector<vector<int>>& heights) {
        int n = heights.size(), m = heights[0].size();
        vector<vector<bool>>visited(n, vector<bool>(m,false));
        vector<vector<int>>dist(n, vector<int>(m,INF));
        priority_queue<Node>pq;
        pq.push(Node(0, 0, 0));
        dist[0][0] = 0;
        while (!pq.empty()) {
            Node top = pq.top();
            pq.pop();
            if (visited[top.row][top.col]) { continue; }
            if (top.row == n - 1 && top.col == m - 1) {//剪枝
                return top.dis;
            }
            //当这个节点真的pop了  那就是确定答案了
            visited[top.row][top.col] = true;
            for (int k = 0,nx,ny; k < 4; k++) {
                 nx = top.row + Move[k];
                 ny = top.col + Move[k + 1];
                 if (nx >= 0 && nx < n 
                     && ny >= 0 && ny < m
                     &&!visited[nx][ny]) {
                     //如果从x y 到这个节点dist能缩小才有必要去...
                     int Max = std::max({ top.dis,std::abs(heights[top.row][top.col] - heights[nx][ny]) });
                     if (Max < dist[nx][ny]) {
                         //真的更新了 ---->代表更好的结果  --->贪心-->先pop
                         dist[nx][ny] = Max;
                         pq.push({ nx,ny,dist[nx][ny] });
                     }
                 }
            }
        }
        return -1;
    }
};