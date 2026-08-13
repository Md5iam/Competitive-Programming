# Digit Dp

## Resources 
[Video](https://youtu.be/cbgdSX2pXcQ?list=PLWtSipmftM8qbtfj2WkoQ7Z9ZrhCl6rPz&t=8378)


## Question
Given an integer N and an integer X, count how many integers from 0 to N have a sum of digits equal to X.

## Recursive Code
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

## Iterative Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve() {
    int n, x;
    cin >> n >> x;

    string str = to_string(n);
    int len = str.size();

    int dp[11][2][92] = {};

    dp[0][0][0] = 1;
    for (int pos = 0; pos < len; pos++) {
        for (int isSmall = 0; isSmall <= 1; isSmall++) {
            for (int digitSum = 0; digitSum <= 90; digitSum++) {
                if (dp[pos][isSmall][digitSum] == 0) continue;

                int hi = isSmall ? 9 : str[pos] - '0';

                for (int i = 0; i <= hi; i++) {
                    int newIsSmall = isSmall || (i < str[pos] - '0');

                    if (digitSum + i <= 91) {
                        dp[pos + 1][newIsSmall][digitSum + i] +=
                            dp[pos][isSmall][digitSum];
                    }
                }
            }
        }
    }

    cout << dp[len][0][x] + dp[len][1][x] << '\n';
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

## Question 
Count the number of integers between a and b where no two adjacent digits are the same.

# Code 
```
#include <bits/stdc++.h>
using namespace std;
#define int long long

string str;
int dp[20][2][2][12];

// hasStart track the leading zero 
int digDp(int pos, int isSmall, int hasStarted ,int prv) {
    if (pos == str.size()) {
        return 1 ;
    }
    if (dp[pos][isSmall][hasStarted][prv] != -1) {
        return dp[pos][isSmall][hasStarted][prv];
    }
    int lo = 0;
    int hi = str[pos] - '0';
    if (isSmall) {
        hi = 9;
    }
    int res = 0;

    for (int i = lo; i <= hi; i++) {
        int newIsSmall = isSmall || (i < str[pos] - '0');
        if (!hasStarted && i == 0 ){
            res += digDp(pos+1, newIsSmall, 0, 0); 
        }
        else{
            if ( hasStarted && i == prv ) continue;

            res += digDp(pos+1, newIsSmall, 1, i);

        }
    }
    return dp[pos][isSmall][hasStarted][prv] = res;
}

int func( int n ){
    if (n < 0) return 0;
    str = to_string(n);
    memset(dp, -1, sizeof(dp));

    return digDp(0, 0, 0, 0);
}

void solve() {
    int L , R; 
    cin >> L >> R;
    cout << func(R) - func(L - 1) << '\n';
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int tests = 1;
    // cin >> tests;
    for (int tc = 1; tc <= tests; tc++) {
        solve();
    }
    return 0;
}
```
