#include <stdio.h>
#include <stdlib.h>

#define NEIGHBORS_MAX_SIZE 100

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

struct UndirectedGraphNode {
    int label;
    struct UndirectedGraphNode *neighbors[NEIGHBORS_MAX_SIZE];
    int neighbors_count;
};

struct label_node {
    struct UndirectedGraphNode *gn;
    struct hlist_node node;
};

struct UndirectedGraphNode *find(int label, int size, struct hlist_head *heads)
{
    int hash = (label < 0 ? -label : label) % size;
    struct hlist_node *p;
    hlist_for_each(p, &heads[hash]) {
        struct label_node *ln = list_entry(p, struct label_node, node);
        if (ln->gn->label == label) {
            return ln->gn;
        }
    }
    return NULL;
}

struct UndirectedGraphNode *dfs(struct UndirectedGraphNode *graph, struct hlist_head *heads, int size)
{
    if (graph == NULL) {
        return NULL;
    }

    struct UndirectedGraphNode *node = find(graph->label, size, heads);
    if (node != NULL) {
        return node;
    }

    node = malloc(sizeof(*node));
    node->label = graph->label;
    node->neighbors_count = graph->neighbors_count;
    struct label_node *ln = malloc(sizeof(*ln));
    ln->gn = node;
    int hash = (node->label < 0 ? -node->label : node->label) % size;
    hlist_add_head(&ln->node, &heads[hash]);

    int i;
    for (i = 0; i < node->neighbors_count; i++) {
        node->neighbors[i] = dfs(graph->neighbors[i], heads, size);
    }

    return node;
}

struct UndirectedGraphNode *clone_graph(struct UndirectedGraphNode *graph)
{
    int i, capacity = 1000;
    struct hlist_head *heads = malloc(capacity * sizeof(*heads));
    for (i = 0; i < capacity; i++) {
        INIT_HLIST_HEAD(&heads[i]);
    }

    return dfs(graph, heads, capacity);
}

int main(int argc, char **argv)
{
    struct UndirectedGraphNode n0, n1, n2;
    n0.label = 0;
    n1.label = 1;
    n2.label = 2;
    n0.neighbors_count = 2;
    n1.neighbors_count = 1;
    n2.neighbors_count = 1;
    n0.neighbors[0] = &n1;
    n0.neighbors[1] = &n2;
    n1.neighbors[0] = &n2;
    n2.neighbors[0] = &n2;

    struct UndirectedGraphNode *res = clone_graph(&n0);
    printf("%p\n", res);

    return EXIT_SUCCESS;
}
