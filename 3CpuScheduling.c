#include <stdio.h>
#include <stdbool.h>

struct Process {
    int id, arrival, burst, remaining, completion, wait, turnaround;
};

void SJF_Preemptive(struct Process p[], int n) {
    int time = 0, completed = 0, shortest;
    float total_wait = 0, total_turnaround = 0;

    while (completed < n) {
        shortest = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0 &&
                (shortest == -1 || p[i].remaining < p[shortest].remaining))
                shortest = i;
        }

        if (shortest == -1) { time++; continue; }

        p[shortest].remaining--;
        time++;

        if (p[shortest].remaining == 0) {
            completed++;
            p[shortest].completion = time;
            p[shortest].turnaround = time - p[shortest].arrival;
            p[shortest].wait = p[shortest].turnaround - p[shortest].burst;
            total_wait += p[shortest].wait;
            total_turnaround += p[shortest].turnaround;
        }
    }

    printf("\nSJF (Preemptive):\nPID\tArr\tBurst\tComp\tWait\tTurn\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].arrival, p[i].burst, p[i].completion, p[i].wait, p[i].turnaround);

    printf("Avg Wait Time: %.2f, Avg Turnaround Time: %.2f\n", total_wait / n, total_turnaround / n);
}

void RoundRobin(struct Process p[], int n, int quantum) {
    int time = 0, completed = 0;
    float total_wait = 0, total_turnaround = 0;

    while (completed < n) {
        bool idle = true;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0) {
                idle = false;
                int exec_time = (p[i].remaining > quantum) ? quantum : p[i].remaining;
                time += exec_time;
                p[i].remaining -= exec_time;

                if (p[i].remaining == 0) {
                    p[i].completion = time;
                    p[i].turnaround = time - p[i].arrival;
                    p[i].wait = p[i].turnaround - p[i].burst;
                    total_wait += p[i].wait;
                    total_turnaround += p[i].turnaround;
                    completed++;
                }
            }
        }
        if (idle) time++;
    }

    printf("\nRound Robin:\nPID\tArr\tBurst\tComp\tWait\tTurn\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].arrival, p[i].burst, p[i].completion, p[i].wait, p[i].turnaround);

    printf("Avg Wait Time: %.2f, Avg Turnaround Time: %.2f\n", total_wait / n, total_turnaround / n);
}

int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter arrival and burst time for P%d: ", i + 1);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].remaining = p[i].burst;
    }

    printf("Enter time quantum for Round Robin: ");
    scanf("%d", &quantum);

    SJF_Preemptive(p, n);

    // Reset remaining time for Round Robin
    for (int i = 0; i < n; i++) p[i].remaining = p[i].burst;

    RoundRobin(p, n, quantum);
    return 0;
}
