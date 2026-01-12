#include <algorithm>
#include <climits>
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
  vector<int> pending = requests;
  int pos = current_head;
  int total = 0;
  vector<int> seq = {pos};
  cout << left << setw(6) << "From" << setw(6) << "to" << setw(10) << "distance"
       << endl;
  while (!pending.empty()) {
    int min_dist = INT_MAX;
    int next = -1;
    for (int r : pending) {
      int dist = abs(pos - r);
      if (dist < min_dist) {
        min_dist = dist;
        next = r;
      }
    }
    total += min_dist;
    cout << left << setw(6) << pos << setw(6) << next << setw(10) << min_dist
         << endl;
    seq.push_back(next);
    pos = next;
    auto it = find(pending.begin(), pending.end(), next);
    if (it != pending.end())
      pending.erase(it);
  }
  cout << "Track sequence: ";
  for (size_t i = 0; i < seq.size(); ++i) {
    cout << seq[i];
    if (i < seq.size() - 1)
      cout << "->";
  }
  cout << endl;
  cout << "Total head movements: " << total << endl;
  return 0;
}