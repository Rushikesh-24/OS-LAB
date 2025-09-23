#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int pid, at, bt, prio, wt, tat, ct;
};

bool cmp(Process a, Process b) {
    if (a.at == b.at)
        return a.prio < b.prio; 
    return a.at < b.at;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "Arrival time for P" << i+1 << ": ";
        cin >> p[i].at;
        cout << "Burst time for P" << i+1 << ": ";
        cin >> p[i].bt;
        cout << "Priority for P" << i+1 << ": ";
        cin >> p[i].prio;
    }

    // Preemptive Priority Scheduling
    int time = 0, completed = 0;
    vector<int> rem_bt(n);
    for (int i = 0; i < n; i++) rem_bt[i] = p[i].bt;
    vector<bool> done(n, false);
    vector<pair<int, pair<int,int>>> gantt;

    int last_idx = -1, start_time = 0;
    while (completed < n) {
        int idx = -1, min_prio = 1e9;
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= time && p[i].prio < min_prio && rem_bt[i] > 0) {
                min_prio = p[i].prio;
                idx = i;
            }
        }
        if (idx == -1) {
            time++;
            continue;
        }
        // Context switch: if process changes, record previous
        if (last_idx != idx) {
            if (last_idx != -1 && start_time != time) {
                gantt.push_back({p[last_idx].pid, {start_time, time}});
            }
            start_time = time;
            last_idx = idx;
        }
        rem_bt[idx]--;
        time++;
        if (rem_bt[idx] == 0) {
            completed++;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            done[idx] = true;
        }
    }
    // Record last process in Gantt chart
    if (last_idx != -1 && start_time != time) {
        gantt.push_back({p[last_idx].pid, {start_time, time}});
    }

    vector<Process> result = p;
    sort(result.begin(), result.end(), [](const Process &a, const Process &b) { return a.pid < b.pid; });
    cout << "\n( Assuming Lower Number = Higher Priority)\nProcess\tAT\tBT\tPRIO\tWT\tTAT\n";
    float total_wt = 0, total_tat = 0;
    for (auto &proc : result) {
        cout << "P" << proc.pid << "\t" << proc.at << "\t" << proc.bt << "\t" 
             << proc.prio << "\t" << proc.wt << "\t" << proc.tat << endl;
        total_wt += proc.wt;
        total_tat += proc.tat;
    }
    cout << "\nAverage Waiting Time: " << total_wt/n << endl;
    cout << "Average Turnaround Time: " << total_tat/n << endl;

    cout << "\nGantt Chart:\n ";
    for (auto &g : gantt) {
        cout << "--------" ;
    }
    cout << "\n ";
    for (auto &g : gantt) {
        cout << "|  P " << g.first << "  ";
    }
    cout << "|\n ";
    for (auto &g : gantt) {
        cout << "--------" ;
    }
    cout << "\n ";
    for (auto &g : gantt) {
        cout << g.second.first << "\t";
    }
    cout << gantt.back().second.second << "\n";

    return 0;
}