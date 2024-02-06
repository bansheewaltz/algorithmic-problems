#include <bits/stdc++.h>
using namespace std;
using iv = vector<int>;

struct tree {
  int id;
  int p;
  string text;
  set<int> children;
};

void solve() {
  int t;
  cin >> t;
  while (t--) {
    map<int, tree> ct;  // comment tree
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
      int id, p;
      string text;
      cin >> id >> p;
      char waste;
      cin.get(waste);
      getline(cin, text);
      ct[id] = {id, p, text + "\n", std::move(ct[id].children)};
      ct[p].children.insert(id);
    }

    auto print = [&](auto self, int id, string buffer) -> void {
      if (ct[id].p == -1)
        cout << ct[id].text;
      else {
        cout << buffer << "|\n";
        cout << buffer << "|--" << ct[id].text;
      }
      int siblings_c = ct[ct[id].p].children.size();

      for (const int child_id : ct[id].children) {
        string nbuf;
        if (siblings_c > 1 && *--ct[ct[id].p].children.end() != id)
          nbuf = buffer + "|  ";
        else
          nbuf = buffer + "   ";
        if (ct[id].p == -1) nbuf = "";
        self(self, child_id, nbuf);
      }
    };
    for (const int id : ct[-1].children) {
      print(print, id, "");
      cout << "\n";
    }
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
