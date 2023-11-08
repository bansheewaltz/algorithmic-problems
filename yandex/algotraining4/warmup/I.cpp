#include <cmath>
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
  cout << "\n";
}

string str;
vector<char> s;

void solve() {
  cin >> str;
  // s.resize(str.size());

  int i;
  for (i = 0; i < str.size(); i++) {
    if (str[i] == '(' || str[i] == '{' || str[i] == '[')
      s.push_back(str[i]);
    else {
      if (s.size() == 0)
        break;
      if (str[i] == ')') {
        if (s.back() == '(')
          s.pop_back();
        else
          break;
      }
      if (str[i] == ']') {
        if (s.back() == '[')
          s.pop_back();
        else
          break;
      }
      if (str[i] == '}') {
        if (s.back() == '{')
          s.pop_back();
        else
          break;
      }
    }
  }

  if (i != str.size() || s.size())
    cout << "no";
  else
    cout << "yes";
}

// void solve() {
//   cin >> s;

//   int cb = 0;
//   int sb = 0;
//   int pb = 0;

//   int i;
//   for (i = 0; i < s.length(); i++) {
//     if (s[i] == '(') {
//       pb++;
//     }
//     if (s[i] == ')') {
//       pb--;
//       if (pb < 0)
//         break;
//     }

//     if (s[i] == '[') {
//       sb++;
//     }
//     if (s[i] == ']') {
//       sb--;
//       if (sb < 0)
//         break;
//     }

//     if (s[i] == '{') {
//       cb++;
//     }
//     if (s[i] == '}') {
//       cb--;
//       if (cb < 0)
//         break;
//     }
//   }

//   if (i != s.length() || pb || cb || sb)
//     cout << "no";
//   else
//     cout << "yes";
// }
