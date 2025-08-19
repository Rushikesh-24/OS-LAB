#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

struct Process {
    string name;
    int burst_time;
    int arrival_time;
    int start_time = 0;
    int completion_time = 0;
    int waiting_time = 0;
    int turnaround_time = 0;
    bool is_completed = false;
};

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        cout << "Enter process name, burst time, and arrival time for process " << i + 1 << ": ";
        cin >> processes[i].name >> processes[i].burst_time >> processes[i].arrival_time;
    }

    vector<Process> gantt_chart_sequence;

    int current_time = 0;
    int completed_count = 0;

    while (completed_count < n) {
        int shortest_burst = numeric_limits<int>::max();
        int shortest_job_index = -1;

        for (int i = 0; i < n; ++i) {
            if (!processes[i].is_completed && processes[i].arrival_time <= current_time) {
                if (processes[i].burst_time < shortest_burst) {
                    shortest_burst = processes[i].burst_time;
                    shortest_job_index = i;
                } else if (processes[i].burst_time == shortest_burst) {
                    if (shortest_job_index != -1 && processes[i].arrival_time < processes[shortest_job_index].arrival_time) {
                        shortest_job_index = i;
                    }
                }
            }
        }

        if (shortest_job_index == -1) {
            int next_arrival_time = numeric_limits<int>::max();
            bool found_uncompleted = false;

            for (int i = 0; i < n; ++i) {
                if (!processes[i].is_completed) {
                    if (processes[i].arrival_time < next_arrival_time) {
                        next_arrival_time = processes[i].arrival_time;
                    }
                    found_uncompleted = true;
                }
            }

            if (!found_uncompleted) {
                break;
            }

            if (next_arrival_time > current_time) {
                current_time = next_arrival_time;
                continue;
            }
        }

        Process& current_process = processes[shortest_job_index];

        current_process.start_time = current_time;
        current_process.completion_time = current_time + current_process.burst_time;
        current_process.turnaround_time = current_process.completion_time - current_process.arrival_time;
        current_process.waiting_time = current_process.turnaround_time - current_process.burst_time;
        
        current_process.is_completed = true;
        completed_count++;
        gantt_chart_sequence.push_back(current_process);

        current_time = current_process.completion_time;
    }

    cout << "\n--- Process Execution Summary (SJF Non-Preemptive) ---\n";
    cout << "Process\tArrival\tBurst\tStart\tCompletion\tTurnaround\tWaiting\n";
    cout << "----------------------------------------------------------------------\n";
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival_time < b.arrival_time;
    });
    for (const auto& p : processes) {
        cout << p.name << "\t" << p.arrival_time << "\t" << p.burst_time << "\t"
             << p.start_time << "\t" << p.completion_time << "\t\t"
             << p.turnaround_time << "\t\t" << p.waiting_time << "\n";
    }

    double total_waiting_time = 0;
    double total_turnaround_time = 0;
    for (const auto& p : processes) {
        total_waiting_time += p.waiting_time;
        total_turnaround_time += p.turnaround_time;
    }
    cout << "\nAverage Waiting Time: " << total_waiting_time / n << endl;
    cout << "Average Turnaround Time: " << total_turnaround_time / n << endl;

    cout << "\n--- Gantt Chart (SJF Non-Preemptive) ---\n";
    
    const int unit_display_width = 3;

    cout << " ";
    int current_gantt_pos = 0;
    for (const auto& p : gantt_chart_sequence) {
        if (p.start_time > current_gantt_pos) {
            int idle_duration = p.start_time - current_gantt_pos;
            cout << string(idle_duration * unit_display_width, '-') << " ";
        }
        cout << string(p.burst_time * unit_display_width, '-') << " ";
        current_gantt_pos = p.completion_time;
    }
    cout << "\n";

    cout << "|";
    current_gantt_pos = 0;
    for (const auto& p : gantt_chart_sequence) {
        if (p.start_time > current_gantt_pos){
            int idle_duration = p.start_time - current_gantt_pos;
            string idle_text = "    ";
            int idle_width = idle_duration * unit_display_width;
            if (idle_width >= (int)idle_text.length()) {
                int padding = (idle_width - idle_text.length()) / 2;
                cout << string(padding, ' ') << idle_text << string(idle_width - idle_text.length() - padding, ' ') << "|";
            } else {
                cout << string(idle_width, ' ') << "|";
            }
        }
        string process_text = p.name;
        int padding = (p.burst_time * unit_display_width - process_text.length()) / 2;
        cout << string(padding, ' ') << process_text << string(p.burst_time * unit_display_width - process_text.length() - padding, ' ') << "|";
        current_gantt_pos = p.completion_time;
    }
    cout << "\n";

    cout << " ";
    current_gantt_pos = 0;
    for (const auto& p : gantt_chart_sequence) {
        if (p.start_time > current_gantt_pos) {
            int idle_duration = p.start_time - current_gantt_pos;
            cout << string(idle_duration * unit_display_width, '-') << " ";
        }
        cout << string(p.burst_time * unit_display_width, '-') << " ";
        current_gantt_pos = p.completion_time;
    }
    cout << "\n";

    cout << "0";
    current_gantt_pos = 0;
    for (const auto& p : gantt_chart_sequence) {
        if (p.start_time > current_gantt_pos) {
            int idle_duration = p.start_time - current_gantt_pos;
            int offset = (idle_duration * unit_display_width) - to_string(p.start_time).length();
            cout << string(max(1, offset), ' ') << p.start_time;
            current_gantt_pos = p.start_time;
        }
        int offset = (p.completion_time - current_gantt_pos) * unit_display_width - to_string(p.completion_time).length();
        cout << string(max(1, offset), ' ') << p.completion_time;
        current_gantt_pos = p.completion_time;
    }
    cout << "\n";

    return 0;
}
