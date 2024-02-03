#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ivv_t = vector<vector<int>>;

void solve() {
  int n;
  cin >> n;
  int a[n];
  for (int i = 0; i < n; i++) cin >> a[i];

  int init = 0;
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      if (a[i] > a[j]) init++;

  ivv_t prefg, prefl, postg, postl;
  prefl = postg = postl = prefg = ivv_t(n, vector<int>(n));
  for (int i = 0; i < n - 1; i++)
    for (int j = i + 1; j < n; j++) {
      prefl[i][j] = prefl[i][j - 1] + (a[i] < a[j]);
      prefg[i][j] = prefg[i][j - 1] + (a[i] > a[j]);
    }
  for (int i = n - 1; i > 0; i--)
    for (int j = i - 1; j >= 0; j--) {
      postl[i][j] = postl[i][j + 1] + (a[i] < a[j]);
      postg[i][j] = postg[i][j + 1] + (a[i] > a[j]);
    }

  ll total = 0;
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      int cur = init;
      cur += prefl[i][j - 1];
      cur -= prefg[i][j - 1];
      cur -= postl[j][i + 1];
      cur += postg[j][i + 1];
      if (a[i] > a[j]) cur--;
      if (a[i] < a[j]) cur++;
      total += cur;
    }
  }

  ll pairsn = n * (n - 1) / 2;
  ll gcd = std::gcd(total, pairsn);
  cout << total / gcd << "/" << pairsn / gcd << "\n";
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
