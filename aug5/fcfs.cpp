#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
struct Process {
    string name;
    int burst_time;
    int arrival_time;
    int completion_time = 0;
    int waiting_time = 0;
    int turnaround_time = 0;
};

bool compareArrival(const Process& a, const Process& b) {
    return a.arrival_time < b.arrival_time;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        cout << "Enter process name, burst time, and arrival time: ";
        cin >> processes[i].name >> processes[i].burst_time >> processes[i].arrival_time;
    }
    sort(processes.begin(), processes.end(), compareArrival);

    int current_time = 0;
    for (int i = 0; i < n; ++i) {
        if (processes[i].arrival_time > current_time) {
            current_time = processes[i].arrival_time;
        }

        processes[i].completion_time = current_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        
        current_time = processes[i].completion_time;
    }

    cout << "\n--- Process Execution Summary ---\n";
    cout << "Process\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    cout << "---------------------------------------------------------\n";
    for (const auto& p : processes) {
        cout << p.name << "\t" << p.arrival_time << "\t" << p.burst_time << "\t"
             << p.completion_time << "\t\t" << p.turnaround_time << "\t\t" << p.waiting_time << "\n";
    }

    double total_waiting_time = 0;
    double total_turnaround_time = 0;
    for (const auto& p : processes) {
        total_waiting_time += p.waiting_time;
        total_turnaround_time += p.turnaround_time;
    }
    cout << "\nAverage Waiting Time: " << total_waiting_time / n << endl;
    cout << "Average Turnaround Time: " << total_turnaround_time / n << endl;

    cout << "\n--- Gantt Chart ---\n";

    int current_gantt_time = 0;

    current_gantt_time = 0;
    for (const auto& p : processes) {
        if (p.arrival_time > current_gantt_time) {
            int idle_len = p.arrival_time - current_gantt_time;
            cout << "     ";
            for (int i = 0; i < idle_len * 2 - 5; ++i) cout << " ";
            cout << "|";
            current_gantt_time = p.arrival_time;
        }
        cout << " " << p.name << " ";
        for (int i = 0; i < p.burst_time * 2 - (int)p.name.length() - 2; ++i) cout << " ";
        cout << "|";
        current_gantt_time += p.burst_time;
    }
    cout << "\n ";

    current_gantt_time = 0;
    cout << "0";
    for (const auto& p : processes) {
        if (p.arrival_time > current_gantt_time) {
            int idle_len = p.arrival_time - current_gantt_time;
            cout.width(idle_len * 2 + 1);
            cout << right << p.arrival_time;
            current_gantt_time = p.arrival_time;
        }
        cout.width(p.burst_time * 2 + 1);
        cout << right << (current_gantt_time + p.burst_time);
        current_gantt_time += p.burst_time;
    }
    cout << endl;
    return 0;
}