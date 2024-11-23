#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

struct Process {
    int pid;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int memory_size;
};

sem_t memory_lock;

void findWaitingTime(struct Process proc[], int n) {
    proc[0].waiting_time = 0;
    for (int i = 1; i < n; i++) {
        proc[i].waiting_time = proc[i - 1].waiting_time + proc[i - 1].burst_time;
    }
}

void findTurnaroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
    }
}

void allocateMemory(struct Process *proc) {
    sem_wait(&memory_lock);
    printf("Allocating %dMB memory for process %d\n", proc->memory_size, proc->pid);
}

void releaseMemory(struct Process *proc) {
    printf("Releasing %dMB memory for process %d\n", proc->memory_size, proc->pid);
    sem_post(&memory_lock);
}

void* processExecution(void *arg) {
    struct Process *proc = (struct Process*)arg;
    allocateMemory(proc);
    printf("Process %d is executing...\n", proc->pid);
    releaseMemory(proc);
    return NULL;
}

void FCFS(struct Process proc[], int n) {
    pthread_t threads[n];
    int total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++) {
        pthread_create(&threads[i], NULL, processExecution, (void*)&proc[i]);
        pthread_join(threads[i], NULL);
    }

    findWaitingTime(proc, n);
    findTurnaroundTime(proc, n);

    printf("\nProcessID\tBurstTime\tWaitingTime\tTurnaroundTime\tMemory\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%dMB\n", proc[i].pid, proc[i].burst_time,
            proc[i].waiting_time, proc[i].turnaround_time, proc[i].memory_size);
        total_wt += proc[i].waiting_time;
        total_tat += proc[i].turnaround_time;
    }

    float avg_wt = (float)total_wt / n;
    float avg_tat = (float)total_tat / n;

    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);
}

int main() {
    sem_init(&memory_lock, 0, 1);

    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter burst time and memory size for process %d: ", proc[i].pid);
        scanf("%d%d", &proc[i].burst_time, &proc[i].memory_size);
    }

    FCFS(proc, n);

    sem_destroy(&memory_lock);

    return 0;
}

/*
Enter number of processes: 3
Enter burst time and memory size for process 1: 4 10
Enter burst time and memory size for process 2: 2 15
Enter burst time and memory size for process 3: 5 20
*/

