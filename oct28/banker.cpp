#include <iomanip>
#include <iostream>
using namespace std;
int main() {
  int n, m;
  cout << "Enter the number of processes : ";
  cin >> n;
  cout << "Enter the number of resources : ";
  cin >> m;
  int allocation[n][m], max[n][m], available[m];

  cout<<"Enter the allocation matrix"<<endl;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> allocation[i][j];
    }
  }

  cout<<"Enter the max matrix"<<endl;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> max[i][j];
    }
  }

  cout<<"Enter the available matrix"<<endl;
  for (int j = 0; j < m; ++j) {
    cin >> available[j];
  }

  char choice;
  do {
    int need[n][m];
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        need[i][j] = max[i][j] - allocation[i][j];
      }
    }

    cout << "\nProcess     Allocation              Max                   Need" << endl;
    for (int i = 0; i < n; ++i) {
      cout << "P" << i << "        ";
      for (int j = 0; j < m; ++j) {
        cout<< setw(3) << allocation[i][j] << " ";
      }
      cout << "          ";
      for (int j = 0; j < m; ++j) {
        cout << setw(3)<< max[i][j] << " ";
      }
      cout << "          ";
      for (int j = 0; j < m; ++j) {
        cout << setw(3)<< need[i][j] << " ";
      }
      cout << endl;
    }

    cout << "\nAvailable" << endl;
    for (int j = 0; j < m; ++j) {
      cout << setw(3) << available[j] << " ";
    }
    cout << endl;

    bool finished[n];
    for (int i = 0; i < n; i++) {
      finished[i] = false;
    }
    int work[m];
    int safeSequence[n];
    int count = 0;

    for (int j = 0; j < m; j++) {
      work[j] = available[j];
    }

    while (count < n) {
      bool found = false;

      for (int i = 0; i < n; i++) {
        if (!finished[i]) {
          bool canAllocate = true;

          for (int j = 0; j < m; j++) {
            if (need[i][j] > work[j]) {
              canAllocate = false;
              break;
            }
          }

          if (canAllocate) {
            bool wouldLeaveAllZero = true;
            for (int j = 0; j < m; j++) {
              if (work[j] - need[i][j] > 0) {
                wouldLeaveAllZero = false;
                break;
              }
            }
            if (wouldLeaveAllZero) {
              canAllocate = false;
            }
          }

          if (canAllocate) {
            for (int j = 0; j < m; j++) {
              work[j] += allocation[i][j];
            }

            safeSequence[count++] = i;
            finished[i] = true;
            found = true;
            for (int j = 0; j < m; j++) {
              cout<< setw(3) << work[j] << " ";
            }
            cout << endl;
          }
        }
      }

      if (!found) {
        cout << "System is in unsafe state! Deadlock may occur." << endl;
        return 0;
      }
    }

    cout << "\nSystem is in safe state." << endl;
    cout << "Safe sequence: ";
    for (int i = 0; i < n; i++) {
      cout << "P" << safeSequence[i];
      if (i < n - 1)
        cout << " -> ";
    }
    cout << endl;

    // New Part: handle additional resource request
    cout << "\nDo you want to make an additional resource request? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
      int p;
      cout << "Enter process number making the request: ";
      cin >> p;
      int request[m];
      cout << "Enter request vector: ";
      for (int j = 0; j < m; j++) {
        cin >> request[j];
      }

      bool valid = true;
      for (int j = 0; j < m; j++) {
        if (request[j] > (max[p][j] - allocation[p][j])) {
          cout << "Error: Process has exceeded its maximum claim.\n";
          valid = false;
          break;
        }
        if (request[j] > available[j]) {
          cout << "Error: Resources not available.\n";
          valid = false;
          break;
        }
      }

      if (valid) {
        for (int j = 0; j < m; j++) {
          available[j] -= request[j];
          allocation[p][j] += request[j];
        }
        cout << "Request granted. Re-evaluating system state...\n";
      }
    }

  } while (choice == 'y' || choice == 'Y');

  return 0; 
}