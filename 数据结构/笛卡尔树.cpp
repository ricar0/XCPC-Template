#include <bits/stdc++.h>
#define ACM_LOCAL
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int N = 3e5 + 10, M = 1e5 + 10, INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
int n, m, k;
struct Car_tree {
    int lc[N], rc[N], stk[N], top, val[N];
    void init(int n) {
        for (int i = 0; i <= n; i++) lc[i] = rc[i] = 0;
    }
    int build(int n) {
        int rt;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &val[i]);
            while (top && val[stk[top]] > val[i]) {
                lc[i] = stk[top], top--;
            }
            if (top) rc[stk[top]] = i;
            stk[++top] = i;
        }
        while (top) rt = stk[top--];
        return rt;
    }
}tr;