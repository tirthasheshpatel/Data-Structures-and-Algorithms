/** Problem Statement:  John have n blocks of length l[i], width w[i], height h[i].
 *                      John can put a block `j` on top of block `i` iff
 *                      l[j] < l[i] and w[j] < w[i]. Your goal is to help John
 *                      make a tower of blocks of maximum height.
 */

#include <iostream>
#include <algorithm>
#define int long long
#define INF LLONG_MAX
#define NEG_INF LLONG_MIN
#define SIZE 100001
using namespace std;

int lwh[SIZE][3], dp_h[SIZE], used[SIZE];

signed main()
{
    int n, dp_l[SIZE]={INF}, dp_w[SIZE] = {INF};
    cin >> n;
    for(int i=0;i<n;i++) {
        int l,w,h;
        cin >> l >> w >> h;
        lwh[i][0] = l;
        lwh[i][1] = w;
        lwh[i][2] = h;
    }

    for(int i=1;i<=n;i++) {
        int __max = NEG_INF;
        int temp, ll=dp_l[i-1], ww=dp_w[i-1];
        int prev_j = 0;
        for(int j=0;j<n;j++) {
            temp = lwh[j][2] + dp_h[i-1];
            if(temp>__max&&!used[j]&&lwh[j][0]<ll&&lwh[j][1]<ww) {
                used[j]=1;
                if(prev_j!=j) used[prev_j] = 0;
                __max = temp;
                prev_j = j;
            }
        }
        dp_l[i] = lwh[prev_j][0];
        dp_w[i] = lwh[prev_j][1];
        dp_h[i] = __max;
    }
    cout << "Maximum height: " << dp_h[n] << endl;
    for(int i=1;i<=n;i++) {
        cout << dp_l[i] << " " << dp_w[i] << endl;
    }
}