#include<bits/stdc++.h>
using namespace std;
const int N=5e5+1000;
int n,m,x,y;
int a[N];
struct Node {
	int l,r; 
	int sum;
	int lmax;
	int rmax; 
	int tmax;
}tr[N<<2]; 

void push_up(Node &u,Node &l,Node &r) {
	u.sum=l.sum+r.sum;
	u.lmax=max(l.lmax,l.sum+r.lmax);
	u.rmax=max(r.rmax,r.sum+l.rmax);
	u.tmax=max(max(l.tmax,r.tmax),l.rmax+r.lmax);
}

void push_up(int u) {
	push_up(tr[u],tr[u<<1],tr[u<<1|1]);
} 
 
void build(int u,int l,int r) {
    tr[u].l = l, tr[u].r = r;
 	if(l==r) {
 		tr[u]={l,r,a[r],a[r],a[r],a[r]};
 		return ;
	}
	int mid = (l+r)>>1;
	
	build(u<<1, l, mid);
	build(u<<1|1, mid+1, r);
	push_up(u);
	
}
void  update(int u,int x,int v) {
 	if(tr[u].l==tr[u].r) {
 		tr[u]={x,x,v,v,v,v};
 		return ;
	}
	int mid = (tr[u].l + tr[u].r)>>1;
	if(x<=mid) update(u<<1, x, v);
	else update(u<<1|1 , x, v);
	push_up(u);
}
Node query(int u,int ql,int qr) {
 	if(ql<=tr[u].l&&qr>=tr[u].r) return tr[u];
 	int mid=tr[u].l+tr[u].r>>1;
 	if(qr<=mid) return query(u<<1,ql,qr);
 	else if(ql>mid) return query(u<<1|1,ql,qr);
	else
	{
		auto left=query(u<<1,ql,qr);
		auto right=query(u<<1|1,ql,qr);
		Node res;
		push_up(res,left,right);
		return res;
	} 
}

