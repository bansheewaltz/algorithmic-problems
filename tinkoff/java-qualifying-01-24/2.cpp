#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n;
  cin >> n;

  int heights[n];
  for (int i = 0; i < n; i++) {
    cin >> heights[i];
  }

  sort(heights, heights + n);
  vector<int> stacks;
  for (int i = 0; i < n;) {
    int count = 1;
    for (int j = i + 1; j < n && heights[i] == heights[j]; j++) {
      count++;
    }
    i += count;
    stacks.push_back(count);
  }

  sort(stacks.begin(), stacks.end());
  cout << stacks.size() << "\n";
  for (int i = 0; i < stacks.size(); i++) {
    cout << stacks[i];
    if (i != stacks.size() - 1) cout << " ";
  }
  cout << "\n";
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
