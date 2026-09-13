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

#include <bits/stdc++.h>
using namespace std;

const int N = 4000005;
int a[N];

void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) a[i] = i;
    for (int m = 1; ; ++m) {
        int x = 2 * m * (m + 1);
        if (x + 1 > n) break;
        swap(a[x - 1], a[x]);
    }
    for (int i = 1; i <= n; ++i) {
        cout << a[i] << (i == n ? '\n' : ' ');
    }
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


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    if (cin >> t) {
        while (t--) solve();
    }
    return 
0;
}


#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;
int sa[N], rnk[N*2], old_rnk[N*2], lcp[N], id[N], cnt[N];
int st_l[20][N], st_r[20][N], lg[N], R[N];
int n;
string s;

void solve() {
    cin >> s;
    n = s.length();
    int m = max(256, n);
    fill(cnt, cnt + m, 0);
    fill(rnk, rnk + n * 2, -1);
    for(int i = 0; i < n; ++i) cnt[rnk[i] = s[i]]++;
    for(int i = 1; i < m; ++i) cnt[i] += cnt[i-1];
    for(int i = n - 1; i >= 0; --i) sa[--cnt[rnk[i]]] = i;
    for(int w = 1; w < n; w <<= 1) {
        int p = 0;
        for(int i = n - w; i < n; ++i) id[p++] = i;
        for(int i = 0; i < n; ++i) if(sa[i] >= w) id[p++] = sa[i] - w;
        fill(cnt, cnt + m, 0);
        for(int i = 0; i < n; ++i) cnt[rnk[i]]++;
        for(int i = 1; i < m; ++i) cnt[i] += cnt[i-1];
        for(int i = n - 1; i >= 0; --i) sa[--cnt[rnk[id[i]]]] = id[i];
        copy(rnk, rnk + n * 2, old_rnk);
        p = 0;
        for(int i = 0; i < n; ++i) {
            rnk[sa[i]] = (i > 0 && old_rnk[sa[i]] == old_rnk[sa[i-1]] && old_rnk[sa[i]+w] == old_rnk[sa[i-1]+w]) ? p : ++p;
        }
        if(p == n - 1) break;
        m = p + 1;
    }
    for(int i = 0, k = 0; i < n; ++i) {
        if(rnk[i] == 0) { lcp[0] = 0; continue; }
        int j = sa[rnk[i]-1];
        while(i + k < n && j + k < n && s[i+k] == s[j+k]) k++;
        lcp[rnk[i]] = k;
        if(k) k--;
    }
    for(int i = 0; i < n; ++i) st_l[0][i] = lcp[i];
    for(int j = 1; j <= lg[n]; ++j) {
        for(int i = 0; i + (1 << j) <= n; ++i) {
            st_l[j][i] = min(st_l[j-1][i], st_l[j-1][i+(1<<(j-1))]);
        }
    }
    for(int i = 0; i < n; ++i) st_r[0][i] = i;
    for(int j = 1; j <= lg[n]; ++j) {
        for(int i = 0; i + (1 << j) <= n; ++i) {
            int L = st_r[j-1][i], R_idx = st_r[j-1][i+(1<<(j-1))];
            st_r[j][i] = (rnk[L] < rnk[R_idx]) ? L : R_idx;
        }
    }
    for(int i = 0, l = 0, r = -1; i < n; ++i) {
        int k = (i > r) ? 1 : min(R[l + r - i], r - i + 1);
        while(0 <= i - k && i + k < n && s[i - k] == s[i + k]) k++;
        R[i] = k - 1;
        if(i + k - 1 > r) {
            l = i - k + 1;
            r = i + k - 1;
        }
    }
    auto get_lcp = [&](int u, int v) {
        if(u == v) return n - u;
        u = rnk[u]; v = rnk[v];
        if(u > v) swap(u, v);
        u++;
        int k = lg[v - u + 1];
        return min(st_l[k][u], st_l[k][v - (1<<k) + 1]);
    };
    for(int i = 0; i < n; ++i) {
        int L = i - R[i], R_idx = i, k = lg[R_idx - L + 1];
        int left = st_r[k][L], right = st_r[k][R_idx - (1<<k) + 1];
        int best = (rnk[left] < rnk[right]) ? left : right;
        int r_m = i - best, ans = r_m;
        for(int r = 0; r <= r_m; ++r) {
            if(get_lcp(i - r, i - r_m) >= 2 * r + 1) {
                ans = r;
                break;
            }
        }
        cout << ans << (i == n - 1 ? "" : " ");
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    lg[1] = 0;
    for(int i = 2; i < N; ++i) lg[i] = lg[i/2] + 1;
    int t;
    cin >> t;
    while(t--) solve();
    return 0;
}

// 電影發明以後，人類的生命，比以前至少延長了三倍。
// amlhdsan
#include <bits/stdc++.h>
#define N 200010
using namespace std;

int n;
long long s, a[N];

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9') {
        if(ch == '-') {
            f = -1;
        }
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

inline void write(int x) {
    if(x < 0) {
        putchar('-');
        x = -x;
    }
    if(x > 9) {
        write(x / 10);
    }
    putchar(x % 10 + '0');
}

inline void writeln(int x) {
    write(x);
    putchar('\n');
}

int main() {
    int T = read();

    while(T--) {
        n = read();
        s = 0;

        for(int i = 1; i <= n; i++) {
            a[i] = read();
            s += a[i];
        }

        if(n == 1) {
            writeln(0);
            continue;
        }

        if(n == 2) {
            long long d = llabs(a[1] - a[2]);
            d %= 4;

            if(d == 3) {
                d = 1;
            }

            writeln(d);
            continue;
        }

        if(n % 2 == 0 && (s & 1)) {
            writeln(1);
        } else {
            writeln(0);
        }
    }

    return 0;
}



