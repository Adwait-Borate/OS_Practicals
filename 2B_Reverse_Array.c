#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include <sys/wait.h>    // Include this on Linux for wait()
#include <string.h>

void sortArray(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void printArray(const char *message, int arr[], int n) {
    printf("%s: ", message);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <array elements>\n", argv[0]);
        return 1;
    }

    int n = argc - 1;
    int arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    printArray("Original array", arr, n);

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process: Reversing the array\n");
        char *args[n + 2];
        args[0] = "./reverse";
        for (int i = 0; i < n; i++) {
            args[i + 1] = argv[i + 1];
        }
        args[n + 1] = NULL;
        execve(args[0], args, NULL);
        perror("execve failed");
        return 1;
    } else {
        // Parent process
        wait(NULL);
        printf("Parent process: Sorting the array\n");
        sortArray(arr, n);
        printArray("Sorted array", arr, n);

        printf("Parent process: Reversing the sorted array\n");
        char *args[n + 2];
        args[0] = "./reverse";
        for (int i = 0; i < n; i++) {
            char buffer[10];
            snprintf(buffer, sizeof(buffer), "%d", arr[i]);
            args[i + 1] = strdup(buffer);
        }
        args[n + 1] = NULL;
        execve(args[0], args, NULL);
        perror("execve failed");
        return 1;
    }
    return 0;
}