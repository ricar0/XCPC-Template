#include <bits/stdc++.h>
using namespace std;
const int N = 1000 + 5;
typedef long long ll;
int c[N][N];

//单点修改，区间查询
int lowbit(int x) {return x & -x;}
void add(int x, int y, int v) {
	for (int i = x; i <= N; i += lowbit(i))
		for (int j = y; j <= N; j += lowbit(j)) 
			c[i][j] += v;
}

ll query(int x, int y) {
	ll res = 0;
	for (int i = x; i > 0; i -= lowbit(i)) 
		for (int j = y; j > 0; j -= lowbit(j))
			res += c[i][j];
	return res;
}

//区间修改，单点查询
void add_s(int x1, int y1, int x2, int y2, int v) {
	add(x2+1, y2+1, v);
	add(x1, y1, v);
	add(x1, y2+1, -v);
	add(x2+1, y1, -v);
}
//区间修改，区间查询
void add(int x,int y,int v) {
    for(int i = x; i<= n;i += lowbit(i))
        for(int j=y;j<=m;j+=lowbit(j)) {
            t1[i][j] += v;
            t2[i][j] += v*x;
            t3[i][j] += v*y;
            t4[i][j] += v*x*y;
        }
}
void modify(int x1,int y1,int x2,int y2,int v) {
    add(x1,y1,v);
    add(x1,y2+1,-v);
    add(x2+1,y1,-v);
    add(x2+1,y2+1,v);
}
int ask(int x, int y) {
    int res = 0;
    for(int i = x;i;i -= lowbit(i))
        for(int j=y;j;j -= lowbit(j))
            res += (x+1)*(y+1)*t1[i][j]-(y+1)*t2[i][j]-(x+1)*t3[i][j]+t4[i][j];
    return res;
}
int query(int x1,int y1,int x2,int y2) {
    return ask(x2,y2)-ask(x2,y1-1)-ask(x1-1,y2)+ask(x1-1,y1-1);
}
