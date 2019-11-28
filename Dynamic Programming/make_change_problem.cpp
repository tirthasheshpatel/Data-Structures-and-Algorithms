/**
 * Problem statement: You have a sequence of n coins <a_0, a_1, a_2, ... , a_n>
 *                    where a_0 = 1 and a_0 < a_1 < a_2 < ... < a_n.
 *                    You have to find the minimum number of coins required to make
 *                    a change of `m` coins.
 *                    Assume each coin can be used infinitely many times.
 * Solution: MC(n) = min( MC(n-a_0), MC(n-a_1) ,... MC(n-a_n) ) + 1.
 */


#include <iostream>
#include <algorithm>

using namespace std;

#define int long long

int arr[100001], dp[100001];

signed main()
{
    int n;
    cin >> n;
    for(int i=0;i<n;i++) cin >> arr[i];
    int m;
    cin >> m;
    for(int i=1;i<=m;i++) {
        int __min = LLONG_MAX;
        for(int j=0;j<n;j++) {
            if(arr[j]>i) continue;
            __min = min(__min, dp[i-arr[j]]+1);
        }
        dp[i] = __min;
    }
    cout << dp[m] << endl;
}