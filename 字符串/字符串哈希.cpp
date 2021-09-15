#include <bits/stdc++.h>
using namespace std;
const int N = 5e6 + 10;
char s[N];
unsigned long long f[N], p[N]; 
int n, m;
int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    p[0] = 1;
    for (int i = 1; i <= n; i++) {
        f[i] = f[i-1] * 1331 + (s[i] - 'a' + 1);
        p[i] = p[i-1] * 1331;
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        int l1, l2, r1, r2;
        scanf("%d %d %d %d", &l1, &r1, &l2, &r2);
        if (f[r1] - f[l1 - 1] * p[r1 - l1 + 1] == f[r2] - f[l2 - 1] * p[r2 - l2 + 1]) printf("Yes\n");
        else printf("No\n");
    }
}

/*

H(T) = H(S + T) - H(S) - p ^ (length(T)) 

*/