#include <stdio.h>
#include <stdlib.h>

int max_area(int *height, int height_size)
{
    int min = 0, max = height_size-1;
    int area_max = 0;

    while (min < max) {
        int area = (max - min) * (height[min] < height[max] ? height[min] : height[max]);
        area_max = area > area_max ? area : area_max;

        if (height[min] < height[max]) {
            while (++min < max && height[min] <= height[min-1]) {
                continue;
            }
        } else {
            while (min < --max && height[max] <= height[max+1]) {
                continue;
            }
        }
    }

    return area_max;
}

int main(int argc, char **argv)
{
    int height[] = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    int len = sizeof(height) / sizeof(int);

    printf("output: %d\n", max_area(height, len));

    return 0;
}
