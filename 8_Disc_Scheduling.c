#include <stdio.h>
#include <math.h>
// this library is for qsort function
#include <stdlib.h>
// this library is for memset function
#include <string.h>

#define disk_size 200

void calculateDiff(int *tracks, int *dist, int n, int head)
{
    for (int i = 0; i < n; i++)
    {
        dist[i] = fabs(head - tracks[i]);
    }
}

// Return the index of track which is at minimum distance with head
int findMinTrackPosition(int *tracks, int *dist, int *isAccessed, int n, int head)
{
    int min = __INT_MAX__;
    int index = -1;
    for (int i = 0; i < n; i++)
    {
        // if the track is not previously accessed
        // and dist[i] is less than minimum
        // then update the
        if (isAccessed[i] == 0 && min > dist[i])
        {
            min = dist[i];
            index = i;
        }
    }
    return index;
}
void SSTF(int *tracks, int head, int n)
{

    // dist will keep track of distance between curr_head and each track
    // 2nd value of this 2d array is boolean isAccessed
    int dist[n];
    int isAccessed[n];

    // first in sequence will be the head and then rest of the tracks hence n+1
    int seek_sequence[n + 1];
    memset(dist, 0, n * sizeof(int));
    memset(isAccessed, 0, n * sizeof(int));
    memset(seek_sequence, 0, (n + 1) * sizeof(int));

    int seek_count = 0;

    for (int i = 0; i < n; i++)
    {
        seek_sequence[i] = head;
        calculateDiff(tracks, dist, n, head);
        // get the index of track with minimum distance
        int index = findMinTrackPosition(tracks, dist, isAccessed, n, head);
        // make isAccessed value to 1 to indicate that track is accessed
        isAccessed[index] = 1;

        seek_count += dist[index];

        // accessed track is not new head
        head = tracks[index];
    }
    // update the last head in seek sequences
    seek_sequence[n] = head;

    printf("Total seek operations: %d\n", seek_count);

    printf("Seek sequence is : \n");

    for (int i = 0; i < n; i++)
    {
        printf("%d->", seek_sequence[i]);
    }
    printf("\n");
}

// void is added to comparator function to make it more generic and work with different data types
int comp(const void *l, const void *n)
{
    // if difference negative then l is small
    // if difference is positive then l is large
    // if 0 then both l and n are equal
    // This function sorts them is ascending order
    return (*(int *)l - *(int *)n);
}
void SCAN(int *tracks, int head, int n, int direction)
{
    // direction 1 means rightside
    // direction 0 means leftside
    int left = 0, right = 0;
    int leftside[n], rightside[n];
    if (direction == 0)
        leftside[left++] = 0;
    else if (direction == 1)
        rightside[right++] = disk_size - 1;

    for (int i = 0; i < n; i++)
    {
        if (tracks[i] < head)
            leftside[left++] = tracks[i];
        if (tracks[i] > head)
            rightside[right++] = tracks[i];
    }

    qsort(leftside, left, sizeof(int), comp);
    qsort(rightside, right, sizeof(int), comp);

    int seek_sequence[n + 3];
    int curr_track, dist, seek_count = 0;

    int go = 2, index = 0;
    while (go--)
    {
        if (direction == 0)
        {
            for (int i = left - 1; i >= 0; i--)
            {
                // get the current track
                curr_track = leftside[i];
                // insert the curr_track into seeksequence
                seek_sequence[index++] = curr_track;

                dist = fabs(curr_track - head);

                seek_count += dist;
                head = curr_track;
            }
            direction = 1;
        }
        else if (direction == 1)
        {
            for (int i = 0; i < right; i++)
            {
                // get the current track
                curr_track = rightside[i];
                // insert the curr_track into seeksequence
                seek_sequence[index++] = curr_track;

                dist = fabs(curr_track - head);

                seek_count += dist;
                head = curr_track;
            }
            direction = 0;
        }
    }

    printf("Num of seek process = %d\n", seek_count);
    printf("Sequence is: ");
    for (int p_s = 0; p_s < index; p_s++)
    {
        printf("%d\t", seek_sequence[p_s]);
    }
}

void CLOOK(int *tracks, int head, int n)
{

    int leftside[n], rightside[n];
    int left = 0, right = 0;
    for (int i = 0; i < n; i++)
    {
        if (tracks[i] < head)
            leftside[left++] = tracks[i];
        if (tracks[i] > head)
            rightside[right++] = tracks[i];
    }

    qsort(leftside, left, sizeof(int), comp);
    qsort(rightside, right, sizeof(int), comp);

    int seek_sequence[n + 1];
    int curr_track, dist, seek_count = 0;
    int index = 0;

    // first service the request on right side of head
    for (int i = 0; i < right; i++)
    {
        curr_track = rightside[i];

        seek_sequence[index++] = curr_track;

        // calculate distance
        dist = fabs(head - curr_track);

        // calculate seekcount
        seek_count += dist;

        // update the head
        head = curr_track;
    }
    // once reached to the right end then go to
    // start of left side
    // therefore calculate the seekcount for going to right end to leftstart
    dist = fabs(head - leftside[0]);
    seek_count += dist;
    head = leftside[0];
    // now go to the start of left side
    // and start services request from that point
    for (int i = 0; i < left; i++)
    {
        curr_track = leftside[i];
        seek_sequence[index++] = curr_track;

        dist = fabs(head - curr_track);

        seek_count += dist;

        head = curr_track;
    }

    printf("Total number of seek operations performed: %d\n", seek_count);

    printf("Seek sequence is: \n");

    for (int i = 0; i < index; i++)
    {
        printf("%d\t", seek_sequence[i]);
    }
    printf("\n");
}

int main()
{
    int n;
    printf("Enter number of tracks: ");
    scanf("%d", &n);
    int tracks[n];
    printf("Enter the tracks:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &tracks[i]);

    int head;
    printf("Enter initial head position: ");
    scanf("%d", &head);

    int choice, direction;
    printf("Choose the algorithm:\n1. SSTF\n2. SCAN\n3. CLOOK\n");
    scanf("%d", &choice);

    if (choice == 2)
    {
        printf("Enter direction (0 for left, 1 for right): ");
        scanf("%d", &direction);
    }

    switch (choice)
    {
    case 1:
        SSTF(tracks, head, n);
        break;
    case 2:
        SCAN(tracks, head, n, direction);
        break;
    case 3:
        CLOOK(tracks, head, n);
        break;
    default:
        printf("Invalid choice.\n");
    }

    return 0;
}
