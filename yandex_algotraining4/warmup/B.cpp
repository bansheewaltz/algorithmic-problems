#include <iostream>
#include <vector>
using namespace std;

int a, b, c, d;

int main() {
  cin >> a >> b >> c >> d;
  /* not divisible */
  int lnum = a * d;
  int rnum = c * b;
  int cden = b * d;
  int cnum = lnum + rnum;
  for (int i = 2; i <= cden; i++) {
    if (cnum % i == 0 && cden % i == 0) {
      cnum /= i;
      cden /= i;
      i--;
    }
  }
  cout << cnum << " " << cden << endl;
}
