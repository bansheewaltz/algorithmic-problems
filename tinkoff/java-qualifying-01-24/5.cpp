#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n;
  cin >> n;

  vector<vector<int>> rooms(n + 1);
  for (int r1, r2, i = 0; i < n - 1; i++) {
    cin >> r1 >> r2;
    rooms[r1].push_back(r2);
    rooms[r2].push_back(r1);
  }

  int qc;
  cin >> qc;

  auto findpath = [&](auto self, int r1, int r2, int src) -> int {
    for (int i = 0; i < rooms[r1].size(); i++)
      if (rooms[r1][i] == r2) return r2;
    for (int i = 0; i < rooms[r1].size(); i++)
      if (rooms[r1][i] != src) {
        int res = self(self, rooms[r1][i], r2, r1);
        if (res) return rooms[r1][i];
      }
    return false;
  };

  for (int r1, r2, i = 0; i < qc; i++) {
    cin >> r1 >> r2;
    cout << findpath(findpath, r1, r2, r1) << "\n";
  }
}

int main() {
#ifdef LOCAL_TESTING
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#elif DEBUGGING
  freopen("in.txt", "r", stdin);
  cout << unitbuf;
#endif
  solve();
}
