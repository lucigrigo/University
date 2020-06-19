#include <bits/stdc++.h>
using namespace std;
#define ll long long

int ans;
string s;
int vis[7][7];

void dfs(int i, int j, int step = 0) {
    if(i == 6 && j == 6) {
        if(step == 48)
            ++ans;
        return;
    }
    vis[i][j] = 1;
    if(s[step] == '?' || s[step] == 'L') {
        if(j > 0 && ! vis[i][j - 1])
            dfs(i, j - 1, step + 1);
    }
    if(s[step] == '?' || s[step] == 'D') {
        if(i < 6 && ! vis[i + 1][j])
            dfs(i + 1, j, step + 1);
    }
    if(s[step] == '?' || s[step] == 'R') {
        if(j < 6 && ! vis[i][j + 1])
            dfs(i, j + 1, step + 1);
    }
    if(s[step] == '?' || s[step] == 'U') {
        if(j > 0 && ! vis[i - 1][j])
            dfs(i - 1, j, step + 1);
    }
    vis[i][j] = 0;
}

int main() {
    cin >> s;
    dfs(0, 0);
    cout << ans;
    return 0;
}
