#include <algorithm>
#include<iostream>
using namespace std;
struct Process {
    string name;
    int burst_time;
    int arrival_time;
};
int main(){
    int n;
    cout<<"Enter the number of processes: ";
    cin>>n;
    Process process[n];
    for(int i=0; i<n; i++){
        cout<<"Enter process name, burst time and arrival time: ";
        cin>>process[i].name>>process[i].burst_time>>process[i].arrival_time;
    }
    sort(process, process+n, [](Process a, Process b) {
        return a.arrival_time < b.arrival_time;
    });
    int waiting_time[n], turnaround_time[n];
    waiting_time[0] = 0;
    turnaround_time[0] = process[0].burst_time;
    for(int i=1; i<n; i++){
        waiting_time[i] = waiting_time[i-1] + process[i-1].burst_time;
        turnaround_time[i] = waiting_time[i] + process[i].burst_time;

        if (process[i].arrival_time > waiting_time[i]) {
            waiting_time[i] = process[i].arrival_time;
            turnaround_time[i] = waiting_time[i] + process[i].burst_time;
        }
    }
    cout<<"Process\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n";
    for(int i=0; i<n; i++){
        cout<<process[i].name<<"\t"<<process[i].burst_time<<"\t\t"<<process[i].arrival_time<<"\t\t"<<waiting_time[i]<<"\t\t"<<turnaround_time[i]<<"\n";
    }
    float avg_waiting_time = 0, avg_turnaround_time = 0;
    for(int i=0; i<n; i++){
        avg_waiting_time += waiting_time[i];
        avg_turnaround_time += turnaround_time[i];
    }
    avg_waiting_time /= n;
    avg_turnaround_time /= n;
    cout<<"Average Waiting Time: "<<avg_waiting_time<<"\n";
    cout<<"Average Turnaround Time: "<<avg_turnaround_time<<"\n";
    return 0;
}