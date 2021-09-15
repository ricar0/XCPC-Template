#include <bits/stdc++.h>
using namespace std;
const int N = 10010;
int match[N], vis[N];
int n, m, ans;
vector<int> g[N];

bool dfs(int x) {
    for (auto v : g[x]) {
        if (!vis[v]) {
            vis[v] = 1;
            if (!match[v] || dfs(match[v])) {
                match[v] = x;
                return true;
            }
        }
    }
    return false;
}
