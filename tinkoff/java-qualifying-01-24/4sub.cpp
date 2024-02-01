#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, g;
  cin >> n >> g;

  struct P {
    int in, vo;
    double value;
  };

  vector<P> pv(n);
  for (P& p : pv) {
    cin >> p.in >> p.vo;
    p.value = (double)p.in / p.vo;
  }

  sort(pv.begin(), pv.end(), [](const P& p1, const P& p2) {
    if (p1.value == p2.value) return p1.vo < p2.vo;
    return p1.value > p2.value;
  });

  int max_in = 0;
  int start = 0;
  while (start < n) {
    int cur_vo = 0;
    int cur_in = 0;
    for (int i = start; i < n && cur_vo < g; i++) {
      if (cur_vo + pv[i].vo <= g) {
        cur_vo += pv[i].vo;
        cur_in += pv[i].in;
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
