#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
  int n;
  cin >> n;
  string in;
  getline(cin, in);

  while (n--) {
    getline(cin, in);
    stringstream ss;
    for (int i = 0; i < in.size();) {
      int res = 0;
      if (i + 3 < in.size()) {
        res = isalpha(in[i + 0]) &&  //
              isdigit(in[i + 1]) &&  //
              isalpha(in[i + 2]) &&  //
              isalpha(in[i + 3]);    //
        if (res) res = 4;
      }
      if (!res && i + 4 < in.size()) {
        res = isalpha(in[i + 0]) &&  //
              isdigit(in[i + 1]) &&  //
              isdigit(in[i + 2]) &&  //
              isalpha(in[i + 3]) &&  //
              isalpha(in[i + 4]);    //
        if (res) res = 5;
      }
      if (!res) {
        cout << "-\n";
        break;
      } else {
        for (int j = i; i < j + res; i++) ss << in[i];
        ss << (i == in.size() ? "\n" : " ");
      }
      if (i == in.size()) cout << ss.str();
    }
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
