#include <iostream>
#include <vector>

using namespace std;

int main() {
  int queries;
  cin >> queries;

  for (int i = 0; i < queries; i++) {
    int range_l, range_r;
    cin >> range_l >> range_r;

    int64_t range_product = 1;
    for (int j = range_l; j <= range_r; j++) {
      range_product *= j;
    }

    int digits_sum = 0;
    int number = range_product;
    while (true) {
      while (number > 0) {
        digits_sum += number % 10;
        number /= 10;
      }
      if (digits_sum < 10)
        break;
      number = digits_sum;
      digits_sum = 0;
    }

    int& compressed_mumber = digits_sum;
    cout << compressed_mumber << '\n';
  }
}
