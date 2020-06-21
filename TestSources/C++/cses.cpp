#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int mxN = 2e4;

ll n, m, ans;
char v[mxN][mxN];
string minpath;
int mindepth = INT_MAX;

void dfs(int i, int j, string path = "", int depth = 0) {
	if(i < 0 || i >= n || j < 0 || j >= m || v[i][j] == '#')
		return;

	if(v[i][j] == 'B') {
		if(depth < mindepth) {
			mindepth = depth;
			minpath = path;
		}
		return;
	}

	v[i][j] = '#';
	dfs(i - 1, j, path + 'U', depth + 1);
	dfs(i + 1, j, path + 'D', depth + 1);
	dfs(i, j - 1, path + 'L', depth + 1);
	dfs(i, j + 1, path + 'R', depth + 1);
	v[i][j] = '.';
}

int main() {
	cin >> n >> m;

	for(int i = 0; i < n; ++i) 
		for(int j = 0; j < m; ++j)
			cin >> v[i][j];

	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if(v[i][j] == 'A') {
				dfs(i, j);
			}
		}
	}

	if(minpath == "") {
		cout << "NO";
	} else {
		cout << "YES" << endl << mindepth << endl << minpath;
	}
	return 0;
}
