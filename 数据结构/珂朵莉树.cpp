#include <iostream>
#include <cstring>
#include <algorithm>
#include <stack>
#include <queue>
#include <map>
#include <vector>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <bitset>
#include <unordered_map>
#include <string>
#include <set>
using namespace std;
#define ACM_LOCAL
#define  IT set<node> ::iterator
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int N = 3e5 + 10;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
typedef pair<int, int> PII;
typedef long long ll;
typedef unsigned long long ull;
int ans;
struct node {
    int l, r;
    mutable ll val;
    node(int L, int R = -1, ll V = 0):l(L), r(R), val(V) {}
    bool operator < (const node &rhs) const {
        return l < rhs.l;
    }
};

set<node> s;
IT split(int pos) {
    IT it = s.lower_bound(node(pos));
    if (it != s.end() && it->l == pos) return it;
    it--;
    int L = it->l, R = it->r;
    ll val = it->val;
    s.erase(it);
    s.insert(node(L, pos-1, val));
    return s.insert(node(pos, R, val)).first;
}

void push_down(int l, int r, ll val) {//区间覆盖操作
    IT itr = split(r+1), itl = split(l);
    s.erase(itl, itr);
    s.insert(node(l, r, val));
}

void add(int l, int r, ll val) {
    IT itr = split(r+1), itl = split(l);
    for (; itl != itr; ++itl) 
        itl->val += val;
}

ll rank(int l, int r, int k) {
    vector<pair<ll, int>> vp;
    IT itr = split(r+1), itl = split(l);
    vp.clear();
    for (; itl != itr; ++itl) {
        vp.push_back(pair<ll, int>(itl->val, itl->r - itl->l + 1));
    }
    sort(vp.begin(), vp.end());
    for (vector<pair<ll,int> >::iterator it = vp.begin(); it != vp.end(); ++it) {
        k -= it->second;
        if (k <= 0) 
            return it->first;
    }
}

ll ksm(ll a, ll b, ll mod) {
    ll res = 1, ans = a % mod;
    while (b) {
        if (b & 1) 
            res = res * ans % mod;
        ans = ans * ans % mod;
        b >>= 1;
    }
    return res;
}

ll sum(int l, int r, int ex, int mod) {
    IT itr = split(r+1), itl = split(l);
    ll res = 0;
    for (; itl != itr; ++itl)
        res = (res + (ll)(itl->r - itl->l + 1) * ksm(itl->val, ll(ex), ll(mod))) % mod;
    return res;
}
