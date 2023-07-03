#include <iostream>
using namespace std;

int main() {
  int parts_count;
  cin >> parts_count;

  long long power_of_2 = 1;
  int exponent = 0;
  while (power_of_2 < parts_count) {
    power_of_2 *= 2;
    ++exponent;
  }

  int& slices_count = exponent;
  cout << slices_count;
}
