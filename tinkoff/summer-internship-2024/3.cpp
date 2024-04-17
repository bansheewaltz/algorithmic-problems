#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

static void solve() {
  int n; cin >> n;
  vector<string> paths(n);
  for (int i = 0; i < n; ++i) 
    cin >> paths[i];
  
  sort(begin(paths), end(paths));
  for (auto& path : paths) {
    auto nesting_level = count(begin(path), end(path), '/');
    for (int i = 0; i < nesting_level; ++i)
      cout << "  ";
    auto last_level = path.find_last_of('/');
    if (last_level != string::npos)
      path = path.substr(last_level + 1);
    cout << path << endl;
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0); // Fast IO
  solve();
}
