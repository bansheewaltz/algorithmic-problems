#include <iostream>
#include <vector>
using namespace std;

int seqlen = 0;
int qrycount = 0;
vector<int> seq;
int lr[2];

#define nf INT_MIN

int solve(int lr[2]) {
  int min = seq[lr[0]];
  for (int i = lr[0]; i <= lr[1]; i++) {
    if (seq[i] < min)
      return min;
    if (seq[i] > min)
      return seq[i];
  }
  return nf;
}

int main() {
  cin >> seqlen >> qrycount;
  seq.resize(seqlen);
  for (int i = 0; i < seqlen; ++i) {
    cin >> seq[i];
  }
  for (int i = 0; i < qrycount; ++i) {
    cin >> lr[0];
    cin >> lr[1];
    int res = solve(lr);
    if (res == nf)
      cout << "NOT FOUND\n";
    else
      cout << res << "\n";
  }
}
