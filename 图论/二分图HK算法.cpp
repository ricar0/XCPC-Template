#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <queue>
#include <stack>
#include <string>
#include <set>
#include <map>
#include <bitset>
using namespace std;
#define ACM_LOCAL

const int N = 3e3 + 5;
const int INF = 0x3f3f3f3f;
typedef pair<int, int> PII;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

int h[N], cnt, n;  //存图
int dx[N], dy[N], dis;                 //左边部分距离，右边部分距离，记录右边部分没有被匹配过的点的最大距离
int machx[N], machy[N];            //左边部分点匹配右边点，左边部分的点个数，右边部分点匹配左边的点
bool vist[N];

struct edge {
    int to, next;
}e[N * N];

void add(int u, int v) {
    e[cnt].to = v;
    e[cnt].next = h[u];
    h[u] = cnt++;
}

bool searchpath() {//找有没有增广路
    queue<int>q;
    dis = INF;
    memset(dx, -1, sizeof(dx));
    memset(dy, -1, sizeof(dy));

    for (int i = 1; i <= n; i++)
        if (machx[i] == -1)
            q.push(i), dx[i] = 0;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (dx[u] > dis)
            break;
        for (int i = h[u]; i != -1; i = e[i].next) {
            int v = e[i].to;
            if (dy[v] == -1) {
                dy[v] = dx[u] + 1;
                if (machy[v] == -1)
                    dis = dy[v];
                else {
                    dx[machy[v]] = dy[v] + 1;
                    q.push(machy[v]);
                }
            }
        }
    }
    return dis != INF;
}
bool findroad(int u) {
    for (int i = h[u]; i != -1; i = e[i].next) {
        int v = e[i].to;
        if (!vist[v] && dy[v] == dx[u] + 1) {
            vist[v] = 1;
            if (machy[v] != -1 && dy[v] == dis)
                continue;
            if (machy[v] == -1 || findroad(machy[v])) {
                machy[v] = u; machx[u] = v;  return true;
            }
        }
    }
    return false;
}
int MaxMatch() {
    int ans = 0;
    memset(machx, -1, sizeof(machx));
    memset(machy, -1, sizeof(machy));
    while (searchpath()) {
        memset(vist, 0, sizeof(vist));
        for (int i = 1; i <= n; i++)
            if (machx[i] == -1)
                ans += findroad(i);
    }
    return ans;
}