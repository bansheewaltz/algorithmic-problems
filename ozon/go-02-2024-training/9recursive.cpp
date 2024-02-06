#include <bits/stdc++.h>
using namespace std;
using iv = vector<int>;
using ivv = vector<vector<int>>;

// does not work on some cases

void solve() {
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    ivv field(n, iv(m));
    for (int t, i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        char t;
        cin >> t;
        field[i][j] = (t == '*' ? 1 : 0);
      }
    }

    struct pos {
      int x, y;
    };

    auto find_brc = [&](int i, int j) -> pos {  // bottom right corner
      while (j + 1 < m && field[i][j + 1] == 1) j++;
      while (i + 1 < n && field[i + 1][j] == 1) i++;
      return {j, i};
    };

    struct seq {
      int x1, x2;
    };

    int nd = 0;
    vector<int> nesting_depths;

    auto scan_frame = [&](auto self, int fis, int fjs, int fie, int fje) -> void {
      if (nd && (fje - fjs < 5 || fie - fis < 5)) return;
      vector<queue<seq>> stops(n);
      int iskip;
      for (int i = fis + (nd > 0); i < fie; i += iskip) {
        iskip = 1;
        int je = fje;
        int js = fjs;
        for (int j = fjs; j < fje;) {
          if (!stops[i].empty()) {
            seq jseq = stops[i].front();
            stops[i].pop();
            js = jseq.x1;
            je = jseq.x2;
            j = js;
          }

          while (j < je && !field[i][j]) j++;
          if (j == je) break;
          pos brc = find_brc(i, j);
          bool prev_skip = true;
          for (int k = i + 1; k <= brc.y; k++) {
            if (j - js >= 5) {
              // if (!stops[k].empty() && stops[k].back().x2 == fje)
              //   stops[k].back().x2 = j;
              // else
              stops[k].push({fjs, j});
            }
            if (fje - (brc.x + 1) >= 5) stops[k].push({brc.x + 1, fje});
            if (fje - (brc.x + 1) < 5 && j - js < 5 && prev_skip)
              iskip++;
            else
              prev_skip = false;
          }
          nesting_depths.push_back(nd++);
          self(self, i + 1, j + 1, brc.y, brc.x);
          nd--;
          j = brc.x + 1;
        }
      }
    };

    scan_frame(scan_frame, 0, 0, n, m);
    sort(nesting_depths.begin(), nesting_depths.end());
    for (int depth : nesting_depths) cout << depth << " ";
    cout << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
#ifdef LOCAL_TESTING
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#elif DEBUGGING
  freopen("in.txt", "r", stdin);
  cout << unitbuf;
#endif
  solve();
}
