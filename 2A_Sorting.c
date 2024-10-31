// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// // #include <sys/wait.h>   // Include this on Linux for wait()

// // Quick Sort
// void quickSort(int arr[], int low, int high) {
//     if (low < high) {
//         int pi = partition(arr, low, high);
//         quickSort(arr, low, pi - 1);
//         quickSort(arr, pi + 1, high);
//     }
// }

// int partition(int arr[], int low, int high) {
//     int pivot = arr[high];
//     int i = (low - 1);
//     for (int j = low; j <= high - 1; j++) {
//         if (arr[j] < pivot) {
//             i++;
//             int temp = arr[i];
//             arr[i] = arr[j];
//             arr[j] = temp;
//         }
//     }
//     int temp = arr[i + 1];
//     arr[i + 1] = arr[high];
//     arr[high] = temp;
//     return (i + 1);
// }

// // Print function
// void printArray(int arr[], int n) {
//     for (int i = 0; i < n; i++) {
//         printf("%d ", arr[i]);
//     }
//     printf("\n");
// }

int main() {
    printf("PARENT: MY PID IS %d\n", getpid());
    int n;
    printf("Enter the size of the array: ");
    scanf("%d", &n);
    
    int arr[n];
    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int ch;
    printf("******************************************************\n");
    printf("***********************MENU*************************\n");
    printf("1. Fork system call (Quick Sort)\n");
    printf("2. Create Orphan State.\n");
    printf("3. Create Zombie State.\n");
    printf("******************************************************\n");
    printf("Enter your choice: ");
    scanf("%d", &ch);
    printf("FORKING...\n");

    pid_t p = fork();
    switch (ch) {
        case 1: {
            if (p < 0) {
                printf("FORK FAILED!\n");
            } else if (p == 0) {
                // Child process
                printf("CHILD: MY PID IS %d\n", getpid());
                printf("CHILD: MY PARENT'S PID IS %d\n", getppid());
                quickSort(arr, 0, n - 1);
                printf("Sorted array by Quick Sort (Child): ");
                printArray(arr, n);
                printf("CHILD: I am dying now.\n");
                printf("_________________________________________________________________\n");
            } else {
                // Parent process
                wait(NULL);
                printf("PARENT: I am back.\n");
                printf("PARENT: MY PID IS %d\n", getpid());
                printf("PARENT: MY CHILD'S PID IS %d\n", p);
                quickSort(arr, 0, n - 1);
                printf("Sorted array by Quick Sort (Parent): ");
                printArray(arr, n);
                printf("PARENT: I am dying now.\n");
                printf("_________________________________________________________________\n");
            }
            break;
        }
        case 2: {
            if (p < 0) {
                printf("FORK FAILED!\n");
            } else if (p == 0) {
                // Child process
                printf("CHILD: MY PID IS %d\n", getpid());
                printf("CHILD: MY PARENT'S PID IS %d\n", getppid());
                printf("CHILD: I am sleeping now.\n");
                sleep(10);
                printf("_________________________________________________________________\n");
                system("ps -elf | grep a.out");
            } else {
                // Parent process
                printf("PARENT: I am back.\n");
                printf("PARENT: MY PID IS %d\n", getpid());
                printf("PARENT: MY CHILD'S PID IS %d\n", p);
                printf("PARENT: I am dying now.\n");
                printf("_________________________________________________________________\n");
                system("ps -elf | grep a.out");
                exit(0);
            }
            break;
        }
        case 3: {
            if (p < 0) {
                printf("FORK FAILED!\n");
            } else if (p == 0) {
                sleep(2);
                // Child process
                printf("CHILD: MY PID IS %d\n", getpid());
                printf("CHILD: MY PARENT'S PID IS %d\n", getppid());
                printf("CHILD: I am dying now.\n");
                printf("_________________________________________________________________\n");
                system("ps -elf | grep a.out");
                exit(0);
            } else {
                // Parent process
                printf("PARENT: I am back.\n");
                printf("PARENT: MY PID IS %d\n", getpid());
                printf("PARENT: MY CHILD'S PID IS %d\n", p);
                printf("PARENT: I am sleeping now.\n");
                sleep(10);
                printf("_________________________________________________________________\n");
                system("ps -elf | grep a.out");
            }
            break;
        }
        default: {
            printf("Invalid choice!\n");
            break;
        }
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include <sys/wait.h>
#include <sys/types.h>

void bubblesort(int arr[],int n){
	for(int i=0;i<n-1;i++){
		for(int j=0;j<n-i-1;j++){
			if(arr[j]>arr[j+1]){
				int temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
	}
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergesort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergesort(arr, l, m);
        mergesort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int main(){
	printf("PARENT: MY PID IS %d\n",getpid());
	int n;
	printf("Enter the size of the array: ");
	scanf("%d",&n);
	int arr[n];
	printf("Enter the elements of the array:- ");
	for(int i=0;i<n;i++){
		scanf("%d",&arr[i]);
	}
	int ch;
	printf("******************************************************\n");
	printf("***********************MENU*************************\n");
	printf("!.Fork system call (Merge Sort/Bubble Sort)\n");
	printf("2.Create Orphan State.\n");
	printf("3.Create Zombie State.\n");
	printf("******************************************************\n");
	printf("Enter you choice:- ");
	scanf("%d",&ch);
	printf("FORKING..\n");
	int p;	
	p=fork();
	switch(ch){
		case 1:{
			if(p<0){
				printf("FORK FAILED!\n");
			}
			else if(p==0){
				printf("CHILD: MY PID IS %d\n",getpid());
				printf("CHILD: MY PARENTS PID IS %d\n",getppid());
				bubblesort(arr,n);
				printf("Sorted array by bubble sort:- ");
				for(int i=0;i<n;i++){
					printf("%d",arr[i]);
				}
				printf("\n");
				printf("CHILD: I am dying now.\n");
				printf("_________________________________________________________________\n");
			}
			else{
				wait(NULL);
				printf("PARENT: I am back.\n");
				printf("PARENT: MY PID IS %d\n",getpid());
				printf("PARENT: MY CHILDS PID IS %d\n",p);
				mergesort(arr,0,n-1);
				printf("Sorted array by merge sort:- ");
				for(int i=0;i<n;i++){
					printf("%d",arr[i]);
				}
				printf("\n");
				printf("PARENT: I am dying now.\n");
				printf("_________________________________________________________________\n");
			}
			break;
		}
		case 2:{
			if(p<0){
				printf("FORK FAILED!\n");
			}
			else if(p==0){
				printf("CHILD: MY PID IS %d\n",getpid());
				printf("CHILD: MY PARENTS PID IS %d\n",getppid());
				printf("CHILD: I am sleeping now.\n");                                      // @Adwait-Borate
				sleep(10);
				printf("_________________________________________________________________\n");
				system("ps -elf | grep a.out");
			}
			else{
				printf("PARENT: I am back.\n");
				printf("PARENT: MY PID IS %d\n",getpid());
				printf("PARENT: MY CHILDS PID IS %d\n",p);
				printf("PARENT: I am dying now.\n");
				printf("_________________________________________________________________\n");
				system("ps -elf | grep a.out");
				exit(0);
			}
			break;
		}
		case 3:{
			if(p<0){
				printf("FORK FAILED!\n");
			}
			else if(p==0){
				sleep(2);
				printf("CHILD: MY PID IS %d\n",getpid());
				printf("CHILD: MY PARENTS PID IS %d\n",getppid());
				printf("CHILD: I am dying now.\n");
				printf("_________________________________________________________________\n");
                // e for showing all process
                // l for long list format
                // f show process hiearchy in tree like strucuter
				system("ps -elf | grep a.out");
				exit(0);
			}
			else{
				printf("PARENT: I am back.\n");
				printf("PARENT: MY PID IS %d\n",getpid());
				printf("PARENT: MY CHILDS PID IS %d\n",p);
				printf("PARENT: I am sleeping now.\n");
				sleep(10);
				printf("_________________________________________________________________\n");
				system("ps -elf | grep a.out");
			}
			break;
		}
		case 4: {
			break;
		}
	}
	
	return 0;
}
