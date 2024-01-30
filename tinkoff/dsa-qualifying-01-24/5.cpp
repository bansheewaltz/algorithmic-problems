#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

struct Car {
  int start_point;
  int number;
  int end_point;
};

bool CheckPath(int current_point, const vector<vector<Car>>& graph, const vector<int>& path,
               int path_index, int& last_point) {
  if (path_index == path.size()) {
    last_point = current_point;
    return true;
  }

  for (const Car& car : graph[current_point]) {
    if (car.number == path[path_index]) {
      int next_point = car.end_point;
      if (CheckPath(next_point, graph, path, path_index + 1, last_point)) {
        return true;
      }
    }
  }

  return false;
}

void solve() {
  int n, m, k;
  cin >> n >> m >> k;

  vector<vector<Car>> graph(n + 1);
  for (int i = 0; i < m; ++i) {
    int u, d, v;
    cin >> u >> d >> v;
    graph[u].push_back({u, d, v});
  }

  vector<int> path(k);
  for (int i = 0; i < k; ++i) cin >> path[i];

  int last_point = -1;
  for (int i = 1; i <= n; ++i) {
    if (CheckPath(i, graph, path, 0, last_point)) {
      cout << last_point << endl;
      return;
    }
  }

  cout << "0" << endl;
}

int main() {
#ifdef LOCAL
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  solve();
}
