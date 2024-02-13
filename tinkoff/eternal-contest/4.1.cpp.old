#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>

using namespace std;
using int64 = int64_t;

int n, k;
vector<int64> numbers;
int64 x = 0;

void read_input() {
  cin >> n >> k;
  numbers.resize(n);
  for (int i = 0; i < n; ++i) {
    cin >> numbers[i];
  }
}

int solve() {
  vector<int64> components;
  for (int i = 0; i < n; ++i) {
    int magnitude_order = 1;
    while (numbers[i] % 10) {
      int64 component = (9 - (numbers[i] % 10)) * magnitude_order;
      if (component != 0)
        components.push_back(component);
      numbers[i] /= 10;
      magnitude_order *= 10;
    }
  }
  sort(components.begin(), components.end());
  while (k--) {
    x += components.back();
    components.pop_back();
  }
  return x;
}

int main() {
  freopen("input.txt", "r", stdin);
  read_input();
  cout << solve();
}
