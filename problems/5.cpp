#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef struct {
  int a;
  int b;
  int c;
  int total;
} Herd;

int countUgliness(int a, int b, int c) {
  vector<int> counts = {a, b, c};
  int max = *max_element(begin(counts), end(counts));
  int min = *min_element(begin(counts), end(counts));
  return max - min;
}

int main() {
  freopen("input.txt", "r", stdin);

  int herds_count;
  cin >> herds_count;

  int a_total = 0;
  int b_total = 0;
  int c_total = 0;

  vector<Herd> herds;
  for (int i = 0; i < herds_count; i++) {
    string herd;
    cin >> herd;

    Herd herd_stats;

    herd_stats.a = count(herd.begin(), herd.end(), 'a');
    herd_stats.b = count(herd.begin(), herd.end(), 'b');
    herd_stats.c = count(herd.begin(), herd.end(), 'c');
    a_total += herd_stats.a;
    b_total += herd_stats.b;
    c_total += herd_stats.c;
    herd_stats.total = herd.length();

    herds.push_back(herd_stats);
  }
  int strength_full_stable = a_total + b_total + c_total;
  int ugliness_full_stable = countUgliness(a_total, b_total, c_total);

  int ugliness_stable = ugliness_full_stable;
  int strength_stable = strength_full_stable;
  int a_stable = a_total;
  int b_stable = b_total;
  int c_stable = c_total;

  // task: instead of finding best to buy we will be finding worst to not buy
  // assuming that the initial state of the stable is inclusion of all herds
  vector<Herd>& herds_stable = herds;
  for (int i = 0; i < herds_count; i++) {
    // auto herd_not_to_buy = herds.begin();
    vector<Herd>::iterator herd_not_to_buy;
    int best_ugliness_wo_herd;
    int best_strength_wo_herd;
    bool found = false;
    for (auto it = herds.begin(); it != herds.end(); ++it) {
      const Herd& herd = *it;
      int a_wo_herd = a_stable - herd.a;
      int b_wo_herd = b_stable - herd.b;
      int c_wo_herd = c_stable - herd.c;

      int ugliness_wo_herd = countUgliness(a_wo_herd, b_wo_herd, c_wo_herd);
      int strength_wo_herd = strength_stable - herd.total;
      if (ugliness_wo_herd < ugliness_stable) {
        if (!found) {
          found = true;
          goto set_herd_as_not_to_buy;
        }
        if (ugliness_wo_herd > best_ugliness_wo_herd)
          continue;
        if (ugliness_wo_herd == best_ugliness_wo_herd) {
          if (best_strength_wo_herd > strength_wo_herd)
            continue;
        }
set_herd_as_not_to_buy:
        herd_not_to_buy = it;
        best_ugliness_wo_herd = ugliness_wo_herd;
        best_strength_wo_herd = strength_wo_herd;
      }
    }
    if (!found)
      break;
    a_stable -= (*herd_not_to_buy).a;
    b_stable -= (*herd_not_to_buy).b;
    c_stable -= (*herd_not_to_buy).c;
    herds_stable.erase(herd_not_to_buy);
    ugliness_stable = best_ugliness_wo_herd;
    strength_stable = best_strength_wo_herd;
  }

  cout << strength_stable;
}
