#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
typedef long long ll;
const int MAX = 1e6 + 10;
char s1[MAX], s2[MAX];
int Next[MAX];
int len1, len2;
void get_Next() {
	int t1 = 0, t2;
	Next[0] = t2 = -1;
	while (t1 < len1) {
		if (t2 == -1 || s2[t1] == s2[t2])
			Next[++t1] = ++t2;
		else t2 = Next[t2];
	}
}

void KMP() {
	int t1 = 0, t2 = 0;
	while (t1 < len1) {
		if (t2 == -1 || s1[t1] == s2[t2])
			t1++, t2++;
		else
			t2 = Next[t2];
		if (t2 == len2) {
			cout << t1 - len2 + 1 << endl;
			t2 = Next[t2];
		}
	}
}

int main() {
	cin >> s1 >> s2;
	len1 = strlen(s1);
	len2 = strlen(s2);
	get_Next();
	KMP();
	for (int i = 1; i <= len2; i++)
		cout << Next[i] << " ";
	return 0;
}