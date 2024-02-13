#include <iostream>
#include <vector>

using namespace std;

int main() {
  int rows, columns, queries;
  cin >> rows >> columns >> queries;

  vector<vector<int>> matrix(rows, vector<int>(columns));
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      cin >> matrix[i][j];
    }
  }

  for (int i = 0; i < queries; i++) {
    int rooms = 0;
    int x, y, stamina;
    cin >> y >> x >> stamina;
    x--, y--;

    for (int i = 0; i < columns; i++) {
      if (i == x)
        continue;
      if (abs(matrix[y][i] - matrix[y][x]) <= stamina)
        rooms++;
    }
    for (int i = 0; i < rows; i++) {
      if (i == y)
        continue;
      if (abs(matrix[i][x] - matrix[y][x]) <= stamina)
        rooms++;
    }
    cout << rooms << '\n';
  }
}
