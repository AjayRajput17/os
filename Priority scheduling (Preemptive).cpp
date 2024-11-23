#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;
    int burst_time;
    int arrival_time;
    int priority;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
};

void findWaitingAndTurnaroundTime(struct Process proc[], int n) {
    int current_time = 0, completed = 0, min_priority_idx;
    int total_wt = 0, total_tat = 0;

    // Initialize remaining time for all processes
    for (int i = 0; i < n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
    }

    while (completed < n) {
        min_priority_idx = -1;
        int min_priority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (proc[i].arrival_time <= current_time && proc[i].remaining_time > 0) {
                if (proc[i].priority < min_priority) {
                    min_priority = proc[i].priority;
                    min_priority_idx = i;
                }
            }
        }

        if (min_priority_idx != -1) {
            proc[min_priority_idx].remaining_time--;
            current_time++;

            if (proc[min_priority_idx].remaining_time == 0) {
                proc[min_priority_idx].completion_time = current_time;
                proc[min_priority_idx].turnaround_time = proc[min_priority_idx].completion_time - proc[min_priority_idx].arrival_time;
                proc[min_priority_idx].waiting_time = proc[min_priority_idx].turnaround_time - proc[min_priority_idx].burst_time;
                
                total_wt += proc[min_priority_idx].waiting_time;
                total_tat += proc[min_priority_idx].turnaround_time;
                completed++;
            }
        } else {
            current_time++; // If no process is ready, increase time
        }
    }

    printf("\nPreemptive Priority Scheduling\n");
    printf("Process ID\tArrival Time\tBurst Time\tPriority\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t%d\t%d\n",
               proc[i].pid, proc[i].arrival_time, proc[i].burst_time,
               proc[i].priority, proc[i].completion_time, proc[i].turnaround_time,
               proc[i].waiting_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time, burst time, and priority for process %d: ", proc[i].pid);
        scanf("%d %d %d", &proc[i].arrival_time, &proc[i].burst_time, &proc[i].priority);
    }

    findWaitingAndTurnaroundTime(proc, n);

    return 0;
}


/*Enter number of processes: 3
Enter arrival time, burst time, and priority for process 1: 0 5 2
Enter arrival time, burst time, and priority for process 2: 1 3 1
Enter arrival time, burst time, and priority for process 3: 2 4 3
*/
