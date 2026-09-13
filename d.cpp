#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <bitset>

using namespace std;

void solve() {
    int n;
    if (!(cin >> n)) return;
    vector<long long> a(n), b(n), c(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    for (int i = 0; i < n; i++) c[i] = b[i] - a[i];

    int k = 0;
    long long neg = 0, pos = 0;
    vector<int> w;
    for (int i = 0; i < n - 1; i++) {
        long long d = c[i + 1] - c[i];
        if (d != 0) {
            k++;
            if (d < 0) neg += d;
            else pos += d;
            w.push_back(abs(d));
        }
    }

    long long t = -c[0];
    if (t < neg || t > pos) {
        cout << k + 1 << "\n";
        return;
    }

    int target = t - neg;
    if (target == 0) {
        cout << k << "\n";
        return;
    }

    sort(w.begin(), w.end());
    vector<int> items;
    for (int i = 0; i < (int)w.size(); ) {
        int j = i;
        while (j < (int)w.size() && w[j] == w[i]) j++;
        int cnt = j - i;
        int val = w[i];
        for (int p = 1; cnt >= p; p <<= 1) {
            items.push_back(p * val);
            cnt -= p;
        }
        if (cnt > 0) items.push_back(cnt * val);
        i = j;
    }

    bitset<20005> dp;
    dp[0] = 1;
    for (int x : items) {
        if (x <= target) {
            dp |= (dp << x);
            if (dp[target]) break;
        }
    }

    if (dp[target]) cout << k << "\n";
    else cout << k + 1 << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    if (cin >> t) {
        while (t--) solve();
    }
    return 0;
}

