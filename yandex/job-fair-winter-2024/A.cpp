#include <bits/stdc++.h>
using namespace std;

int check(char b[8][8], int i, int j) {
  int res = 0;
  int e;

  if (j >= 6) goto vertical;

  e = 0;
  // horizontal
  for (int k = j; k < j + 3; k++)
    if (b[i][k] == '.') e++;
  // bottom
  if (e == 3 && i + 1 < 8 && b[i + 1][j + 1] == '.') res += 1;
  // top
  if (e == 3 && i - 1 >= 0 && b[i - 1][j + 1] == '.') res += 1;

vertical:
  if (i >= 6) return res;
  e = 0;
  // vertical
  for (int k = i; k < i + 3; k++)
    if (b[k][j] == '.') e++;
  // right
  if (e == 3 && j + 1 < 8 && b[i + 1][j + 1] == '.') res += 1;
  // left
  if (e == 3 && j - 1 >= 0 && b[i + 1][j - 1] == '.') res += 1;

  return res;
}

void solve() {
  char b[8][8];
  // vector<vector<int>> b);
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++) cin >> b[i][j];

  int res = 0;
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++) res += check(b, i, j);

  cout << res << "\n";
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
