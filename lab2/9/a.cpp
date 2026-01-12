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
  int pos = current_head;
  int total = 0;
  vector<int> seq = {pos};
  cout << left << setw(6) << "From" << setw(6) << "to" << setw(10) << "distance"
       << endl;
  for (int r : requests) {
    int dist = abs(pos - r);
    total += dist;
    cout << left << setw(6) << pos << setw(6) << r << setw(10) << dist << endl;
    seq.push_back(r);
    pos = r;
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