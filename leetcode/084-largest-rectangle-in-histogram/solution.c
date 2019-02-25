#include <stdio.h>
#include <stdlib.h>

struct Object {
    int *nums;
    int len;
};

void print_nums(int *nums, int size)
{
    if (size < 1) {
        printf("[]\n");
        return;
    }

    int i;
    printf("[%d", nums[0]);
    for (i = 1; i < size; i++) {
        printf(", %d", nums[i]);
    }
    printf("]\n");
}

int largetst_rectangle_area(int *heights, int heights_size)
{
    int *indexes = malloc(heights_size * sizeof(int));
    int *left = malloc(heights_size * sizeof(int));
    int *right = malloc(heights_size * sizeof(int));

    int i, pos = 0;
    for (i = 0; i < heights_size; i++) {
        while (pos > 0 && heights[indexes[pos - 1]] >= heights[i]) {
            pos--;
        }
        left[i] = pos == 0 ? -1 : indexes[pos - 1];
        indexes[pos++] = i;
    }

    pos = 0;
    for (i = heights_size - 1; i >= 0; i--) {
        while (pos > 0 && heights[indexes[pos - 1]] >= heights[i]) {
            pos--;
        }
        right[i] = pos == 0 ? heights_size : indexes[pos - 1];
        indexes[pos++] = i;
    }

    int max_area = 0;
    for (i = 0; i < heights_size; i++) {
        int area = heights[i] * (right[i] - left[i] - 1);
        max_area = area > max_area ? area : max_area;
    }

    free(indexes);
    free(left);
    free(right);

    return max_area;
}

int main(int argc, char **args)
{
    int nums1[] = { 2, 1, 5, 6, 2, 3 }, len1 = sizeof(nums1) / sizeof(int);
    struct Object inputs[] = {
        { .nums = nums1, .len = len1 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;
        printf("\n Input: ");
        print_nums(nums, size);
        int area = largetst_rectangle_area(nums, size);
        printf(" Output: %d\n", area);
    }

    return EXIT_SUCCESS;
}
