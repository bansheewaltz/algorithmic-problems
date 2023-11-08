#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

void solve();

int main() {
#ifdef LOCAL
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  solve();
  cout << "\n";
}

int r, c;
vector<vector<int>> f;

void solve() {
  cin >> r;
  cin >> c;
  f = vector<vector<int>>(r, vector<int>(c));

  for (int i = 0; i < r; i++)
    for (int j = 0; j < c; j++)
      cin >> f[i][j];

  int ms = 0;
  int smaller = r < c ? r : c;
  for (int i = 0; i < r; i++)
    for (int j = 0; j < c; j++) {
      if (f[i][j]) {
        int cur = 1;
        if (!ms)
          ms = 1;
        for (int k = 1; k < smaller; k++) {
          if (i + k < r && j + k < c && f[i][j + k]&&)
            cur++;
          else {
            j += k;
            break;
          }
        }
        ms < cur ? ms = cur : 0;
      }
    }
  cout << ms;
}
