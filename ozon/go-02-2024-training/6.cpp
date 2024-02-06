
#include <bits/stdc++.h>
using namespace std;
using iv = vector<int>;
using sv = vector<string>;

ostream& operator<<(ostream& os, sv const& content) {
  for (int i = 0; i < content.size(); i++) os << content[i] << "\n";
  os << "-\n";
  return os;
}

void solve() {
  int t;
  cin >> t;
  while (t--) {
    string in;
    cin >> ws;
    getline(cin, in);
    stringstream ss(in);

    int curh = 0;
    int curv = 0;
    char ch = 0;
    sv content;
    content.push_back("");
    while (ss.rdbuf()->in_avail()) {
      ss >> ch;
      switch (ch) {
        case 'U':
          curv = max(0, curv - 1);
          curh = (curh <= content[curv].size() ? curh : content[curv].size());
          break;
        case 'D':
          curv = min((int)content.size() - 1, curv + 1);
          curh = (curh <= content[curv].size() ? curh : content[curv].size());
          break;
        case 'R':
          curh = min((int)content[curv].size(), curh + 1);
          break;
        case 'L':
          curh = max(0, curh - 1);
          break;
        case 'B':
          curh = 0;
          break;
        case 'E':
          curh = content[curv].size();
          break;
        case 'N': {
          string trail;
          if (curh != content[curv].size()) {
            trail = content[curv].substr(curh);
            content[curv] = content[curv].substr(0, curh);
          }
          content.insert(content.begin() + curv + 1, trail);
          curv++;
          curh = 0;
          break;
        }
        default:
          content[curv].insert(curh, 1, ch);
          curh++;
      }
    }

    cout << content;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
#ifdef LOCAL_TESTING
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#elif DEBUGGING
  freopen("in.txt", "r", stdin);
  cout << unitbuf;
#endif
  solve();
}
