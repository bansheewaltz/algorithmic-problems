#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include <vector>

using namespace std;
using ll = int64_t;
using vi = vector<int>;
using pi = pair<int, int>;

typedef struct {
  double x;
  double y;
} Point;

void polygonInsertEdgePointByX(vector<Point> points, int x) {
  int counter = 0;
  int x = point.x;
  for (int i = 0; i <= points.size(); i++) {
    if (points[i].x < x && x <= points[(i + 1) % points.size()].x) {
      ++i;
      points.insert(points.begin() + i + 1, point);
      if (counter == 2)
        return;
    }
  }
}

double computePolygonAreaShoelace(vector<Point> points) {
  double left_sum = 0.0;
  double right_sum = 0.0;

  for (size_t i = 0; i < points.size(); ++i) {
    size_t j = (i + 1) % points.size();
    left_sum += points[i].x * points[j].y;
    right_sum += points[j].x * points[i].y;
  }

  return 0.5 * abs(left_sum - right_sum);
}

auto findPointIdxByValue(vector<Point> const& points, Point const& value) {
  for (int i = 0; i < points.size(); ++i) {
    if (points[i].x == value.x && points[i].y == value.y)
      return i;
  }
}

bool operator!=(const Point& a, const Point& b) {
  return !(a.x == b.x && a.y == b.y);
}

int main() {
  int vertices_count = 0;
  cin >> vertices_count;

  vector<Point> points;
  for (int i = 1; i <= vertices_count; ++i) {
    Point point;
    cin >> point.x >> point.y;
    points.push_back(point);
  }

  Point leftmost_point;
  Point rightmost_point;
  for (auto const& point : points) {
    if (leftmost_point.x > point.x)
      leftmost_point = point;
    if (rightmost_point.x < point.x)
      rightmost_point = point;
  }

  auto leftmost_point_idx = findPointIdxByValue(points, leftmost_point);
  auto rightmost_point_idx = findPointIdxByValue(points, rightmost_point);

  double total_polygon_area = computePolygonAreaShoelace(points);

  vector<Point> first_side_bound_points;
  for (int i = leftmost_point_idx; i % points.size() != rightmost_point_idx; ++i) {
    first_side_bound_points.push_back(points[i]);
  }
  vector<Point> second_side_bound_points;
  for (int i = leftmost_point_idx; i % points.size() != rightmost_point_idx; --i) {
    second_side_bound_points.push_back(points[i]);
  }
  vector<Point>* upper_bound_points = nullptr;
  vector<Point>* lower_bound_points = nullptr;
  if (first_side_bound_points[1].y >= points[leftmost_point_idx].y) {
    upper_bound_points = &first_side_bound_points;
    lower_bound_points = &second_side_bound_points;
  } else {
    upper_bound_points = &second_side_bound_points;
    lower_bound_points = &first_side_bound_points;
  }

  Point* current = &points[leftmost_point_idx];
  int ubp_last_idx = 0;
  int lbp_last_idx = 0;
  while (current != &points[rightmost_point_idx]) {
    if ((*upper_bound_points)[ubp_last_idx + 1].x < (*lower_bound_points)[lbp_last_idx + 1].x) {
      current = &(*upper_bound_points)[ubp_last_idx + 1];
      ubp_last_idx++;
    } else {
      current = &(*lower_bound_points)[lbp_last_idx + 1];
      lbp_last_idx++;
    }
  }
}
