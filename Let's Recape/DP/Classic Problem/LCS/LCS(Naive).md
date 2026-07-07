# Recursive Code 
```cpp
#include<bits/stdc++.h>
using namespace std ;

const int N = 3030 ;
string a , b ;
int dp[N][N];

int lcs( int i , int j )
{
    if ( i >= a.size() or j >= b.size()) return 0 ;
    if ( dp[i][j] != -1 ) return dp[i][j];
    int ans = ( i+1 , j );
    ans = max( ans , lcs(i , j+1));
    if ( a[i] ==  b[j])
    {
        ans = max ( ans , lcs( i+1 , j+1)+1);
    }
    return dp[N][N] = ans ;

}

void path( int i , int j )
{
    if ( i >= a.size() || j >= b.size()) return ;
    if ( a[i] == b[j])
    {
        cout << a[i];
        path( i+1 , j+1);
    }
    int x = lcs(i+1 , j);
    int y = lcs(i , j+1);

    if ( x >= y )
    {
      path(i+1 , j);
    }
    else
    {
       path(i, j+1);
    }
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>> a >> b ;
    memset ( dp , -1 , sizeof(dp));
    cout << lcs( 0 , 0 ) << '\n';

    return 0 ;
}
```

# Iterative Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
#include "trace.cpp"
#else
#define dbg(...)
#endif
void solve() {
    int n ; cin >> n ;
    vector<int>a(n) , b(n);
    for ( int i = 0 ; i < n ; i++ ){
        cin >> a[i];
    }
    for ( int i = 0 ; i < n ; i++ ){
        cin >> b[i];
    }
    vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
    for ( int i = 1 ; i <= n ; i++ ){
        for ( int j = 1 ; j <= n ; j++ ){
            if ( a[i-1] == b[j-1]){
                dp[i][j] = 1 + dp[i-1][j-1];
            }
            else{
                dp[i][j] = max ( dp[i-1][j] , dp[i][j-1]);
            }
        }
    }
    cout << dp[n][n] << '\n';
}
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int tests = 1;
    cin >> tests;
    for (int tc = 1; tc <= tests; tc++) {
        solve();
    }
    return 0;
}
```
