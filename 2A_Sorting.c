#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include <sys/wait.h>   // Include this on Linux for wait()

// Quick Sort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

// Print function
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter number of integers: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the integers: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process started, sorting using Quick Sort...\n");
        quickSort(arr, 0, n - 1);
        printf("Child process sorted array: ");
        printArray(arr, n);
        printf("Child process exiting...\n");
        exit(0);
    } else {
        // Parent process
        printf("Parent process started, sorting using Quick Sort...\n");
        quickSort(arr, 0, n - 1);
        printf("Parent process sorted array: ");
        printArray(arr, n);

        // Wait for child process to complete
        int status;
        wait(&status);  // Catching the return value of wait() in status
        printf("Parent process detected child process completion.\n");

        // Demonstrate zombie state
        printf("Demonstrating zombie state. Check process list.\n");
        sleep(5);

        // Demonstrate orphan state
        if (fork() == 0) {
            printf("Orphan process started, parent will exit.\n");
            sleep(10);
            printf("Orphan process exiting.\n");
            exit(0);
        } else {
            printf("Parent process exiting, orphan process will be adopted by init.\n");
            exit(0);
        }
    }

    return 0;
}
