
#include<iostream>
#include<algorithm>
#include<queue>

#include<vector>
#include<cstring>

using namespace std;

class Solution {
public:
    //存储 节点 + dist
    using PII = pair<int, int>;
    // 当让也可以不使用这个 方法
    // PII 默认优先比较 前一个first  后second
    //struct comparator {
    //    //大根堆变小根堆  反一下
    //    bool operator()(const PII& p1, const PII& p2) {
    //        return p1.second > p2.second;
    //    }
    //};

    const int INF = 0x3f3f3f3f;
    struct Edge {
        int start;
        int end;
        int weight;
        Edge(int s = -1, int e = -1, int w = -1) :start(s), end(e), weight(w) {}
        bool operator<(const Edge& e) {
            return weight > e.weight;//默认为大根堆，这里反一下 改为小根堆
        }
    };

    // 注意 PII first 存储dist  second 存储节点编号
    int compute(const  vector<vector<Edge>>&Graph, priority_queue<PII, vector<PII>, std::greater<PII>>&pq, vector<int>&dist, vector<bool>&visited) {
        while (!pq.empty()) {
            PII top = pq.top();
            pq.pop();
            int dis = top.first, v = top.second;
            if (visited[v]) {
                continue;
            }
            visited[v] = true;
            for (auto& edge : Graph[v]) {
                int to = edge.end;
                //如果没有从堆上pop出去过 + 能更新当前的dist
                if (!visited[to] && dist[to] > dis + edge.weight) {
                    dist[to] = dis + edge.weight;
                    pq.push({ dist[to],to });
                }
            }
        }
        int ans = 0;
        for (int i = 1; i <= dist.size() - 1; i++) {
            if (dist[i] == INF) {
                return -1;
            }
            ans = std::max(ans, dist[i]);
        }
        return ans;
    }
    // k出发 
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        priority_queue<PII,vector<PII>,std::greater<PII>>pq;
        vector<int>dist(n + 1,INF);
        vector<bool>visited(n + 1,false);
        vector<vector<Edge>>Graph(n+1);//邻接表
        //有向图
        for (int i = 0; i < times.size(); i++) {
            int u = times[i][0], v = times[i][1], w = times[i][2];
            Graph[u].push_back(Edge(u, v, w));
        }
        // 初始化
        pq.push({ 0,k });
        dist[k] = 0;
        return compute(Graph, pq, dist, visited);
    }
};