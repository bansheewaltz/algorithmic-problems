#include <deque>
#include <iostream>

using namespace std;

int main() {
  int n_queries = 0;
  cin >> n_queries;

  deque<int> q;
  deque<int> new_queue;
  for (int i = 0; i < n_queries; i++) {
    int query = 0;
    cin >> query;
    switch (query) {
      case 1:
        int number;
        cin >> number;
        q.push_back(number);
        break;
      case 2:
        for (const auto& element : q) {
          new_queue.push_back(element);
          new_queue.push_back(element);
        }
        q = new_queue;
        new_queue.clear();
        break;
      case 3:
        cout << q.front() << '\n';
        q.pop_front();
        break;
    }
  }
}
