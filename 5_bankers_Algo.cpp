#include <iostream>
using namespace std;

int main() {
    int p, r; // Number of processes and resources

    // Define maximum processes and resources
    p = 5;  // Number of processes (fixed to 5)
    r = 3;  // Number of resources (fixed to 3)

    // Allocation and Maximum Demand matrices, initialized as arrays
    int alloc[5][3]; // Allocation matrix: current resource allocation for each process
    int max[5][3];   // Maximum demand matrix: max resources each process may request
    int avail[3];    // Available resources: resources currently available in the system

    // Input Allocation matrix from user
    cout << "Enter the allocation matrix:\n";
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            cout << "Allocation for P" << i << ", R" << j << ": ";
            cin >> alloc[i][j];
        }
    }

    // Input Maximum Demand matrix from user
    cout << "Enter the maximum demand matrix:\n";
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            cout << "Maximum demand for P" << i << ", R" << j << ": ";
            cin >> max[i][j];
        }
    }

    // Input Available resources from user
    cout << "Enter the available resources:\n";
    for (int j = 0; j < r; j++) {
        cout << "Available units of R" << j << ": ";
        cin >> avail[j];
    }

    // Initialize arrays to track process completion and safe sequence
    int completed[5] = { 0 }; // Completion status for each process
    int safeSeq[5];           // Safe sequence of processes (order in which processes can safely execute)
    int index = 0;            // Index for inserting into safe sequence

    // Calculate the Need matrix
    int need[5][3]; // Need matrix: remaining resources each process requires
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            need[i][j] = max[i][j] - alloc[i][j]; // Calculate need as max - allocated
        }
    }

    // Banker's Algorithm to find a safe sequence, if it exists
    for (int count = 0; count < p; count++) {
        // Try to find a process that can safely proceed
        for (int i = 0; i < p; i++) {
            if (completed[i] == 0) { // Process is not yet completed
                bool canProceed = true;

                // Check if all required resources are available
                for (int j = 0; j < r; j++) {
                    if (need[i][j] > avail[j]) { // If need > available, process can't proceed
                        canProceed = false;
                        break;
                    }
                }

                // If process i can proceed safely
                if (canProceed) {
                    safeSeq[index++] = i; // Add process to safe sequence
                    for (int j = 0; j < r; j++) {
                        avail[j] += alloc[i][j]; // Release resources after process finishes
                    }
                    completed[i] = 1; // Mark process as completed
                }
            }
        }
    }

    // Check if the system is in a safe state by verifying if all processes are completed
    bool isSafe = true;
    for (int i = 0; i < p; i++) {
        if (completed[i] == 0) { // If any process is incomplete, system is unsafe
            isSafe = false;
            cout << "The system is not safe.\n";
            break;
        }
    }

    // Print the safe sequence if system is safe
    if (isSafe) {
        cout << "Following is the SAFE Sequence:\n";
        for (int i = 0; i < p - 1; i++) {
            cout << " P" << safeSeq[i] << " ->";
        }
        cout << " P" << safeSeq[p - 1] << endl;
    }

    return 0;
}