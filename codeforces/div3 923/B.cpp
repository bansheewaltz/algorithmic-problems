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
    int m[26] = {};
    for (int temp, i = 0; i < n; i++) {
      cin >> temp;
      for (int j = 0; j < 26; j++)
        if (m[j] == temp) {
          m[j]++;
          cout << (char)(j + 97);
          break;
        }
    }
    cout << "\n";
  }
}

int main() {
  // ios::sync_with_stdio(0);
  // cin.tie(0);
#ifdef LOCAL_TESTING
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#elif DEBUGGING
  freopen("in.txt", "r", stdin);
  cout << unitbuf;
#endif
  solve();
}
