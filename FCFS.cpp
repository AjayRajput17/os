#include <stdio.h>

void findWaitingTime(int processes[], int n, int bt[], int wt[]) {
    // Waiting time for the first process is 0
    wt[0] = 0;

    // Calculate waiting time for the rest
    for (int i = 1; i < n; i++) {
        wt[i] = bt[i - 1] + wt[i - 1];
    }
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    // Calculate turnaround time = burst time + waiting time
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

void findAverageTime(int processes[], int n, int bt[]) {
    int wt[n], tat[n]; // Waiting time and Turnaround time arrays
    int total_wt = 0, total_tat = 0;

    // Find waiting times
    findWaitingTime(processes, n, bt, wt);

    // Find turnaround times
    findTurnAroundTime(processes, n, bt,wt ,tat);

    // Display process information
    printf("Processes\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i], bt[i], wt[i], tat[i]);
    }

    // Calculate and display averages
    printf("Average waiting time = %.2f\n", (float)total_wt / n);
    printf("Average turnaround time = %.2f\n", (float)total_tat / n);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n], burst_time[n];

    printf("Enter burst times for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        printf("Process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }

    findAverageTime(processes, n, burst_time);

    return 0;
}
