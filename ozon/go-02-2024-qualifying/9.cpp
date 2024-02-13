#include <bits/stdc++.h>
using namespace std;
using iv = vector<int>;

void solve() {
  int t;
  cin >> t;
  for (int ti = 0; ti < t; ti++) {
    // cout << "t" << ti << "\n";
    int n;
    cin >> n;
    string s;
    cin >> s >> ws;

    vector<bool> used(n);
    vector<int> order(n);

    // define zs as second, xs as first, right-leaning ys as second order
    int frst_cnt = 0, sec_cnt = 0;
    int i = n - 1;
    while (s[i] == 'Y' && i > 0 && (i == n - 1 || s[i + 1] == 'Y')) order[i] = 2, i--, sec_cnt++;
    for (; i >= 0; i--) {
      if (s[i] == 'Z') order[i] = 2, sec_cnt++;
      if (s[i] == 'X') order[i] = 1, frst_cnt++;
    }

    // define left-leaning ys as first order
    i = 0;
    while (s[i] == 'Y' && i < n - 1 && (i == 0 || s[i - 1] == 'Y')) order[i] = 1, i++, frst_cnt++;

    // define remaining ys' orders
    int frst_left = n / 2 - frst_cnt;
    int sec_left = n / 2 - sec_cnt;
    for (; (frst_left || sec_left) && i < n; i++) {
      if (s[i] != 'Y') continue;
      if (frst_left)
        order[i] = 1, frst_left--;
      else
        order[i] = 2, sec_left--;
    }

    // match YZ pairs first
    int j = 1;
    for (int i = 0; i < n - 1; i++) {
      if (s[i] != 'Y' || order[i] != 1) continue;
      bool has_pair = false;
      if (j <= i) j = i + 1;
      for (; j < n; j++) {
        if (used[j]) continue;
        if (s[j] == 'Z') {
          used[j] = has_pair = true;
          j++;
          break;
        }
      }
      if (has_pair) used[i] = 1;
    }
    // match pairs and find unused
    j = 1;
    for (int i = 0; i < n - 1; i++) {
      if (s[i] != 'X') continue;
      bool has_pair = false;
      if (j <= i) j = i + 1;
      for (; j < n; j++) {
        if (used[j] || order[j] == 1) continue;
        if ((s[j] == 'Y' || s[j] == 'Z') && order[j == 2]) {
          used[j] = has_pair = true;
          break;
        }
      }
      if (has_pair) used[i] = 1;
    }

    cout << (accumulate(used.begin(), used.end(), 0) == n ? "Yes" : "No") << "\n";
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
#ifdef LOCAL_TESTING
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#elif DEBUGGING
  freopen("in.txt", "r", stdin);
  cout << unitbuf;
#endif
  solve();
}
