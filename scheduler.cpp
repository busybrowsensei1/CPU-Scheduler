#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

struct Process {
    int id;
    int arrival_time;
    int serve_time;
    int finish_time;
    int response_time;
    int waiting_time;
    int start_time;
    int priority;
    int turnaround_time; // New field for turnaround time
};

void SRTF(int n, vector<Process> &processes) {
    auto cmp = [](Process a, Process b) { return a.serve_time > b.serve_time; };
    priority_queue<Process, vector<Process>, decltype(cmp)> pq(cmp);
    int time = 0, i = 0, completed = 0;
    while (completed < n) {
        while (i < n && processes[i].arrival_time <= time) {
            pq.push(processes[i]);
            i++;
        }
        if (!pq.empty()) {
            Process p = pq.top();
            pq.pop();
            p.start_time = time;
            p.serve_time--; // Decrease serve time for SRTF
            time++; // Increment time for each unit of service
            if (p.serve_time == 0) {
                p.finish_time = time;
                p.response_time = p.finish_time - p.arrival_time;
                p.waiting_time = p.response_time - p.serve_time;
                p.turnaround_time = p.finish_time - p.arrival_time; // Calculate turnaround time
                processes[p.id - 1] = p;
                completed++;
            } else {
                pq.push(p); // Push back for remaining service time
            }
        } else {
            time = processes[i].arrival_time;
        }
    }
}

void FCFS(int n, vector<Process> &processes) {
    int time = 0;
    for (int i = 0; i < n; i++) {
        processes[i].start_time = max(time, processes[i].arrival_time);
        time = processes[i].start_time + processes[i].serve_time;
        processes[i].finish_time = time;
        processes[i].response_time = processes[i].finish_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].response_time - processes[i].serve_time;
        processes[i].turnaround_time = processes[i].finish_time - processes[i].arrival_time; // Calculate turnaround time
    }
}

void SJN(int n, vector<Process> &processes) {
    auto cmp = [](Process a, Process b) { return a.serve_time > b.serve_time; };
    priority_queue<Process, vector<Process>, decltype(cmp)> pq(cmp);
    int time = 0, i = 0, completed = 0;
    while (completed < n) {
        while (i < n && processes[i].arrival_time <= time) {
            pq.push(processes[i]);
            i++;
        }
        if (!pq.empty()) {
            Process p = pq.top();
            pq.pop();
            p.start_time = time;
            time += p.serve_time;
            p.finish_time = time;
            p.response_time = p.finish_time - p.arrival_time;
            p.waiting_time = p.response_time - p.serve_time;
            p.turnaround_time = p.finish_time - p.arrival_time; // Calculate turnaround time
            processes[p.id - 1] = p;
            completed++;
        } else {
            time = processes[i].arrival_time;
        }
    }
}

void PriorityScheduling(int n, vector<Process> &processes) {
    auto cmp = [](Process a, Process b) { return a.priority > b.priority; };
    priority_queue<Process, vector<Process>, decltype(cmp)> pq(cmp);
    int time = 0, i = 0, completed = 0;
    while (completed < n) {
        while (i < n && processes[i].arrival_time <= time) {
            pq.push(processes[i]);
            i++;
        }
        if (!pq.empty()) {
            Process p = pq.top();
            pq.pop();
            p.start_time = time;
            time += p.serve_time;
            p.finish_time = time;
            p.response_time = p.finish_time - p.arrival_time;
            p.waiting_time = p.response_time - p.serve_time;
            p.turnaround_time = p.finish_time - p.arrival_time; // Calculate turnaround time
            processes[p.id - 1] = p;
            completed++;
        } else {
            time = processes[i].arrival_time;
        }
    }
}

void RoundRobin(int n, vector<Process> &processes, int quantum) {
    queue<Process> q;
    vector<int> remaining_time(n);
    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].serve_time;
    }
    int time = 0, i = 0, completed = 0;
    while (completed < n) {
        while (i < n && processes[i].arrival_time <= time) {
            q.push(processes[i]);
            i++;
        }
        if (!q.empty()) {
            Process p = q.front();
            q.pop();
            if (remaining_time[p.id - 1] == processes[p.id - 1].serve_time) {
                processes[p.id - 1].start_time = time;
            }
            int served_time = min(quantum, remaining_time[p.id - 1]);
            remaining_time[p.id - 1] -= served_time;
            time += served_time;
            if (remaining_time[p.id - 1] == 0) {
                processes[p.id - 1].finish_time = time;
                processes[p.id - 1].response_time = processes[p.id - 1].finish_time - processes[p.id - 1].arrival_time;
                processes[p.id - 1].waiting_time = processes[p.id - 1].response_time - processes[p.id - 1].serve_time;
                processes[p.id - 1].turnaround_time = processes[p.id - 1].finish_time - processes[p.id - 1].arrival_time; // Calculate turnaround time
                completed++;
            } else {
                while (i < n && processes[i].arrival_time <= time) {
                    q.push(processes[i]);
                    i++;
                }
                q.push(p);
            }
        } else {
            time = processes[i].arrival_time;
        }
    }
}

int main(int argc, char *argv[]) {
    string algo = argv[1];
    int n;
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cin >> processes[i].arrival_time >> processes[i].serve_time;
        if (algo == "priority") {
            cin >> processes[i].priority;
        }
    }

    if (algo == "fcfs") {
        FCFS(n, processes);
    } else if (algo == "sjf") {
        sort(processes.begin(), processes.end(), [](Process a, Process b) {
            return a.arrival_time < b.arrival_time;
        });
        SJN(n, processes);
    } else if (algo == "srtf") {
        sort(processes.begin(), processes.end(), [](Process a, Process b) {
            return a.arrival_time < b.arrival_time;
        });
        SRTF(n, processes);
    } else if (algo == "priority") {
        sort(processes.begin(), processes.end(), [](Process a, Process b) {
            return a.arrival_time < b.arrival_time;
        });
        PriorityScheduling(n, processes);
    } else if (algo == "round_robin") {
        int quantum;
        cin >> quantum;
        sort(processes.begin(), processes.end(), [](Process a, Process b) {
            return a.arrival_time < b.arrival_time;
        });
        RoundRobin(n, processes, quantum);
    }

    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int last_finish_time = 0;

    cout << "\n\tArrival time\tServe time\tFinish time\tResponse time\tWaiting time\tTurnaround time\n";
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
        last_finish_time = max(last_finish_time, processes[i].finish_time);
        cout << "P" << processes[i].id << ": \t" << processes[i].arrival_time << "\t\t" << processes[i].serve_time << "\t\t" << processes[i].finish_time << "\t\t" << processes[i].response_time << "\t\t" << processes[i].waiting_time << "\t\t" << processes[i].turnaround_time << "\n";
    }
    cout << "\nAverage waiting time: " << total_waiting_time / n << "\n";
    cout << "Average turnaround time: " << total_turnaround_time / n << "\n";
    cout << "Throughput: " << n / (double)last_finish_time << " processes per unit time\n";

    // Output Gantt chart data
    for (int i = 0; i < n; i++) {
        cout << "P" << processes[i].id << " " << processes[i].start_time << " " << processes[i].finish_time << "\n";
    }

    return 0;
}
