#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;
using ll = int64_t;
using vi = vector<int>;

set<int> sum_set;
ll total = 0;
ll counter = 0;

void counter_recursive(vi &values, ll cur_sum, size_t last_value_id) {
  for (size_t i = last_value_id; i < values.size(); ++i) {
    if (cur_sum + values[i] <= total) {
      if (sum_set.find(cur_sum + values[i]) == sum_set.end()) {
        ++counter;
        sum_set.insert(cur_sum + values[i]);
      }
      counter_recursive(values, cur_sum + values[i], i);
    }
  }
}

int main() {
  cin >> total;
  total -= 1;
  counter += 1;

  vi values;
  int value;
  while (cin >> value)
    values.push_back(value);
  sort(values.rbegin(), values.rend());

  if (values.size() > 1) {
    counter_recursive(values, 0, 0);
  }

  cout << counter;
}
