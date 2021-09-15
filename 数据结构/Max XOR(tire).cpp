#include <bits/stdc++.h>
using namespace std;
const int N = 100010;
const int M = 3000010;
int n, a[N];
int trie[M][2];
int cnt;
void insert(int x){
    int p = 0;
    for (int i = 30; ~i; i--){
        int w = x >> i & 1;
        if (!trie[p][w]) trie[p][w] = ++cnt;
        p = trie[p][w];
    }    
}

int query(int x){
    int p = 0;
    int res = 0;
    for (int i = 30; ~i; i--){
        int w = x >> i & 1;
        
        if (trie[p][w ^ 1]){
            res += (1 << i);
            p = trie[p][w ^ 1];
        }
        else p = trie[p][w];
    }
    return res;
}

