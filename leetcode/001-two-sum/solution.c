#include <stdio.h>
#include <stdlib.h>

struct object {
    int val;
    int index;
};

void print_array(int *array, int len)
{
    int i;

    putchar('[');
    for (i = 0; i < len; i++) {
        if (i == 0) {
            printf("%d", array[i]);
        } else {
            printf(", %d", array[i]);
        }
    }
    putchar(']');
}

static int compare(const void *lhs, const void *rhs)
{
    return ((struct object *) lhs)->val - ((struct object *) rhs)->val;
}

static int * two_sum(int *nums, int numsSize, int target)
{
    int i, j;
    struct object *objs = malloc(numsSize * sizeof(*objs));
    for (i = 0; i < numsSize; i++) {
        objs[i].val = nums[i];
        objs[i].index = i;
    }
    qsort(objs, numsSize, sizeof(*objs), compare);

    int *results = malloc(2 * sizeof(int));
    i = 0;
    j = numsSize -1;
    while (i < j) {
        int diff = target - objs[i].val;
        if (diff > objs[j].val) {
            while (++i < j && objs[i].val == objs[i - 1].val) {}
        } else if (diff < objs[j].val) {
            while (--j > i && objs[j].val == objs[j + 1].val) {}
        } else {
            results[0] = objs[i].index;
            results[1] = objs[j].index;
            return results;
        }
    }
    return NULL;
}

int main(int argc, char **argv)
{
    int nums[] = { 2, 7, 11, 15 };
    int len = sizeof(nums) /sizeof(*nums);
    int target = 9;


    printf(" Given nums: "); print_array(nums, len);
    printf(", target = %d\n", target);

    int *indexes = two_sum(nums, len, target);
    if (indexes != NULL) {
        printf(" [%d, %d]\n", indexes[0], indexes[1]);
    } else {
        printf(" Not found\n");
    }

    return EXIT_SUCCESS;
}
