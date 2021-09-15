/*

void solve() {
    while (cin >> a[++n]);
    n--;
    for (int i = 1; i <= n; i++) {
        if (a[i] > b[len1]) b[++len1] = a[i];
        else {
            int pos = lower_bound(b + 1, b + len1 + 1, a[i]) - b;
            b[pos] = a[i]; 
        }
    }
    
    reverse(a+1, a+n+1);
    for (int i = 1; i <= n; i++) {
        if (a[i] >= b[len2]) b[++len2] = a[i];
        else {
            int pos = upper_bound(b + 1, b + len2 + 1, a[i]) - b;
            b[pos] = a[i]; 
        }
    }
    cout << len2 << endl;
    cout << len1 << endl;
}


*/