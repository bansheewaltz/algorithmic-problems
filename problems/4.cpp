#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>

using namespace std;
using int64 = int64_t;

int n, k;
vector<int64> numbers;
int64 x = 0;

int countDigits(int64 value) {
  int n = 1;
  while (value /= 10) {
    n++;
  }
  return n;
}

int64 maxNumberOfMagnitude(int digits) {
  if (n == 0) {
    return 0;
  }
  int n = 9;
  for (int i = 1; i < digits; i++) {
    n = n * 10 + 9;
  }
  return n;
}

void read_input() {
  cin >> n >> k;
  numbers.resize(n);
  for (int i = 0; i < n; ++i) {
    cin >> numbers[i];
  }
}

int solve() {
  priority_queue<int64> queue;
  for (int i = 0; i < n; ++i) {
    int digits_count = countDigits(numbers[i]);
    int64 priority = maxNumberOfMagnitude(digits_count) - numbers[i];
    if (priority == 0)
      continue;
    queue.push(priority);
  }
  while (k != 0 && !queue.empty()) {
    int64 biggest_number = queue.top();
    queue.pop();

    int digits = countDigits(biggest_number);
    int64 new_priority = biggest_number % (int64)pow(10, digits - 1);
    x += biggest_number - new_priority;
    queue.push(new_priority);
    k--;
  }
  return x;
}

int main() {
  freopen("input.txt", "r", stdin);
  read_input();
  cout << solve();
}
