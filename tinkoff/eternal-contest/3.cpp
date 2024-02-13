#include <iostream>
#include <vector>

using namespace std;

int n, t;
vector<int> floors;
int x;

void read_input() {
  cin >> n >> t;
  for (int i = 0; i < n; ++i) {
    int floor;
    cin >> floor;
    floors.push_back(floor);
  }
  cin >> x, x--;
}

int solve() {
  int time_bw_first = floors[x] - floors[0];
  int time_bw_last = floors[floors.size() - 1] - floors[x];

  if (time_bw_first <= t || time_bw_last <= t) {
    return time_bw_first + time_bw_last;
  }
  if (time_bw_first > time_bw_last) {
    return 2 * time_bw_last + time_bw_first;
  }
  return time_bw_last + 2 * time_bw_first;
}

int main() {
  read_input();
  cout << solve();
}
