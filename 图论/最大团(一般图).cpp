const int N = 200 + 5;
int n;
int G[N][N];
int cnt[N];//cnt[i]为>=i的最大团点数
int group[N];//最大团的点
int vis[N];//记录点的位置
int res;//最大团的数目
bool dfs(int pos, int num) {//num为已取的点数
    for (int i = pos + 1; i <= n; i++) {
        if (cnt[i] + num <= res)//剪枝，若取i但cnt[i]+已经取了的点数仍<ans
            return false;

        if (G[pos][i]) {//与当前团中元素比较，取Non-N(i)
            int j;
            for (j = 0; j < num; j++)
                if (!G[i][vis[j]])
                    break;
            if (j == num) {//若为空，则皆与i相邻，则此时将i加入到最大团中
                vis[num] = i;
                if (dfs(i, num + 1))
                    return true;
            }
        }
    }

    if (num > res) {//每添加一个点最多使最大团数+1,后面的搜索就没有意义了
        res = num;//最大团中点的数目
        for (int i = 1; i <= num; i++)//最大团的元素
            group[i] = vis[i - 1];
        return true;
    }
    return false;
}

void maxClique() {
    res = -1;
    for (int i = n; i >= 1; i--) {//枚举所有点
        vis[0] = i;
        dfs(i, 1);
        cnt[i] = res;
    }
}
