#include <stdio.h>
#include <stdlib.h>

//replace the page which is loaded first
//if all pages are used in future, replace the page which is used first
void fifo(int pages[], int n, int capacity) {
    int frame[capacity], index = 0, faults = 0;
    for (int i = 0; i < capacity; i++) frame[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            frame[index] = pages[i];
            index = (index + 1) % capacity;
            faults++;
        }
        printf("Frame: ");
        for (int j = 0; j < capacity; j++) printf("%d ", frame[j]);
        printf("\n");
    }
    printf("Total Page Faults (FIFO): %d\n", faults);
}


//replace the page which is not used in longest dimension of time in past
//Go to the past and check which page is not used for longest time
void lru(int pages[], int n, int capacity) {
    int frame[capacity], time[capacity], faults = 0, counter = 0;
    for (int i = 0; i < capacity; i++) frame[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0, least = 0;
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                time[j] = ++counter;
                break;
            }
        }
        if (!found) {
            for (int j = 1; j < capacity; j++) {
                if (time[j] < time[least]) least = j;
            }
            frame[least] = pages[i];
            time[least] = ++counter;
            faults++;
        }
        printf("Frame: ");
        for (int j = 0; j < capacity; j++) printf("%d ", frame[j]);
        printf("\n");
    }
    printf("Total Page Faults (LRU): %d\n", faults);
}


//replace the page which is not used in longest dimension of time in future
//if all pages are used in future, replace the page which is used in longest dimension of time in future
void optimal(int pages[], int n, int capacity) {
    int frame[capacity], faults = 0;
    for (int i = 0; i < capacity; i++) frame[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            int replace = -1, farthest = i + 1;
            for (int j = 0; j < capacity; j++) {
                int k;
                for (k = i + 1; k < n; k++) {
                    if (frame[j] == pages[k]) break;
                }
                if (k == n) {
                    replace = j;
                    break;
                } else if (k > farthest) {
                    farthest = k;
                    replace = j;
                }
            }
            if (replace == -1) replace = 0;
            frame[replace] = pages[i];
            faults++;
        }
        printf("Frame: ");
        for (int j = 0; j < capacity; j++) printf("%d ", frame[j]);
        printf("\n");
    }
    printf("Total Page Faults (Optimal): %d\n", faults);
}

int main() {
    int choice, n, capacity;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter the pages: ");
    for (int i = 0; i < n; i++) scanf("%d", &pages[i]);
    printf("Enter the frame capacity: ");
    scanf("%d", &capacity);

    do {
        printf("Choose Page Replacement Algorithm:\n1. FIFO\n2. LRU\n3. Optimal\n4. Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fifo(pages, n, capacity);
                break;
            case 2:
                lru(pages, n, capacity);
                break;
            case 3:
                optimal(pages, n, capacity);
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
