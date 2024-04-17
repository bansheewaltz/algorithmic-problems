#include <bits/stdc++.h>
using namespace std;
#define endl '\n'


static void solve() {
  constexpr int inf = INT_MAX, n_max = 100, K = 0, G = 1;
  const vector<int> dxK = { 1,  2, 2, 1, -1, -2, -2, -1},
                    dyK = {-2, -1, 1, 2,  2,  1, -1, -2},
                    dxG = { 1,  1, 1, 0, -1, -1, -1,  0},
                    dyG = {-1,  0, 1, 1,  1,  0, -1, -1};
  
  int n; cin >> n;
  vector<string> board(n);
  int x0, y0, xf, yf;
  for (int i = 0; i < n; ++i) {
    cin >> board[i];
    for (int j = 0; j < n; ++j) {
      if (board[i][j] == 'S') 
        x0 = i, y0 = j;
      if (board[i][j] == 'F') 
        xf = i, yf = j;
    }
  }

  const auto in_board = [n](int i, int j) { 
    return i >= 0 && i < n && j >= 0 && j < n; 
  };

  vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(2, inf)));
  dp[x0][y0][K] = 0;
  // <<steps, figure>, <x,y>>
  set<pair<pair<int, int>, pair<int,int>>> bfsq = {{{0, K}, {x0, y0}}};
  while (!bfsq.empty()) {
    auto strategy = *begin(bfsq); bfsq.erase(begin(bfsq));
    auto f = strategy.first.second;
    auto x = strategy.second.first;
    auto y = strategy.second.second;

    for (size_t i = 0; i < 8; ++i) {
      int x1 = x, y1 = y;
      if (f == K)
        x1 += dxK[i], y1 += dyK[i];
      if (f == G)
        x1 += dxG[i], y1 += dyG[i];
      if (!in_board(x1, y1)) 
        continue;
      
      int f1 = f;
      if (board[x1][y1] == 'G')
        f1 = G;
      if (board[x1][y1] == 'K')
        f1 = K;
      if (dp[x1][y1][f1] > dp[x][y][f] + 1) {
        bfsq.erase({{dp[x1][y1][f1], f1}, {x1, y1}});
        dp[x1][y1][f1] = dp[x][y][f] + 1;
        bfsq.insert({{dp[x1][y1][f1], f1}, {x1, y1}});
      }
    }
  }

  auto min = ::min(dp[xf][yf][K], dp[xf][yf][G]);
  cout << (min == inf ? -1 : min) << endl;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0); // Fast IO
  solve();
}
