#include <bits/stdc++.h>
using namespace std;
const int N = 100010;
int tire[26*N][26], n, m;
int cnt, level[N*26];

void insert(string s) {
    int p = 0;
    for (int i = 0; i < s.length(); i ++) {
        int v = s[i] - 'a';
        if (!tire[p][v]) tire[p][v] = ++cnt;
        p = tire[p][v];
    }
    level[p] ++;
}

int query(string s) {
    int p = 0;
    int res = 0;
    for (int i = 0; i < s.length(); i ++) {
        p = tire[p][s[i]-'a'];
        if (!p) break;
        res += level[p];
    }
    return res;
} 
