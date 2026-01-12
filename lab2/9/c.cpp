#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;
int main() {
  int block_size;
  cout << "Enter block size: ";
  cin >> block_size;
  vector<int> requests;
  cout << "Enter request queue (-1 to exit): ";
  int req;
  do {
    cin >> req;
    if (req != -1)
      requests.push_back(req);
  } while (req != -1);
  int current_head;
  cout << "Enter current head position: ";
  cin >> current_head;
  int prev_head;
  cout << "Enter previous head position: ";
  cin >> prev_head;
  int dir = (current_head >= prev_head) ? 1 : -1;
  // Separate left and right (renamed to avoid shadowing std::left)
  vector<int> left_reqs, right_reqs;
  for (int r : requests) {
    if (r < current_head)
      left_reqs.push_back(r);
    else if (r > current_head)
      right_reqs.push_back(r);
  }
  sort(left_reqs.begin(), left_reqs.end());
  sort(right_reqs.begin(), right_reqs.end());
  vector<int> order;
  if (dir == 1) {
    order.insert(order.end(), right_reqs.begin(), right_reqs.end());
    reverse(left_reqs.begin(), left_reqs.end());
    order.insert(order.end(), left_reqs.begin(), left_reqs.end());
  } else {
    reverse(left_reqs.begin(), left_reqs.end());
    order.insert(order.end(), left_reqs.begin(), left_reqs.end());
    order.insert(order.end(), right_reqs.begin(), right_reqs.end());
  }
  int pos = current_head;
  int total = 0;
  vector<int> seq = {pos};
  cout << left << setw(6) << "From" << setw(6) << "to" << setw(10) << "distance"
       << endl;
  for (int next : order) {
    int dist = abs(pos - next);
    total += dist;
    // Row output (uses std::left without conflict)
    cout << left << setw(6) << pos << setw(6) << next << setw(10) << dist
         << endl;
    seq.push_back(next);
    pos = next;
  }
  cout << "Track sequence: ";
  for (size_t i = 0; i < seq.size(); ++i) {
    cout << seq[i];
    if (i < seq.size() - 1)
      cout << ">";
  }
  cout << endl;
  cout << "Total head movements: " << total << endl;
  return 0;
}