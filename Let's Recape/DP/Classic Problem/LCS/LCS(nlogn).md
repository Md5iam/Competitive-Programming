# Iterative code 
## works when both arrays are permutations / all values are unique.
```cpp
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
#include "trace.cpp"
#else
#define dbg(...)
#endif

void solve() {
    int n; cin >> n;
    vector<int> a(n), b(n);
    vector<int> pos(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pos[a[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    vector<int> lis;
    for (int i = 0; i < n; i++) {
        int x = pos[b[i]];

        auto it = lower_bound(lis.begin(), lis.end(), x);
        if (it == lis.end()) {
            lis.push_back(x);
        } else {
            *it = x;
        }
    }
    int lcs = lis.size();
    cout << lcs << '\n';
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
