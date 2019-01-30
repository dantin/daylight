#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Object {
    struct Interval *intervals;
    struct Interval *new_interval;
    int len;
};

struct Interval {
    int start;
    int end;
};

void print_interval(struct Interval interval)
{
    printf("[%d, %d]", interval.start, interval.end);
}

void print_intervals(struct Interval *intervals, int size)
{
    int i;
    if (size < 1) {
        printf("[]\n");
        return;
    }

    printf("["); print_interval(intervals[0]);
    for (i = 1; i < size; i++) {
        printf(", "); print_interval(intervals[i]);
    }
    printf("]\n");
}

int binary_search(int *nums, int size, int target)
{
    int low = -1, high = size;

    while (low + 1 < high) {
        int mid = low + (high - low) / 2;
        if (target > nums[mid]) {
            low = mid;
        } else {
            high = mid;
        }
    }

    if (high == size || nums[high] != target) {
        return -high - 1;
    }
    return high;
}

struct Interval *insert(struct Interval *intervals, int intervals_size, struct Interval new_interval, int *return_size) {
    struct Interval *p;
    if (intervals_size == 0) {
        p = malloc(sizeof(*p));
        p->start = new_interval.start;
        p->end = new_interval.end;
        *return_size = 1;
        return p;
    }

    int i, count;
    int *nums = malloc(2 * intervals_size * sizeof(int));
    for (i = 0; i < intervals_size; i++) {
        nums[i * 2] = intervals[i].start;
        nums[i * 2 + 1] = intervals[i].end;
    }

    int start0 = binary_search(nums, 2 * intervals_size, new_interval.start);
    int end0 = binary_search(nums, 2 * intervals_size, new_interval.end);

    int start1 = -1, end1 = -1;
    int merge_start = -1, merge_end = -1;
    if (start0 >= 0) {
        merge_start = start0 / 2;
    } else {
        start1 = -start0 - 1;
        merge_start = start1 / 2;
    }
    if (end0 >= 0) {
        merge_end = end0 / 2;
    } else {
        end1 = -end0 - 1;
        if (end1 % 2 == 0) {
            merge_end = end1 / 2 > 0 ? end1 / 2 - 1 : 0;
        } else {
            merge_end = end1 / 2;
        }
    }

    if (merge_start == merge_end) {
        if (start0 < 0 && end0 < 0 && start1 == end1 && start1 % 2 == 0) {
            count = intervals_size + 1;
            p = malloc(count * sizeof(*p));
            memcpy(p, intervals, merge_start * sizeof(*p));
            p[merge_start] = new_interval;
            memcpy(p + merge_start + 1, intervals + merge_start, (intervals_size - merge_start) * sizeof(*p));
        } else {
            count = intervals_size;
            p = malloc(count * sizeof(*p));
            memcpy(p, intervals, count*sizeof(*p));
            if (start0 < 0 && start1 % 2 == 0) {
                p[merge_start].start = new_interval.start;
            }
            if (end0 < 0 && end1 % 2 == 0) {
                p[merge_end].end = new_interval.end;
            }
        } 
    } else {
        count = intervals_size - (merge_end - merge_start);
        p = malloc(count * sizeof(*p));
        memcpy(p, intervals, merge_start * sizeof(*p));
        memcpy(p + merge_start, intervals + merge_end, (intervals_size - merge_end) * sizeof(*p));
        if (start0 < 0 && start1 % 2 == 0) {
            p[merge_start].start = new_interval.start;
        } else {
            p[merge_start].start = intervals[merge_start].start;
        }
        if (end0 < 0 && end1 % 2 == 0) {
            p[merge_start].end = new_interval.end;
        } else {
            p[merge_start].end = intervals[merge_end].end;
        }
    }

    free(nums);
    *return_size = count;
    return p;
}

int main(int argc, char **argv)
{
    struct Interval intervals1[] = {
        { .start = 1, .end = 3 },
        { .start = 6, .end = 9 },
    }, new_interval1 = { .start = 2, .end = 5 };
    struct Interval intervals2[] = {
        { .start = 1,  .end = 2 },
        { .start = 3,  .end = 5 },
        { .start = 6,  .end = 7 },
        { .start = 8,  .end = 10 },
        { .start = 12, .end = 16 },
    }, new_interval2 = { .start = 4, .end = 8 };
    int len1 = sizeof(intervals1) / sizeof(struct Interval);
    int len2 = sizeof(intervals2) / sizeof(struct Interval);

    struct Object inputs[] = {
        { .intervals = intervals1, .len = len1, .new_interval = &new_interval1 },
        { .intervals = intervals2, .len = len2, .new_interval = &new_interval2 },
    };
    int i, return_size, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        struct Interval *intervals = inputs[i].intervals;
        int size = inputs[i].len;
        struct Interval *new_elem = inputs[i].new_interval;
        printf("\n Input: "); print_intervals(intervals, size);
        printf(" newInterval = "); print_interval(*new_elem);

        struct Interval *inserted = insert(intervals, size, *new_elem, &return_size);
        printf("\n Output: "); print_intervals(inserted, return_size);
    }

    return EXIT_SUCCESS;
}
