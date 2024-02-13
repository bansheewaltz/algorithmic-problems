#include <bits/stdc++.h>
using namespace std;
using iv = vector<int>;
using ivv = vector<vector<int>>;

void solve() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    string in;
    cin >> in;
    int l = -1, r = -1;
    for (int i = 0; i < n; i++)
      if (in[i] == 'B') {
        if (l==-1)
          l = i;
        else
          r = i;
      }
    if (r == -1) r = l;
    cout << r - l + 1 << "\n";
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
