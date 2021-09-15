#include <bits/stdc++.h>
using namespace std;
const int N = 1000010;
int q[N], a[N], n, k;
void deque_max() {
    int hh = 1, tt = 0;
    for (int i = 1; i <= n; i ++) {
        while(hh <= tt && q[hh] + k <= i) hh ++;
        while(hh <= tt && a[q[tt]] < a[i]) tt --;
        q[++tt] = i;
        if (i >= k) cout << a[q[hh]] << " ";
    }
}

void deque_min() {
    int hh = 1, tt = 0;
    for (int i = 1; i <= n; i ++) {
        while(hh <= tt && q[hh] + k <= i) hh ++;
        while(hh <= tt && a[q[tt]] > a[i]) tt --;
        q[++tt] = i;
        if (i >= k) cout << a[q[hh]] << " ";
    }
}
