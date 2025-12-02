
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<cstring>

using namespace std;

class Solution {
public:

    const int INF = 0x3f3f3f3f;
    //其中 flights[i] = [fromi, toi, pricei] ，表示该航班都从城市 fromi 开始，以价格 pricei 抵达 toi。
    //最多经过 k 站中转的路线，使得从 src 到 dst 的 价格最便宜 ，并返回该价格。 如果不存在这样的路线，则输出 -1
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<int>dist(n+1,INF);//0-based
        dist[src] = 0;
        // 最多k次中转 ---> k+1 次松弛  
        // 要限制一下每一次遍历过程中多次松弛
        vector<int>nexts;
        for (int i = 0; i <= k; i++) {
            nexts = dist;
            // 考察每一条边
            for (auto& edge : flights) {
                int from = edge[0], to = edge[1], weight = edge[2];
                //1)需要能够到达 from节点 
                //2）如果从from点出发到达to点 的距离能够更小 -->更新  一次松弛
                if (nexts[from] != INF && nexts[to] > dist[from] + weight) {
                    nexts[to] = dist[from] + weight;
                }
            }
            dist = nexts;
        }
        return dist[dst] == INF ? -1 : dist[dst];
    }
};