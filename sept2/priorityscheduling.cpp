#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int id;       // process ID
    int at;       // arrival time
    int bt;       // burst time
    int priority; // priority
    int ct;       // completion time
    int tat;      // turnaround time
    int wt;       // waiting time
};

bool arrivalCompare(Process a, Process b) {
    return a.at < b.at;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "Enter AT, BT, Priority for P" << p[i].id << ": ";
        cin >> p[i].at >> p[i].bt >> p[i].priority;
    }

    sort(p.begin(), p.end(), arrivalCompare);

    int time = 0, completed = 0;
    vector<bool> done(n, false);

    while (completed < n) {
        int idx = -1;
        int highestPriority = 1e9;

        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= time) {
                if (p[i].priority < highestPriority) {
                    highestPriority = p[i].priority;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            time++; 
        } else {
            time += p[idx].bt;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            done[idx] = true;
            completed++;
        }
    }

    cout << "\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\n";
    double totalTAT = 0, totalWT = 0;
    for (int i = 0; i < n; i++) {
        cout << "P" << p[i].id << "\t" << p[i].at << "\t" << p[i].bt
             << "\t" << p[i].priority << "\t\t" << p[i].ct << "\t" << p[i].tat
             << "\t" << p[i].wt << "\n";
        totalTAT += p[i].tat;
        totalWT += p[i].wt;
    }

    cout << "\nAverage TAT = " << (totalTAT / n);
    cout << "\nAverage WT = " << (totalWT / n) << endl;
    vector<string> ganttProc;
    vector<int> ganttTime;
    int currTime = 0;
    int lastTime = 0;
    int prevIdx = -1;

    int firstArrival = p[0].at;
    currTime = firstArrival;

    vector<bool> doneGantt(n, false);
    int completedGantt = 0;

    while (completedGantt < n) {
        int idx = -1;
        int highestPriority = 1e9;

        for (int i = 0; i < n; i++) {
            if (!doneGantt[i] && p[i].at <= currTime) {
                if (p[i].priority < highestPriority) {
                    highestPriority = p[i].priority;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            ganttProc.push_back("IDLE");
            currTime++;
            ganttTime.push_back(currTime);
        } else {
            ganttProc.push_back("P" + to_string(p[idx].id));
            currTime += p[idx].bt;
            ganttTime.push_back(currTime);
            doneGantt[idx] = true;
            completedGantt++;
        }
    }

    vector<string> compactProc;
    vector<int> compactTime;
    if (!ganttProc.empty()) {
        compactProc.push_back(ganttProc[0]);
        compactTime.push_back(ganttTime[0]);
        for (size_t i = 1; i < ganttProc.size(); i++) {
            if (ganttProc[i] == compactProc.back()) {
                compactTime.back() = ganttTime[i];
            } else {
                compactProc.push_back(ganttProc[i]);
                compactTime.push_back(ganttTime[i]);
            }
        }
    }

    cout << "\nGantt Chart:\n";
    // Top bar
    for (size_t i = 0; i < compactProc.size(); i++) {
        cout << " ";
        int len = compactProc[i].size() + 2;
        for (int j = 0; j < len; j++) cout << "-";
    }
    cout << "\n";
    // Process names
    for (size_t i = 0; i < compactProc.size(); i++) {
        cout << "| " << compactProc[i] << " ";
    }
    cout << "|\n";
    // Bottom bar
    for (size_t i = 0; i < compactProc.size(); i++) {
        cout << " ";
        int len = compactProc[i].size() + 2;
        for (int j = 0; j < len; j++) cout << "-";
    }
    cout << "\n";
    // Time stamps
    int start = firstArrival;
    cout << start;
    for (size_t i = 0; i < compactTime.size(); i++) {
        int len = compactProc[i].size() + 2;
        cout << string(len, ' ') << compactTime[i];
    }
    cout << endl;
    return 0;
}