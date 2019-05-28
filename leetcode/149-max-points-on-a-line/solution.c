#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Object {
    int *nums;
    int len;
    int col_size;
};

int **make_points(int *nums, int size, int dimension_size, int **points_col_size, int *length)
{
    int i, j;

    *length = size / dimension_size;
    int **points = malloc((*length) * sizeof(int *));
    *points_col_size = malloc((*length) * sizeof(int));

    for (i = 0; i < *length; i++) {
        int *point = malloc(dimension_size * sizeof(int));
        for (j = 0; j < dimension_size; j++) {
            point[j] = nums[i * dimension_size + j];
        }
        points[i] = point;
        (*points_col_size)[i] = dimension_size;
    }

    return points;
}

void print_nums(int *nums, int size)
{
    char *s = "";
    int i;
    printf("[");
    for (i = 0; i < size; i++) {
        printf("%s%d", s, nums[i]);
        s = ", ";
    }
    printf("]");
}

void print_points(int **points, int points_size, int *points_col_size)
{
    char *s = "";
    int i;
    printf("[");
    for (i = 0; i < points_size; i++) {
        printf("%s", s);
        print_nums(points[i], points_col_size[i]);
        s = ", ";
    }
    printf("]");
}

void free_points(int **points, int size)
{
    int i;
    for (i = 0; i < size; i++) {
        free(points[i]);
    }
    free(points);
}

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - (size_t)&(((type *)0)->member)))

#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define hlist_for_each(pos, head) \
    for (pos = (head)->first; pos; pos = pos->next)

#define hlist_for_each_safe(pos, n, head) \
    for (pos = (head)->first; pos && ({ n = pos->next; true; }); pos = n)

struct hlist_node;

struct hlist_head {
    struct hlist_node *first;
};

struct hlist_node {
    struct hlist_node *next, **pprev;
};

void INIT_HLIST_HEAD(struct hlist_head *h)
{
    h->first = NULL;
}

int hlist_empty(struct hlist_head *h)
{
    return !h->first;
}

void hlist_add_head(struct hlist_node *n, struct hlist_head *h)
{
    if (h->first != NULL) {
        h->first->pprev = &n->next;
    }
    n->next = h->first;
    n->pprev = &h->first;
    h->first = n;
}

void hlist_del(struct hlist_node *n)
{
    struct hlist_node *next = n->next;
    struct hlist_node **pprev = n->pprev;
    *pprev = next;
    if (next != NULL) {
        next->pprev = pprev;
    }
}

struct point_node {
    int p1;
    int p2;
    struct hlist_node node;
};

bool can_insert(struct hlist_head *head, int p1, int p2)
{
    struct hlist_node *pos;
    hlist_for_each(pos, head) {
        struct point_node *pn = list_entry(pos, struct point_node, node);
        return p1 == pn->p1;
    }
    return true;
}

int gcd(int x, int y)
{
    while (y != 0) {
        int tmp = y;
        y = x % y;
        x = tmp;
    }
    return x;
}

int max_points(int **points, int points_size, int *points_col_size)
{
    if (points_size <= 2) {
        return points_size;
    }

    int i, j, slope_size = points_size * points_size / 2 + 133;
    int *horizontal_cnts = malloc(points_size * sizeof(int));
    memset(horizontal_cnts, 0, points_size * sizeof(int));
    int *vertical_cnts = malloc(points_size * sizeof(int));
    memset(vertical_cnts, 0, points_size * sizeof(int));
    int *slope_cnts = malloc(slope_size * sizeof(int));
    memset(slope_cnts, 0, slope_size* sizeof(int));
    int *dup_cnts = malloc(points_size * sizeof(int));
    for (i = 0; i < points_size; i++) {
        dup_cnts[i] = 1;
    }

    struct hlist_head *heads = malloc(slope_size * sizeof(*heads));
    for (i = 0; i < slope_size; i++) {
        INIT_HLIST_HEAD(&heads[i]);
    }

    for (i = 0; i < points_size; i++) {
        for (j = i + 1; j < points_size; j++) {
            if (points[i][0] == points[j][0]) {
                horizontal_cnts[i]++;
                horizontal_cnts[j]++;
            }

            if (points[i][1] == points[j][1]) {
                vertical_cnts[i]++;
                vertical_cnts[j]++;
            }

            if (points[i][0] == points[j][0] && points[i][1] == points[j][1]) {
                dup_cnts[i]++;
                dup_cnts[j]++;
            }

            if (points[i][0] != points[j][0] && points[i][1] != points[j][1]) {
                int dx = points[j][0] - points[i][0];
                int dy = points[j][1] - points[i][1];
                int tmp = gcd(dx, dy);
                dx /= tmp;
                dy /= tmp;
                int hash = dx * dy - 1333 * (dx + dy);
                if (hash < 0) {
                    hash = -hash;
                }
                hash %= slope_size;
                if (can_insert(&heads[hash], i, j)) {
                    struct point_node *pn = malloc(sizeof(*pn));
                    pn->p1 = i;
                    pn->p2 = j;
                    hlist_add_head(&pn->node, &heads[hash]);
                }
            }
        }
    }

    for (i = 0; i < slope_size; i++) {
        struct hlist_node *pos;
        int idx = -1;
        hlist_for_each(pos, &heads[i]) {
            struct point_node *pn = list_entry(pos, struct point_node, node);
            idx = pn->p1;
            slope_cnts[i]++;
        }
        if (idx >= 0) {
            slope_cnts[i] += dup_cnts[idx];
        }
    }

    int max_num = 0;
    for (i = 0; i < points_size; i++) {
        if (horizontal_cnts[i] + 1 > max_num) {
            max_num = horizontal_cnts[i] + 1;
        }
        if (vertical_cnts[i] + 1 > max_num) {
            max_num = vertical_cnts[i] + 1;
        }
    }
    for (i = 0; i < slope_size; i++) {
        if (slope_cnts[i] > max_num) {
            max_num = slope_cnts[i];
        }
    }
    free(horizontal_cnts);
    free(vertical_cnts);
    free(dup_cnts);
    free(slope_cnts);
    free(heads);

    return max_num;
}

int main(int argc, char **argv)
{
    int nums1[] = { 1, 1, 2, 2, 3, 3 }, len1 = sizeof(nums1) / sizeof(int), col_size1 = 2;
    int nums2[] = { 0, 0, 1, 65536, 65536, 0 }, len2 = sizeof(nums2) / sizeof(int), col_size2 = 2;
    struct Object inputs[] = {
        { .nums = nums1, .len = len1, .col_size = col_size1 },
        { .nums = nums2, .len = len2, .col_size = col_size2 },
    };
    int i, size, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int length = inputs[i].len;
        int col_size = inputs[i].col_size;
        int *points_col_size = NULL;

        int **points = make_points(nums, length, col_size, &points_col_size, &size);

        printf("\n Input: ");
        print_points(points, size, points_col_size);
        printf("\n");

        int max = max_points(points, size, points_col_size);
        printf(" Output: %d\n", max);

        free_points(points, size);
        free(points_col_size);
    }

    return EXIT_SUCCESS;
}
