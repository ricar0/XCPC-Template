#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2 * 1e6 + 9;

int trie[maxn][26]; 
int cntword[maxn];  
int fail[maxn];     
int cnt = 0;

void insertWords(string s) {
    int root = 0;
    for (int i = 0; i < s.size(); i++) {
        int next = s[i] - 'a';
        if (!trie[root][next])
            trie[root][next] = ++cnt;
        root = trie[root][next];
    }
    cntword[root]++;      
}
void getFail() {
    queue <int>q;
    for (int i = 0; i < 26; i++) {      
        if (trie[0][i]) {
            fail[trie[0][i]] = 0;
            q.push(trie[0][i]);
        }
    }
    while (!q.empty()) {
        int now = q.front();
        q.pop();

        for (int i = 0; i < 26; i++) {
            if (trie[now][i]) {

                fail[trie[now][i]] = trie[fail[now]][i];
                q.push(trie[now][i]);
            }
            else
                trie[now][i] = trie[fail[now]][i];
        }
    }
}


int query(string s) {
    int now = 0, ans = 0;
    for (int i = 0; i < s.size(); i++) {    
        now = trie[now][s[i] - 'a'];  
        for (int j = now; j && cntword[j] != -1; j = fail[j]) {
            ans += cntword[j];
            cntword[j] = -1;    
        }
    }
    return ans;
}

int main() {
    int n;
    string s;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s;
        insertWords(s);
    }
    fail[0] = 0;
    getFail();
    cin >> s;
    cout << query(s) << endl;
    return 0;
}


