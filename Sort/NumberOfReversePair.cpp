#include<vector>
#include<iostream>
#include<queue>
#include<algorithm>
#include<cstring>
#include<list>
#include<vector>
#include<string>
#include<map>
#include<unordered_map>
#include<set>
#include<unordered_set>

using namespace std;
#define int long long 
#define endl "\n"

/*
逆序对数量
给定一个长度为n的数组arr
如果 i < j 且 arr[i] > arr[j]
那么(i, j)就是一个逆序对
求arr中逆序对的数量
1 <= n <= 5 * 10 ^ 5
1 <= arr[i] <= 10 ^ 9
测试链接： https ://www.luogu.com.cn/problem/P1908
*/

const int N = 5e5 + 5;
