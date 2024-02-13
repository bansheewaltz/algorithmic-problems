#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

string fmt(string n) {
  string nfmt;
  for (int i = 0; i < n.size(); i++) {
    if (isdigit(n[i])) {
      nfmt.push_back(n[i]);
    }
  }

  if (nfmt.size() == 11 && nfmt[0] == '7') nfmt[0] = '8';
  if (nfmt.size() == 7) nfmt = "8495" + nfmt;

  return nfmt;
}

int main() {
#ifdef LOCAL
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  string n;
  cin >> n;
  string target = fmt(n);

  while (cin >> n) {
    string nfmt = fmt(n);
    cout << (nfmt == target ? "YES" : "NO") << std::endl;
  }
}
