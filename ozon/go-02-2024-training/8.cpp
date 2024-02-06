#include <bits/stdc++.h>
using namespace std;

void solve() {
  auto strtoint = [](string in) {
    if ('2' <= in[0] && in[0] <= '9') return in[0] - '0';
    switch (in[0]) {
      case 'T': return 10;
      case 'J': return 11;
      case 'Q': return 12;
      case 'K': return 13;
      case 'A': return 14;
      default: return 0;
    }
  };
  auto inttochar = [](int n) {
    if (2 <= n && n <= 9) return (char)(n + '0');
    switch (n) {
      case 10: return 'T';
      case 11: return 'J';
      case 12: return 'Q';
      case 13: return 'K';
      case 14: return 'A';
      default: return '0';
    }
  };

  vector<vector<char>> ccards(15);
  vector<char> suits = {'S', 'C', 'D', 'H'};
  for (int i = 1; i < 15; i++) {
    ccards[i] = suits;
  }

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;

    vector<vector<char>> cards = ccards;

    struct hand {
      int f, s;
      int comb;
    };

    hand fh;
    vector<hand> hv;
    for (int i = 0; i < n; i++) {
      hand p;
      string in[2];
      cin >> in[0] >> in[1];
      for (int i = 0; i < 2; i++) {
        int val = strtoint(in[i]);
        auto pos = find(cards[val].begin(), cards[val].end(), in[i][1]);
        cards[val].erase(pos);
        if (i == 0) p.f = val;
        if (i == 1) p.s = val;
        if (i == 1) p.comb = (p.f == p.s) + 1;
      }
      if (i == 0) fh = p;
      if (i != 0) hv.push_back(p);
    }

    auto recalc_comb = [](const hand& h, int v) { return h.comb + (v == h.f || v == h.s); };
    auto recalc_val = [](const hand& h, int v) {
      if (h.f == h.s == v) return v;
      if (h.f == h.s) return h.f;
      if (h.f == v) return h.f;
      if (h.s == v) return h.s;
      return max({h.f, h.s, v});
    };

    stringstream ss;
    int count = 0;
    for (int i = 2; i < 15; i++) {
      if (cards[i].empty()) continue;
      int fcomb = recalc_comb(fh, i);
      int fval = recalc_val(fh, i);
      for (const hand& h : hv) {
        int comb = recalc_comb(h, i);
        int val = recalc_val(h, i);
        if (comb > fcomb || comb == fcomb && fval < val) {
          cards[i].clear();
          break;
        }
      }
      count += cards[i].size();
      for (char suit : cards[i]) ss << inttochar(i) << suit << "\n";
    }
    cout << count << "\n";
    cout << ss.str();
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
