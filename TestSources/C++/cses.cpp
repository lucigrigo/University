#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;

    if(n == 1)
        cout << 1;
    else if(n <= 3)
        cout << "NO SOLUTION";
    else {
        int m = n / 2 + 1;
        int a = 1;

        while(a <= n / 2 || m <= n) {
            cout << a << " " << m << " ";
            ++a; ++m;
        }
    }
    return 0;
}
