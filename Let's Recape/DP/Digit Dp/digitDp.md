# Digit Dp

## Question
Given an integer N and an integer X, count how many integers from 0 to N have a sum of digits equal to X.

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

string str;
int x;
int dp[11][2][92];

int func(int pos, int isSmall, int digitSum) {
    if (pos == str.size()) {
        return digitSum == x;
    }
    if (dp[pos][isSmall][digitSum] != -1) {
        return dp[pos][isSmall][digitSum];
    }
    int lo = 0;
    int hi = str[pos] - '0';
    if (isSmall) {
        hi = 9;
    }
    int res = 0;

    for (int i = lo; i <= hi; i++) {
        int newIsSmall = isSmall || (i < str[pos] - '0');
        int val = func(pos + 1, newIsSmall, digitSum + i);
        res += val;
    }
    return dp[pos][isSmall][digitSum] = res;
}

void solve() {
    int n;
    cin >> n >> x;
    str = to_string(n);
    memset(dp, -1, sizeof(dp));
    cout << func(0, 0, 0) << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
```