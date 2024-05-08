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
    queue<char> q;
    for (int i = 0; i < n; i++) {
      char ch = in[i];
      if (q.empty() || ch == 'X') {
        q.push(ch);
        continue;
      }
      if (ch == 'Y') {
        if (q.front() == 'X')
          q.pop();
        else
          q.push(ch);
      }
      if (ch == 'Z') {
        if (q.front() == 'Y' || q.front() == 'X')
          q.pop();
        else
          break;
      }
    }
    cout << (q.empty() ? "Yes" : "No") << "\n";
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
