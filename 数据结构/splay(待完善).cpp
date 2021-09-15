#include <bits/stdc++.h>

#define ACM_LOCAL
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int N = 5e5 + 10, M = 5e5 + 10, INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
int n, m, k, cnt;
int a[N];

struct SplayTree {
     int sz[N], ch[N][2], cnt[N], fa[N], rev[N], val[N], ad[N];
     int tot, rt;
#define rt ch[anc][0]
#define keynode ch[ch[rt][1]][0]
     const int anc = 0;
     void clear(int x) {sz[x] = cnt[x] = ch[x][0] = ch[x][1] = val[x] = ad[N] = 0;}
     void init() {tot = 0, clear(0);}
     int get(int x) {return ch[fa[x]][1] == x;}

     int newnode(int k) {
         int x = ++tot; clear(x);
         val[x] = k;
         sz[x] = cnt[x] = 1;
         return tot;
     }

     void setc(int x, int y, int d) { //基本点操作：设置x的d号儿子为y
         ch[x][d] = y;
         if (y) fa[y] = x;
         if (x) push_up(x);
     }

    void reverse(int x) {
        if (x == 0) return;//Necessary
        swap(ch[x][0], ch[x][1]);
        rev[x] ^= 1;
    }
    void add(int x, int k) {
        if (x == 0)return;
        val[x] += k;
        ad[x] += k;
    }

    void push_up(int x) {
        sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + cnt[x];
    }

    void push_down(int x) {
        if (!x) return;
        if (rev[x]) {
            reverse(ch[x][0]);
            reverse(ch[x][1]);
            rev[x] = 0;
        }
        if (ad[x]) {
            add(ch[x][0], ad[x]);
            add(ch[x][1], ad[x]);
            ad[x] = 0;
        }
    }
    void rotate(int x) {
        int f = fa[x];
        int ff = fa[f];
        bool d = get(x);
        bool dd = get(f);
        setc(f, ch[x][!d], d);	//第一步：把与x原父节点同方向的子树取作原父节点f的子树
        setc(x, f, !d);			//第二步：使与x原父节点同方向的子树连接原父节点f
        setc(ff, x, dd);		//第三步：使得x替代原父节点f，变为新父节点点ff的子树
    }

    void splay(int x, int anc = 0) {//双旋
        if (x == 0)return;
        while (fa[x] != anc) {
            push_down(fa[x]);
            push_down(x);
            if (fa[fa[x]] != anc)rotate(get(x) == get(fa[x]) ? fa[x] : x);
            rotate(x);
        }
    }
    int rank(int k) {//排名
        int x = rt;
        while (1) {
            if (x == 0)return 0;
            if (k == val[x]) { splay(x); return x; }
            bool d = k > val[x];
            x = ch[x][d];
        }
        splay(x);
    }

    void ins(int k) {
        int x = rank(k);
        if (x) {cnt[x]++; sz[x]++; return;}
        int fa = anc; x = rt;
        bool d = 0;
        while (x) {
            fa = x;
            d = k > val[x];
            x = ch[x][d];
        }
        x = newnode(k);
        setc(fa, x, d);
        splay(x);
    }

    int Min(int x) {//子树中最小节点
        push_down(x);
        while (ch[x][0]) x = ch[x][0], push_down(x);
        return x;
    }
    int Max(int x) {//子树中最大节点
        push_down(x);
        while (ch[x][1]) x = ch[x][1], push_down(x);
        return x;
    }
    int kth(int k) {
        ++k;	//这里涉及到区间操作，我们在左右界各添加新节点，因此进入时要++k
        int x = rt;
        while (1) {
            push_down(x);
            if (sz[ch[x][0]] >= k) x = ch[x][0];
            else if (sz[ch[x][0]] + cnt[x] >= k) return x;
            else
            {
                k -= sz[ch[x][0]] + cnt[x];
                x = ch[x][1];
            }
        }
    }
    void del(int x) {
        splay(x);//转到根后便不再需要pushdown()
        if (ch[x][0] == 0)setc(anc, ch[x][1], 0);	//如果没有左子树，则直接把右子树放到树根
        else
        {
            setc(anc, ch[x][0], 0);					//第一步：把左子树放到树根
            splay(Max(ch[x][0]), anc);				//第二步：把左子树最大节点转到树根
            setc(rt, ch[x][1], 1);					//第三步：把右子树接到树根上
        }
    }
    //查找操作：返回树中[l,r]区间段的根节点
    int segment(int l, int r) {
        splay(kth(l - 1), anc);
        splay(kth(r + 1), rt);
        return keynode;
    }
    //分离操作：把[l,r]区间段从树中分离
    int split(int l, int r) {
        int x = segment(l, r); fa[x] = 0;
        setc(ch[rt][1], 0, 0);
        push_up(rt);
        return x;
    }
    //合并操作，把子树x插入到pos位置的右侧
    void inspos(int x, int pos) {
        segment(pos + 1, pos);	//使得pos位于根，pos+1位于根的右子树
        setc(ch[rt][1], x, 0);
        push_up(rt);
    }
    //中序遍历
    void ldr(int x) {
        if (ch[x][0]) ldr(ch[x][0]);
        printf("%d ", x);
        if (ch[x][1]) ldr(ch[x][1]);
    }
    void add(int l, int r, int k) {//区间加
        int x = segment(l, r);
        add(x, k);
        splay(x);
    }

    void reverse(int l, int r) {//区间翻转
        int x = segment(l, r);
        reverse(x);
        splay(x);
    }



}spy;

void solve() {
    int n, opt, x;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef ACM_LOCAL
    freopen("input", "r", stdin);
    freopen("output", "w", stdout);
#endif
    solve();
    return 0;
}