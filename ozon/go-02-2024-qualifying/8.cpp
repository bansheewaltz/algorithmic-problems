#include <bits/stdc++.h>
using namespace std;
using iv = vector<int>;

void solve() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    iv a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int top = 0;
    int lesser = 0;
    int greater = 0;
    iv seasons(n + 1);
    int cur = 0;
    for (int i = 0; i < n - 1; i++) {
      if (a[i] < a[i + 1]) {
        if (lesser) top = lesser;
        lesser = 0;
        greater++;
        if (greater < top && !seasons[greater]) seasons[greater]++;
        if (greater == top) cur < 2 ? cur = 2 : cur++;
        if (cur > seasons[top]) seasons[top] = cur / 2;
        if (greater > top) cur = 0;
      } else {
        if (greater) top = greater;
        greater = 0;
        lesser++;
        if (lesser < top && !seasons[lesser]) seasons[lesser] = 1;
        if (lesser == top) cur < 2 ? cur = 2 : cur++;
        if (cur > seasons[top]) seasons[top] = cur / 2;
        if (lesser > top) cur = 0;
      }
    }
    for (int i = 1; i < n + 1; i++) cout << seasons[i] << " ";
    cout << "\n";
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
