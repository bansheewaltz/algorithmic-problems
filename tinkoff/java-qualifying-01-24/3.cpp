#include <bits/stdc++.h>
using namespace std;

struct Gift {
  int d, c, s;
};

void solve() {
  int n;
  cin >> n;

  vector<Gift> gl;
  for (int i = 0; i < n; i++) {
    int d, c, s;
    cin >> d >> c >> s;
    gl.push_back({d, c, s});
  }

  sort(gl.begin(), gl.end(), [](Gift a, Gift b) {
    if (a.s == b.s) return a.d + a.c < b.d + b.c;
    return (a.s < b.s);
  });

  int current_day = 0;
  for (int i = 0; i < n; ++i) {
    int ready_day = gl[i].d + gl[i].c;
    current_day = max(current_day, ready_day);
    if (current_day > gl[i].s) {
      cout << "NO\n";
      return;
    }
    current_day++;
  }

  cout << "YES\n";
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
