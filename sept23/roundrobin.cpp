#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Process {
  string name;
  int burst, arrival;
  int remaining;
  int turnaround, waiting;
  bool done;
};

int main() {
  int n, quantum;
  Process processes[10];

  cout << "Enter no. of processes: ";
  cin >> n;
  cout << "Enter Time Quantum: ";
  cin >> quantum;
  cout << "Arrival and Burst times: \n";
  for (int i = 0; i < n; i++) {
    cin >> processes[i].arrival >> processes[i].burst;
    processes[i].name = to_string(i);
    processes[i].remaining = processes[i].burst;
    processes[i].done = false;
  }

  int firstArrival = processes[0].arrival;
  for (int i = 1; i < n; i++)
    firstArrival = min(firstArrival, processes[i].arrival);

  int time = firstArrival, completed = 0;
  vector<int> timeLine;
  vector<string> execOrder;

  queue<int> q;
  vector<bool> inQueue(n, false);

  for (int i = 0; i < n; i++) {
    if (processes[i].arrival == firstArrival) {
      q.push(i);
      inQueue[i] = true;
    }
  }

  while (completed < n) {
    if (q.empty()) {
      time++;
      for (int i = 0; i < n; i++) {
        if (!inQueue[i] && !processes[i].done && processes[i].arrival <= time) {
          q.push(i);
          inQueue[i] = true;
        }
      }
      execOrder.push_back("");
      timeLine.push_back(time);
      continue;
    }

    int idx = q.front();
    q.pop();
    int runTime = min(quantum, processes[idx].remaining);

    for (int t = 0; t < runTime; t++) {
      execOrder.push_back("P" + processes[idx].name);
      time++;
      timeLine.push_back(time);

      for (int i = 0; i < n; i++) {
        if (!inQueue[i] && !processes[i].done && processes[i].arrival <= time) {
          q.push(i);
          inQueue[i] = true;
        }
      }
    }

    processes[idx].remaining -= runTime;

    if (processes[idx].remaining == 0) {
      processes[idx].done = true;
      processes[idx].turnaround = time - processes[idx].arrival;
      processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;
      completed++;
    } else {
      q.push(idx);
    }
  }

  vector<string> compactProc;
  vector<int> compactTime;
  compactProc.push_back(execOrder[0]);
  compactTime.push_back(timeLine[0]);
  for (size_t i = 1; i < execOrder.size(); i++) {
    if (execOrder[i] == compactProc.back()) {
      compactTime.back() = timeLine[i];
    } else {
      compactProc.push_back(execOrder[i]);
      compactTime.push_back(timeLine[i]);
    }
  }

  cout << "\nGantt Chart:\n";

  for (size_t i = 0; i < compactProc.size(); i++) {
    cout << " ";
    int len = compactProc[i].empty() ? 4 : compactProc[i].size() + 2;
    for (int j = 0; j < len; j++)
      cout << "-";
  }
  cout << "\n";

  for (size_t i = 0; i < compactProc.size(); i++) {
    if (compactProc[i].empty())
      cout << "|    ";
    else
      cout << "| " << compactProc[i] << " ";
  }
  cout << "|\n";

  for (size_t i = 0; i < compactProc.size(); i++) {
    cout << " ";
    int len = compactProc[i].empty() ? 4 : compactProc[i].size() + 2;
    for (int j = 0; j < len; j++)
      cout << "-";
  }
  cout << "\n";

  cout << firstArrival;
  for (size_t i = 0; i < compactTime.size(); i++) {
    int len = compactProc[i].empty() ? 4 : compactProc[i].size() + 2;

    string timeStr = to_string(compactTime[i]);
    int timeWidth = timeStr.length();

    int totalWidth = len + 1; 
    int padding = max(1, totalWidth - timeWidth);

    for (int j = 0; j < padding; j++)
      cout << " ";
    cout << compactTime[i];
  }
  cout << "\n\n";
  cout << "\n\n";

  cout << setw(10) << left << "Process" << setw(10) << left << "AT" << setw(10)
       << left << "BT" << setw(10) << left << "TAT" << setw(10) << left << "WT"
       << endl;

  for (int i = 0; i < n; i++) {
    cout << setw(10) << left << "P" + processes[i].name << setw(10) << left
         << processes[i].arrival << setw(10) << left << processes[i].burst
         << setw(10) << left << processes[i].turnaround << setw(10) << left
         << processes[i].waiting << endl;
  }

  double totalTAT = 0, totalWT = 0;
  for (int i = 0; i < n; i++) {
    totalTAT += processes[i].turnaround;
    totalWT += processes[i].waiting;
  }

  double ATAT = totalTAT / n;
  double AWT = totalWT / n;

  cout << "\nAverage Turnaround Time (ATAT): " << ATAT << endl;
  cout << "Average Waiting Time (AWT): " << AWT << endl;
}