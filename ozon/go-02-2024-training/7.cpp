#include <bits/stdc++.h>
using namespace std;
using iv = vector<int>;

void solve() {
  int t;
  cin >> t;
  while (t--) {
    int k;
    cin >> k;
    iv printed(k + 1);
    string in;
    cin >> ws;
    getline(cin, in);
    stringstream ss(in);

    while (ss) {
      int num, l, r;
      char ch = 0;
      ss >> num;
      ss >> ch;
      if (ch == '-') {
        l = num;
        ss >> r;
        for (int i = l; i <= r; i++) printed[i]++;
        ss >> ch;
      } else
        printed[num]++;
    }

    bool prev = false;
    for (int i = 1; i < k + 1; i++) {
      if (!printed[i]) {
        if (prev) cout << ",";
        cout << i;
        int c = 0;
        while (i + 1 < k + 1 && !printed[i + 1]) c++, i++;
        if (c) cout << "-" << i;
        prev = true;
      }
    }
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
