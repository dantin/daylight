#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

struct Point {
    int x, y;
};

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

int max_points(struct Point *points, int points_size)
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
            if (points[i].x == points[j].x) {
                horizontal_cnts[i]++;
                horizontal_cnts[j]++;
            }

        }
    }
}

int main(int argc, char **argv)
{
    return EXIT_SUCCESS;
}
