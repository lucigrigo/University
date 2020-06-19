#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ll n, x;
    ll c[(int)2e5] = {};
    cin >> n >> x;
    for(int i = 0; i < n; ++i)
        cin >> c[i];
    ll ans = 0;
    sort(c, c + n);
    for(int i = 0, j = n - 1; i < j;) {
        while(i < j && c[i] + c[j] > x)
            --j;
        if(i >= j)
            break;
        ++ans;
        ++i, --j;
    }
    cout << n-ans;
    return 0;
}
