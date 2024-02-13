#include <bits/stdc++.h>
using namespace std;
using iv = vector<int>;
using ll = long long;

void solve() {
  int t;
  cin >> t;
  while (t--) {
    string in;
    cin >> in >> ws;

    bool res = true;
    for (int i = 0; i < in.length(); i++) {
      if (i == 0 && in[i] != 'M') {
        res = false;
        break;
      }
      if (i == 0) continue;
      if (in[i - 1] == 'M') {
        if (in[i] == 'M') {
          res = false;
          break;
        }
        continue;
      }
      if (in[i - 1] == 'R' && in[i] != 'C') {
        res = false;
        break;
      }
      if (in[i - 1] == 'C' && in[i] != 'M') {
        res = false;
        break;
      }
      if (in[i - 1] == 'D' && in[i] != 'M') {
        res = false;
        break;
      }
    }
    if (in[in.size() - 1] != 'D') res = false;

    cout << (res ? "YES" : "NO") << "\n";
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
