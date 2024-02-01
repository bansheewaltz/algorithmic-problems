#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, m, g;
  cin >> n >> m >> g;

  struct Dragon {
    int in, vo;
  };

  vector<Dragon> dv(n);
  for (Dragon& d : dv) cin >> d.in;
  for (Dragon& d : dv) cin >> d.vo;

  vector<int> fa[n];
  for (int i = 0, f1, f2; i < m; i++) {
    cin >> f1 >> f2;
    fa[f1 - 1].push_back(f2 - 1);
    fa[f2 - 1].push_back(f1 - 1);
  }

  vector checked(n, 0);

  struct FriendGroup : Dragon {
    double value;
  };

  vector<FriendGroup> fgv;

  for (int i = 0; i < n; i++) {
    if (checked[i]) continue;
    int group_vo = 0;
    int group_in = 0;

    auto invite_friends = [&](auto self, int i) -> void {
      for (int j = 0; j < fa[i].size(); j++) {
        int fi = fa[i][j];
        if (checked[fi]) continue;
        // if (group_vo > g) break;

        group_in += dv[fi].in;
        group_vo += dv[fi].vo;
        checked[fi] = 1;

        self(self, fi);
      }
    };

    invite_friends(invite_friends, i);
    if (!group_vo) group_vo = dv[i].vo, group_in = dv[i].in;
    fgv.push_back({group_in, group_vo, (double)group_in / group_vo});
  }

  sort(fgv.begin(), fgv.end(), [](const FriendGroup& p1, const FriendGroup& p2) {
    if (p1.value == p2.value) return p1.vo < p2.vo;
    return p1.value > p2.value;
  });

  int max_in = 0;
  int start = 0;
  while (start < fgv.size()) {
    int cur_vo = 0;
    int cur_in = 0;
    for (int i = start; i < fgv.size() && cur_vo < g; i++) {
      if (cur_vo + fgv[i].vo <= g) {
        cur_vo += fgv[i].vo;
        cur_in += fgv[i].in;
      }
    }
    if (cur_in < max_in) break;
    max_in = cur_in;
    start++;
  }
  cout << max_in << "\n";
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
