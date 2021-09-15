//带权并查集
const int N = 1e5 + 10;
int fa[N], d[N];
int find(int x) {
    int par = fa[x];
    fa[x] = find(fa[x]);
    d[x] += d[par];
}

//合并x和y, 并计算路径长度
void merge(int x, int y, int w) {//w代表 x->y 路径长
    int fx = find(x), fy = find(y);
    if (fx != fy) fa[fx] = fy, d[fx] = d[y] - d[x] + w;
    else {
        int dis = d[x] - d[y]; // 如果x和y已经存在关系，dis代表x到y的距离
    }
}

//种类并查集

find(x) --- x的同类
find(x+n) ---
find(x+n+n....) ---

//建立虚点
void merge(int x, int y) {//正常的合并操作
    int fx = find(x), fy = find(y);
    ans[fy] += ans[fx];
    num[fy] += num[fx];
    fa[fx] = fy;
}

void move(int x) {//id[x] 代表x目前的编号
    int fx = find(id[x]);
    ans[fx] -= x;//原来集合中减去x的贡献
    num[fx]--;
    id[x] = ++n;//建立新的节点
    ans[id[x]] = x;
    num[id[x]] = 1;
    fa[id[x]] = id[x];
}

//可撤销并查集
struct Undo_dsu {
    stack<PII> st;
    int fa[N], siz[N];
    void init() {
        while (st.size()) st.pop();
        for (int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
    }
    int find(int x) {return fa[x] == x ? x : find(fa[x]);}
    bool merge(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy) return false;
        if (siz[fx] > siz[fy]) swap(fx, fy), swap(x, y);
        siz[fy] += siz[fx], fa[fx] = fy;
        st.push({fx, fy});
        return true;
    }
    void undo() {
        PII now = st.top();
        fa[now.fi] = now.fi;
        siz[now.se] -= siz[now.fi];
        st.pop();
    }
}dsu;
