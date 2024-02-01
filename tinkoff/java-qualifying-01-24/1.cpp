#include <bits/stdc++.h>
using namespace std;

void solve() {
  string input;
  cin >> input;
  regex vowel_re("code\\d+");
  cout << regex_replace(input, vowel_re, "???") << '\n';
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
