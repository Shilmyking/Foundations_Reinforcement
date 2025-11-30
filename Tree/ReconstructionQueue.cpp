
// 重建队列
// 一共n个人，每个人有(a, b)两个数据，数据a表示该人的身高
// 数据b表示该人的要求，站在自己左边的人中，正好有b个人的身高大于等于自己的身高
// 请你把n个人从左到右进行排列，要求每个人的要求都可以满足
// 返回其中一种排列即可，本题的数据保证一定存在这样的排列
// 测试链接 : https://leetcode.cn/problems/queue-reconstruction-by-height/

#include <iostream>
#include <algorithm>
#include <climits>
#include <cstring>
#include<vector>

using namespace std;


const int MAXN = 2001;