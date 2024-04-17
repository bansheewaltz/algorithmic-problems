#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

static void transpose(int n) {
  for (int i = 0; i < n; ++i)
    for (int j = i + 1; j < n; ++j) {
      // swap(mat[i, j], mat[j, i])
      cout << i << " " << j << " " << j << " " << i << endl;
    }
}

static void reverse_rows(int n) {
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n / 2; ++j) {
      // swap(mat[i, j], mat[i, (n - 1) - j])
      cout << i << " " << j << " " << i << " " << (n - 1) - j << endl;
    }
}

static void solve() {
  int n; cin >> n;
  char rot; cin >> rot;

  cout << ((n * n - n) / 2) + (n / 2 * n) << endl;
  if (rot == 'R')
    transpose(n), reverse_rows(n);
  if (rot == 'L')
    reverse_rows(n), transpose(n);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0); // Fast IO
  solve();
}
