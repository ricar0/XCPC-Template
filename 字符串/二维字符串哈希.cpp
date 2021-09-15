#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

typedef unsigned long long ULL;

const int N = 1010, M = N * N, P = 131;

int n, m, a, b;
ULL hashv[N][N], p[M];
char str[N];

ULL calc(ULL f[], int l, int r)
{
    return f[r] - f[l - 1] * p[r - l + 1];
}

int main()
{
    scanf("%d%d%d%d", &n, &m, &a, &b);

    p[0] = 1;
    for (int i = 1; i <= n * m; i ++ ) p[i] = p[i - 1] * P;

    for (int i = 1; i <= n; i ++ )
    {
        scanf("%s", str + 1);
        for (int j = 1; j <= m; j ++ ) hashv[i][j] = hashv[i][j - 1] * P + str[j] - '0';
    }

    unordered_map<ULL, int> S;
    for (int i = b; i <= m; i ++ )
    {
        ULL s = 0;
        int l = i - b + 1, r = i;
        for (int j = 1; j <= n; j ++ )
        {
            s = s * p[b] + calc(hashv[j], l, r);
            if (j - a > 0) s -= calc(hashv[j - a], l, r) * p[a * b];
            if (j >= a) S[s] = 1;
        }
    }

    int Q;
    scanf("%d", &Q);
    while (Q -- )
    {
        ULL s = 0;
        for (int i = 0; i < a; i ++ )
        {
            scanf("%s", str);
            for (int j = 0; j < b; j ++ ) s = s * P + str[j] - '0';
        }
        if (S[s]) puts("1");
        else puts("0");
    }

    return 0;
}

