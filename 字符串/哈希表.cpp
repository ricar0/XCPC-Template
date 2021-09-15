#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
const int p = 99991;

int h[N], Next[N], n, m, snow[N][6], cnt;

int H(int *a) {
    int cal = 0, mul = 1;
    for (int i = 0; i < 6; i++) {
        cal = (cal + a[i]) % p;
        mul = 1ll * mul * a[i] % p;
    }
    return (cal + mul) % p;
}

bool insert(int *a) {
    int val = H(a);
    for (int i = h[val]; i; i = Next[i]) {
        //if (equal(snow[i], a)) return 1;
    }
    ++cnt;
    memcpy(snow[cnt], a, 6*sizeof(int));
    Next[cnt] = h[val];
    h[val] = cnt;
    return 0;
}