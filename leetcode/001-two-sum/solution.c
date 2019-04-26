#include <stdio.h>
#include <stdlib.h>

struct Object {
    int *nums;
    int len;
    int target;
};

struct object {
    int val;
    int index;
};

void print_nums(int *nums, int size)
{
    int i;
    char *s = "";

    printf("[");
    for (i = 0; i < size; i++) {
        printf("%s%d", s, nums[i]);
        s = ", ";
    }
    printf("]");
}

int compare(const void *lhs, const void *rhs)
{
    return ((struct object *) lhs)->val - ((struct object *) rhs)->val;
}

int *two_sum(int *nums, int nums_size, int target)
{
    int i, j;
    struct object *objs = malloc(nums_size * sizeof(*objs));
    for (i = 0; i < nums_size; i++) {
        objs[i].val = nums[i];
        objs[i].index = i;
    }
    qsort(objs, nums_size, sizeof(*objs), compare);

    int *results = malloc(2 * sizeof(int));
    i = 0;
    j = nums_size - 1;
    while (i < j) {
        int diff = target - objs[i].val;
        if (diff > objs[j].val) {
            while (++i < j && objs[i].val == objs[i - 1].val) {}
        } else if (diff < objs[j].val) {
            while (--j > i && objs[j].val == objs[j + 1].val) {}
        } else {
            results[0] = objs[i].index;
            results[1] = objs[j].index;
            free(objs);
            return results;
        }
    }
    free(objs);

    return NULL;
}

int main(int argc, char **argv)
{
    int nums1[] = { 2, 7, 11, 15 }, len1 = sizeof(nums1) /sizeof(int);
    int target1 = 9;
    struct Object inputs[] = {
        { .nums = nums1, .len = len1, .target = target1 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;
        int target = inputs[i].target;

        printf(" Given nums: ");
        print_nums(nums, size);
        printf(", target = %d\n", target);

        int *indexes = two_sum(nums, size, target);
        if (indexes != NULL) {
            printf(" [%d, %d]\n", indexes[0], indexes[1]);
        } else {
            printf(" Not found\n");
        }
        free(indexes);
    }

    return EXIT_SUCCESS;
}
