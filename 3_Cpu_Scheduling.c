#include <stdio.h>
#include <stdbool.h>

struct Process {
    int id, arrival, burst, remaining, completion, wait, turnaround;
};

void print_gantt_chart(int gantt_chart[], int gantt_count) {
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < gantt_count; i++) {
        printf(" P%d |", gantt_chart[i]);
    }
    printf("\n");
    printf("0");  // Start time
    for (int i = 1; i <= gantt_count; i++) {
        printf("  %d", i);  // Time labels under each process
    }
    printf("\n");
}

void SJF_Preemptive(struct Process p[], int n) {
    int time = 0, completed = 0, shortest; // Initialize time, completed processes count, and shortest process index
    float total_wait = 0, total_turnaround = 0; // Initialize total wait and turnaround times
    int gantt_chart[1000];  // Gantt chart log for SJF
    int gantt_count = 0; // Counter for Gantt chart entries

    while (completed < n) { // Loop until all processes are completed
        shortest = -1; // Reset shortest process index
        for (int i = 0; i < n; i++) { // Iterate through all processes
            // Check if process has arrived, is remaining, and is shorter than the current shortest
            if (p[i].arrival <= time && p[i].remaining > 0 &&
                (shortest == -1 || p[i].remaining < p[shortest].remaining))
                shortest = i; // Update the shortest process index
        }

        if (shortest == -1) { time++; continue; } // If no process is available, increment time and continue

        p[shortest].remaining--; // Decrement remaining time for the selected process
        gantt_chart[gantt_count++] = p[shortest].id; // Record the process ID in the Gantt chart
        time++; // Increment the current time

        if (p[shortest].remaining == 0) { // Check if the selected process has completed
            completed++; // Increment the completed processes count
            p[shortest].completion = time; // Set completion time for the process
            p[shortest].turnaround = time - p[shortest].arrival; // Calculate turnaround time
            p[shortest].wait = p[shortest].turnaround - p[shortest].burst; // Calculate waiting time
            total_wait += p[shortest].wait; // Accumulate total wait time
            total_turnaround += p[shortest].turnaround; // Accumulate total turnaround time
        }
    }

    // Print results
    printf("\nSJF (Preemptive):\nPID\tArr\tBurst\tComp\tWait\tTurn\n");
    for (int i = 0; i < n; i++) // Iterate through all processes to display their info
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].arrival, p[i].burst, p[i].completion, p[i].wait, p[i].turnaround);

    // Print average wait and turnaround times
    printf("Avg Wait Time: %.2f, Avg Turnaround Time: %.2f\n", total_wait / n, total_turnaround / n);
    print_gantt_chart(gantt_chart, gantt_count); // Call function to print the Gantt chart
}


void RoundRobin(struct Process p[], int n, int quantum) {
    int time = 0, completed = 0;
    float total_wait = 0, total_turnaround = 0;
    int gantt_chart[1000];  // Gantt chart log for Round Robin
    int gantt_count = 0;

    while (completed < n) {
        bool idle = true;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0) {
                idle = false;
                int exec_time = (p[i].remaining > quantum) ? quantum : p[i].remaining;
                

                p[i].remaining -= exec_time;
                for (int j = 0; j < exec_time; j++) {
                    gantt_chart[gantt_count++] = p[i].id; // Record for Gantt chart
                }
                time += exec_time;
                
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
        if (idle) {
            gantt_chart[gantt_count++] = -1; // Mark idle time in Gantt chart
            time++;
        }
    }

    printf("\nRound Robin:\nPID\tArr\tBurst\tComp\tWait\tTurn\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].arrival, p[i].burst, p[i].completion, p[i].wait, p[i].turnaround);

    printf("Avg Wait Time: %.2f, Avg Turnaround Time: %.2f\n", total_wait / n, total_turnaround / n);
    print_gantt_chart(gantt_chart, gantt_count);
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
