#include <bits/stdc++.h>
using namespace std;
using iv = vector<int>;

// not finished

struct folder {
  string dir;
  vector<string> files;
  vector<folder> folders;
  bool infected = false;

  void readfiles(string in) {
    int i = 0;
    stringstream ss(in);
    if (in.find(']') == string::npos) {
      while (true) {
        string s;
        getline(cin, s);
        ss << s;
        if (s.find(']') != string::npos) break;
      }
    }
    string s = ss.str();
    while (s[i] != '[') i++;
    i++;
    while (i < s.size()) {
      while (s[i] != '\"') i++;
      i++;
      int begin = i;
      while (s[i] != '\"') i++;
      int end = i;
      files.push_back(s.substr(begin, end));
      if (s.substr(end - 5, end) == ".hack") infected = true;
      i++;
    }
  }
};

folder* readfolders() {
  string s;
  cin >> s;
  if (s.find("div") == string::npos) {
    while (true) {
      string s;
      getline(cin, s);
      ss << s;
      if (s.find(']') != string::npos) break;
    }
  }
}

void solve() {
  int t;
  cin >> t;
  while (t--) {
    int total = 0;
    int n;
    cin >> n;

    folder* root = readfolders();

    for (int i = 0; i < n; i++) {
    }

    cout << "\n";
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
#ifdef LOCAL_TESTING
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#elif DEBUGGING
  freopen("in.txt", "r", stdin);
  cout << unitbuf;
#endif
  solve();
}
