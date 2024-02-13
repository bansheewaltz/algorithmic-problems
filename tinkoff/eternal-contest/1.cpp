#include <iostream>
using namespace std;

int main() {
  int plan_price;
  int traffic_per_month;
  int extra_mb_price;
  int traffic_spending;

  cin >> plan_price >> traffic_per_month >> extra_mb_price >> traffic_spending;
  int payment = plan_price;
  if (traffic_spending > traffic_per_month) {
    payment += (traffic_spending - traffic_per_month) * extra_mb_price;
  }
  cout << payment;
}
