#include <bits/stdc++.h>
using namespace std;
using iv = vector<int>;

void solve() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    string in;
    cin >> in >> ws;

    iv used(n);
    bool res = true;

    for (int i = 0; i < n; i++) {
      if (i % 2 == 0 && in[i] == 'Y') {
        used[i] = true;
        int pair = false;
        for (int j = i + 1; j < n; j++) {
          if (!used[j] && in[j] == 'Z') {
            used[j] = true;
            pair = true;
            break;
          }
        }
        if (!pair) used[i] = false;
      }
    }

    for (int i = n - 1; i > 0 && res; i--) {
      if (!used[i] && in[i] == 'Z') {
        used[i] = 1;
        bool pair = false;
        for (int j = i - 1; j >= 0; j--) {
          if (used[j]) continue;
          if (in[j] == 'Y' || in[j] == 'X') {
            used[j] = 1;
            pair = true;
            break;
          }
        }
        if (!pair) {
          res = false;
          break;
        }
      }
    }

    for (int i = 0; i < n - 1 && res; i++) {
      if (used[i]) continue;
      if (in[i] == 'Z') {
        res = false;
        break;
      }
      used[i] = true;
      char f = in[i];
      bool pair = false;
      for (int j = i + 1; j < n; j++) {
        if (used[j]) continue;
        if (f == 'X' && (in[j] == 'Y' || in[j] == 'Z')) {
          used[j] = 1;
          pair = true;
          break;
        }
        if (f == 'Y' && in[j] == 'Z') {
          used[j] = 1;
          pair = true;
          break;
        }
      }
      if (!pair) res = false;
    }
    cout << (res ? "Yes" : "No") << "\n";
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
