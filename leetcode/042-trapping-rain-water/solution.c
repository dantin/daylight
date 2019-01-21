#include <stdio.h>
#include <stdlib.h>

void print_nums(int *nums, int size)
{
    int i;
    if (size < 1) {
        printf("[]\n");
    }

    printf("[%d", nums[0]);
    for (i = 1; i < size; i++) {
        printf(", %d", nums[i]);
    }
    printf("]\n");
}

int trap(int *height, int height_size)
{
    if (height_size < 2) {
        return 0;
    }

    int i, j, left= -1, right = -1, total = 0;
    for (i = 0; i < height_size; i++) {
        if (height[i] > 0) {
            left = i;
            break;
        }
    }

    while (i < height_size) {
        right = -1;
        for (j = i + 1; j < height_size; j++) {
            if (height[j] >= height[j-1]) {
                if (right < 0 || height[j] >= height[right]) {
                    right = j;
                }
                if (height[j] >= height[left]) {
                    break;
                }
            }
        }

        if (right >= 0) {
            int level = height[left] < height[right] ? height[left] : height[right];
            while (i < right) {
                if (level > height[i]) {
                    total += level - height[i];
                }
                i++;
            }
            left = right;
            i = right;
        } else {
            i = j;
        }
    }

    return total;
}

int main(int argc, char **argv)
{
    int inputs[] = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    int len = sizeof(inputs) / sizeof(int);

    printf("\n Input: "); print_nums(inputs, len);
    int traps = trap(inputs, len);
    printf(" Output: %d\n", traps);

    return EXIT_SUCCESS;
}
