#include <stdio.h>
#include <stdlib.h>

struct Object {
    int *nums;
    int len;
};

void print_nums(int *nums, int size)
{
    if (size < 1) {
        printf("[]");
        return;
    }
    int i = 0;
    printf("[%d", nums[i]);
    for (i = 1; i < size; i++) {
        printf(", %d", nums[i]);
    }
    printf("]");
}

int candy(int *ratings,  int ratings_size)
{
    if (ratings_size == 0) return 0;
    if (ratings_size == 1) return 1;

    int i, *candies = malloc(ratings_size * sizeof(int));
    candies[0] = 1;

    for (i = 1; i < ratings_size; i++) {
        if (ratings[i] > ratings[i - 1]) {
            candies[i] = candies[i - 1] + 1;
        } else {
            candies[i] = 1;
        }
    }

    int sum = candies[ratings_size - 1];
    for (i = ratings_size - 2; i >= 0; i--) {
        if (ratings[i] > ratings[i + 1] && candies[i] <= candies[i + 1]) {
            candies[i] = candies[i + 1] + 1;
        }
        sum += candies[i];
    }

    free(candies);

    return sum;
}

int main(int argc, char **argv)
{
    int nums1[] = { 1, 0, 2 }, len1 = sizeof(nums1) / sizeof(int);
    int nums2[] = { 1, 2, 2 }, len2 = sizeof(nums2) / sizeof(int);
    struct Object inputs[] = {
        { .nums = nums1, .len = len1 },
        { .nums = nums2, .len = len2 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;

        printf("\n Input: ");
        print_nums(nums, size);
        int count = candy(nums, size);

        printf("\n Output: %d\n", count);
    }
    return EXIT_SUCCESS;
}
