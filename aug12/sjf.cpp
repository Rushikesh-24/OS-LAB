#include<iostream>
using namespace std;

struct Process {
    int id;
    int bt;
    int at;
    int wt;
    int tat;
};

bool cmp(Process a, Process b) {
    return a.at < b.at;
}

int main(){
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    Process p[n];

    cout << "Enter the arrival and burst time for each process:\n";
    for(int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "Process " << (i + 1) << " Arrival Time: ";
        cin >> p[i].at;
        cout << "Process " << (i + 1) << " Burst Time: ";
        cin >> p[i].bt;
    }

    vector<bool> completed(n, false);
    int completed_count = 0;
    int current_time = 0;
    int idle_times[100] = {0};
    Process sjf_order[100];
    int sjf_idx = 0;
    while(completed_count < n) {
        int idx = -1;
        int min_bt = 1e9;
        for(int i = 0; i < n; i++) {
            if(!completed[i] && p[i].at <= current_time) {
                if(p[i].bt < min_bt) {
                    min_bt = p[i].bt;
                    idx = i;
                }
            }
        }
        if(idx == -1) {
            int next_at = 1e9;
            for(int i = 0; i < n; i++) {
                if(!completed[i] && p[i].at < next_at) {
                    next_at = p[i].at;
                }
            }
            idle_times[sjf_idx] = next_at - current_time;
            current_time = next_at;
            continue;
        }
        idle_times[sjf_idx] = 0;
        p[idx].wt = current_time - p[idx].at;
        current_time += p[idx].bt;
        p[idx].tat = p[idx].wt + p[idx].bt;
        completed[idx] = true;
        sjf_order[sjf_idx] = p[idx];
        sjf_idx++;
        completed_count++;
    }

    float total_wt = 0, total_tat = 0;
    cout << "\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for(int i = 0; i < n; i++) {
        cout << "P" << sjf_order[i].id << "\t" << sjf_order[i].at << "\t\t" << sjf_order[i].bt << "\t\t" << sjf_order[i].wt << "\t\t" << sjf_order[i].tat << endl;
        total_wt += sjf_order[i].wt;
        total_tat += sjf_order[i].tat;
    }
    cout << "\nAverage Waiting Time: " << total_wt/n << endl;
    cout << "Average Turnaround Time: " << total_tat/n << endl;
    cout << "Gantt Chart:\n ";
    
    for(int i = 0; i < n; i++) {
        if(idle_times[i] > 0) cout << "--------";
        cout << "-------";
    }
    cout << "\n ";
    
    for(int i = 0; i < n; i++) {
        if(idle_times[i] > 0) cout << "|       ";
        cout << "| P" << sjf_order[i].id << "   ";
    }
    cout << "|\n ";
    
    for(int i = 0; i < n; i++) {
        if(idle_times[i] > 0) cout << "--------";
        cout << "-------";
    }
    cout << "\n ";
    
    int time_marker = 0;
    cout << time_marker+1;
    for(int i = 0; i < n; i++) {
        if(idle_times[i] > 0) {
            time_marker += idle_times[i];
            printf("%7d", time_marker+1);
        }
        time_marker += sjf_order[i].bt;
        printf("%7d", time_marker+1);
    }
    cout << endl;
    return 0;
}