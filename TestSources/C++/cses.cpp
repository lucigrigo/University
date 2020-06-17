#include <bits/stdc++.h>

using namespace std;

#define ll long long

int main() {
	ll n, s = 0;
	cin >> n;
	int v[21];
	for(int i = 0; i < n; ++i) {
		cin >> v[i], s += v[i];
	}
	ll ans = 0;
	for(int i = 0; i < 1<<n; ++i) {
		ll ls = 0;
		for(int j = 0; j < n; ++j) {
			if(i>>j&1) {
				ls += v[j];
			}
		}
		if(ls <= s / 2) {
			ans = max(ans, ls);
		}
	}
	cout << s - 2 * ans;
    return 0;
}
