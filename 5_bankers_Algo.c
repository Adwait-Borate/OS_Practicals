#include <stdio.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int main() {
    // resources A,B,C
    int n = MAX_PROCESSES; // Fixed number of processes
    int A, B, C;           // Total resources

    printf("Enter the total Number of resources of each type (A,B,C): ");
    scanf("%d %d %d", &A, &B, &C);

    int allocate[MAX_PROCESSES][MAX_RESOURCES] = {0};                                //allocate
    printf("Enter Allocated resources: \n");
    for (int i = 0; i < n; i++) {
        printf("Enter the allocated resources for P%d\n", i + 1);
        for (int j = 0; j < MAX_RESOURCES; j++) {
            scanf("%d", &allocate[i][j]);
        }
    }

    int maxreq[MAX_PROCESSES][MAX_RESOURCES] = {0};                                   //maxreq
    printf("Enter Maximum Required resources: \n"); 
    for (int i = 0; i < n; i++) {
        printf("Enter the required resources for P%d\n", i + 1);
        for (int j = 0; j < MAX_RESOURCES; j++) {
            scanf("%d", &maxreq[i][j]);
        }
    }

    printf("Enter Currently Available resources of each type(A,B,C)\n");
    int ava, avb, avc;
    scanf("%d %d %d", &ava, &avb, &avc);
 
    int needed[MAX_PROCESSES][MAX_RESOURCES] = {0};                                   //needed  
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < MAX_RESOURCES; j++) {
            needed[i][j] = maxreq[i][j] - allocate[i][j];
        }
    }

    // Display the Allocation Matrix
    printf("\nAllocation Matrix:\n");
    printf("P\tA\tB\tC\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t", i + 1);
        for (int j = 0; j < MAX_RESOURCES; j++) {
            printf("%d\t", allocate[i][j]);
        }
        printf("\n");
    }

    // Display the Maximum Resources Matrix
    printf("\nMaximum Resources Matrix:\n");
    printf("P\tA\tB\tC\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t", i + 1);
        for (int j = 0; j < MAX_RESOURCES; j++) {
            printf("%d\t", maxreq[i][j]);
        }
        printf("\n");
    }

    // Display the Need Matrix
    printf("\nNeed Matrix:\n");
    printf("P\tA\tB\tC\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t", i + 1);
        for (int j = 0; j < MAX_RESOURCES; j++) {
            printf("%d\t", needed[i][j]);
        }
        printf("\n");
    }

    int processes[MAX_PROCESSES] = {0};
    int completed = 0;
    
    while (completed != n) {
        for (int i = 0; i < n; i++) {
            if ((needed[i][0] <= ava && needed[i][0] != -1) &&
                (needed[i][1] <= avb && needed[i][1] != -1) &&
                (needed[i][2] <= avc && needed[i][2] != -1)) {
                completed++;
                processes[completed - 1] = i + 1;                        // @Adwait-Borate
                ava += allocate[i][0];
                avb += allocate[i][1];
                avc += allocate[i][2];
                // Mark this process as completed by setting needed to -1
                for (int j = 0; j < MAX_RESOURCES; j++) {
                    needed[i][j] = -1;
                }
            }
        }
    }

    // Final output
    printf("\n\nCurrently Available Resources: \n");
    printf("%d %d %d\n", ava, avb, avc);
    
    printf("\nThe Order Of Completion of processes is: \n");
    for (int i = 0; i < n; i++) {
        printf("P%d->", processes[i]);
    }
    printf("\n");

    return 0;
}
