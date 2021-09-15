struct LinerBase {
    static const int MAX_BIT = 61;
    bool isZero; ll num[N], tmp[N];
    LinerBase() {
        memset(num, 0, sizeof num);
        memset(tmp, 0, sizeof tmp);
    }
    void insert(ll x) {
        for (int i = MAX_BIT; i >= 0; i--) {
            if (!(x & (1ll << i))) continue;
            if (num[i]) {
                x ^= num[i];
            } else {
                num[i] = x;
                return;
            }
        }
        isZero = true;
    }
    int countNumber() {
        int cnt = 0;
        for (int i = 0; i <= MAX_BIT; i++) if (num[i] & (1ll << i)) cnt++;
        return cnt;
    }
    void rebuild() {
        int cnt = 0;
        for (int i = MAX_BIT; i >= 0; i--)
            for (int j = i-1; j >= 0; j--)
                if (num[i] & (1ll << j)) num[i] ^= num[j];

        for (int i = 0; i <= MAX_BIT; i++) {
            if (num[i]) tmp[cnt++] = num[i];
        }
    }
    ll qryKth(ll k) {
        if (isZero) k--;
        if (!k) return 0;
        int cnt = countNumber(); ll ans = 0;
        if (k >= (1ll << cnt)) return -1;
        for (int i = 0; i < cnt; i++) {
            if (k & (1ll << i)) ans ^= tmp[i];
        }
        return ans;
    }
}lb;
