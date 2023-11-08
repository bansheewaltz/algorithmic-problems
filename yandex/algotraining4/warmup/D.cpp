#include <iostream>
#include <vector>
using namespace std;

void solve();

int main() {
#ifdef LOCAL
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  solve();
}

std::string a, b;
vector<int> enc;

void solve() {
  enc.resize('z' - 'a' + 1);

  cin >> a;
  cin >> b;

  for (int i = 0; i < a.size(); i++)
    enc[a[i] - 'a']++;
  for (int i = 0; i < b.size(); i++) {
    enc[b[i] - 'a']--;
    if (enc[b[i] - 'a'] < 0) {
      cout << "NO\n";
      return;
    }
  }
  cout << "YES\n";
}
