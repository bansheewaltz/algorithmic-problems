#include <iostream>

using namespace std;

int main() {
  int n = 0;
  cin >> n;

  cout << 0 << ' ';

  int64_t total_cubes_count = 1;
  for (int h = 2; h <= n; h++) {
    int64_t base_side = 2 * h - 1;
    int64_t base_cubes_count = base_side * base_side;
    total_cubes_count += base_cubes_count;
    int64_t cubes_price = base_cubes_count * base_side - total_cubes_count;
    cout << cubes_price << ' ';
  }
}
