#include <stdio.h>
#include <stdlib.h>

struct Object {
    int *gas;
    int gas_size;
    int *cost;
    int cost_size;
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

int can_complete_circuit(int *gas, int gas_size, int *cost, int cost_size)
{
    int i, store = 0, start = -1;
    for (i = 0; i < gas_size; i++) {
        if (start < 0) {
            start = i;
        }
        store += gas[i] - cost[i];
        if (store < 0) {
            store = 0;
            start = -1;
        }
    }
    if (start > 0) {
        for (i = 0; i < start; i++) {
            store += gas[i] - cost[i];
            if (store < 0) {
                return -1;
            }
        }
    }

    return start;
}

int main(int argc, char **argv)
{
    int gas1[] = { 1, 2, 3, 4, 5 }, gas_size1 = sizeof(gas1) / sizeof(int);
    int cost1[] = { 3, 4, 5, 1, 2 }, cost_size1 = sizeof(cost1) / sizeof(int);
    int gas2[] = { 2, 3, 4 }, gas_size2 = sizeof(gas2) / sizeof(int);
    int cost2[] = { 3, 4, 3 }, cost_size2 = sizeof(cost2) / sizeof(int);
    struct Object inputs[] = {
        { .gas = gas1, .gas_size = gas_size1, .cost = cost1, .cost_size = cost_size1 },
        { .gas = gas2, .gas_size = gas_size2, .cost = cost2, .cost_size = cost_size2 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *gas = inputs[i].gas;
        int gas_size = inputs[i].gas_size;
        int *cost = inputs[i].cost;
        int cost_size = inputs[i].cost_size;

        printf("\n Input:");
        printf("\n   gas:  ");
        print_nums(gas, gas_size);
        printf("\n   cost: ");
        print_nums(cost, cost_size);

        int idx = can_complete_circuit(gas, gas_size, cost, cost_size);
        printf("\n Output: %d\n", idx);
    }

    return EXIT_SUCCESS;
}
