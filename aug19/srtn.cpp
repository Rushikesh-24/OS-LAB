#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct Process {
    int id, at, bt, rt, wt, tat, ct, start;
};

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "Process " << (i + 1) << " Arrival Time: ";
        cin >> p[i].at;
        cout << "Process " << (i + 1) << " Burst Time: ";
        cin >> p[i].bt;
        p[i].rt = p[i].bt;
        p[i].wt = 0;
        p[i].tat = 0;
        p[i].ct = 0;
        p[i].start = -1;
    }

    int min_at = p[0].at;
    for (int i = 1; i < n; i++) {
        if (p[i].at < min_at) min_at = p[i].at;
    }

    cout << "\nGantt Chart:\n ";
    int last_time = 0;
    int seg = 0;
    vector<int> chart_id, chart_time;
    chart_time.push_back(min_at);

    int completed = 0, current_time = min_at, prev = -1;
    vector<int> finish_time(n, -1);

    while (completed < n) {
        int idx = -1, min_rt = 1e9;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && p[i].rt > 0) {
                if (p[i].rt < min_rt) {
                    min_rt = p[i].rt;
                    idx = i;
                }
                if (p[i].rt == min_rt && p[i].at < p[idx].at) {
                    idx = i;
                }
            }
        }
        if (idx != -1) {
            if (seg == 0 || chart_id.empty() || chart_id.back() != idx) {
                if (seg == 0) chart_id.push_back(idx);
                else {
                    chart_id.push_back(idx);
                    chart_time.push_back(current_time);
                }
                seg++;
            }
            p[idx].rt--;
            current_time++;
            if (p[idx].rt == 0) {
                completed++;
            }
        } else {
            if (seg == 0 || chart_id.empty() || chart_id.back() != -1) {
                if (seg == 0) chart_id.push_back(-1);
                else {
                    chart_id.push_back(-1);
                    chart_time.push_back(current_time);
                }
                seg++;
            }
            current_time++;
        }
    }
    chart_time.push_back(current_time);

    // Calculate WT and TAT correctly
    for (int i = 0; i < n; i++) {
        p[i].rt = p[i].bt;
        finish_time[i] = -1;
    }
    completed = 0;
    current_time = min_at;
    while (completed < n) {
        int idx = -1, min_rt = 1e9;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && p[i].rt > 0) {
                if (p[i].rt < min_rt) {
                    min_rt = p[i].rt;
                    idx = i;
                }
                if (p[i].rt == min_rt && p[i].at < p[idx].at) {
                    idx = i;
                }
            }
        }
        if (idx != -1) {
            p[idx].rt--;
            current_time++;
            if (p[idx].rt == 0) {
                finish_time[idx] = current_time;
                completed++;
            }
        } else {
            current_time++;
        }
    }

    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        p[i].tat = finish_time[i] - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    // Print chart
    cout << " ";
    for (size_t k = 1; k < chart_time.size(); k++) {
        cout << "------";
    }
    cout << "\n|";
    for (size_t k = 1; k < chart_time.size(); k++) {
        if (chart_id[k-1] == -1)
            cout << "     |";
        else
            cout << " P" << p[chart_id[k-1]].id << "  |";
    }
    cout << "\n ";
    for (size_t k = 1; k < chart_time.size(); k++) {
        cout << "------";
    }
    cout << "\n";
    // Print time markers
    for (size_t k = 0; k < chart_time.size(); k++) {
        cout << setw(6) <<left<< chart_time[k];
    }
    cout << "\n";

    cout << "\nProcess\tAT\tBT\tWT\tTAT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << p[i].id << "\t" << p[i].at << "\t" << p[i].bt << "\t" << p[i].wt << "\t" << p[i].tat << endl;
    }
    cout << "\nAverage Waiting Time: " << fixed << setprecision(2) << total_wt / n << endl;
    cout << "Average Turnaround Time: " << fixed << setprecision(2) << total_tat / n << endl;

    return 0;
}