#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Object {
    char *s;
    int rows;
    int cols;
};

char **make_board(char *s, int rows, int cols)
{
    int len = strlen(s);
    if (rows * cols != len) {
        return NULL;
    }
    char **board = malloc(rows * sizeof(char *));
    int i, j;
    for (i = 0; i < rows; i++) {
        board[i] = malloc(cols * sizeof(cols));
    }

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            board[i][j] = s[i * cols + j];
        }
    }

    return board;
}

void print_board(char **board, int rows, int cols)
{
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

void free_board(char **board, int rows)
{
    int i;
    for (i = 0; i < rows; i++) {
        free(board[i]);
    }
    free(board);
}

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - (size_t)&(((type *)0)->member)))

#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define list_first_entry(ptr, type, field) list_entry((ptr)->next, type, field)
#define list_last_entry(ptr, type, field) list_entry((ptr)->prev, type, field)

#define list_for_each(p, head) \
    for (p = (head)->next; p != (head); p = p->next)

#define list_for_each_safe(p, n, head) \
    for (p = (head)->next, n = p->next; p != (head); p = n, n = p->next)

struct list_head {
    struct list_head *next, *prev;
};

void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list->prev = list;
}

int list_empty(const struct list_head *head)
{
    return (head->next == head);
}

void __list_add(struct list_head *new, struct list_head *prev, struct list_head *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

void list_add(struct list_head *_new, struct list_head *head)
{
    __list_add(_new, head, head->next);
}

void list_add_tail(struct list_head *_new, struct list_head *head)
{
    __list_add(_new, head, head->next);
}

void __list_del(struct list_head *entry)
{
    entry->next->prev = entry->prev;
    entry->prev->next = entry->next;
}

void list_del(struct list_head *entry)
{
    __list_del(entry);
    entry->next = entry->prev = NULL;
}

struct node {
    struct list_head link;
    int x, y;
};

struct node *node_new(struct list_head *free_list)
{
    struct node *n;
    if (list_empty(free_list)) {
        n = malloc(sizeof(*n));
    } else {
        n = list_first_entry(free_list, struct node, link);
        list_del(&n->link);
    }
    return n;
}

void bfs(char **board, int row_size, int col_size,
         struct list_head *queue, struct list_head *free_list)
{
    while (!list_empty(queue)) {
        struct node *n;
        struct node *node = list_first_entry(queue, struct node, link);
        board[node->x][node->y] = 'P';

        if (node->x > 0 && board[node->x - 1][node->y] == 'O') {
            n = node_new(free_list);
            n->x = node->x - 1;
            n->y = node->y;
            board[n->x][n->y] = 'P';
            list_add_tail(&n->link, queue);
        }

        if (node->y < col_size - 1 && board[node->x][node->y + 1] == 'O') {
            n = node_new(free_list);
            n->x = node->x;
            n->y = node->y + 1;
            board[n->x][n->y] = 'P';
            list_add_tail(&n->link, queue);
        }

        if (node->x < row_size - 1 && board[node->x + 1][node->y] == 'O') {
            n = node_new(free_list);
            n->x = node->x + 1;
            n->y = node->y;
            board[n->x][n->y] = 'P';
            list_add_tail(&n->link, queue);
        }

        if (node->y > 0 && board[node->x][node->y - 1] == 'O') {
            n = node_new(free_list);
            n->x = node->x;
            n->y = node->y - 1;
            board[n->x][n->y] = 'P';
            list_add_tail(&n->link, queue);
        }

        list_del(&node->link);
        list_add(&node->link, free_list);
    }
}

void solve(char **board, int board_row_size, int *board_col_size)
{
    int i, j;
    struct node *n;
    struct list_head queue, free_list;

    INIT_LIST_HEAD(&queue);
    INIT_LIST_HEAD(&free_list);

    for (i = 0; i < *board_col_size; i++) {
        if (board[0][i] == 'O') {
            n = node_new(&free_list);
            n->x = 0;
            n->y = i;
            list_add_tail(&n->link, &queue);
            bfs(board, board_row_size, *board_col_size, &queue, &free_list);
        }
    }

    for (i = 0; i < *board_col_size; i++) {
        if (board[board_row_size - 1][i] == 'O') {
            n = node_new(&free_list);
            n->x = board_row_size - 1;
            n->y = i;
            list_add_tail(&n->link, &queue);
            bfs(board, board_row_size, *board_col_size, &queue, &free_list);
        }
    }

    for (i = 0; i < board_row_size; i++) {
        if (board[i][0] == 'O') {
            n = node_new(&free_list);
            n->x = i;
            n->y = 0;
            list_add_tail(&n->link, &queue);
            bfs(board, board_row_size, *board_col_size, &queue, &free_list);
        }
    }

    for (i = 0; i < board_row_size; i++) {
        if (board[i][*board_col_size - 1] == 'O') {
            n = node_new(&free_list);
            n->x = i;
            n->y = *board_col_size - 1;
            list_add_tail(&n->link, &queue);
            bfs(board, board_row_size, *board_col_size, &queue, &free_list);
        }
    }

    for (i = 0; i < board_row_size; i++) {
        for (j = 0; j < *board_col_size; j++) {
            board[i][j] = board[i][j] == 'P' ? 'O' : 'X';
        }
    }
}

int main(int argc, char **argv)
{
    struct Object inputs[] = {
        { .s = "XXXX" "XOOX" "XXOX" "XOXX", .rows = 4, .cols = 4 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        char *s = inputs[i].s;
        int rows = inputs[i].rows;
        int cols = inputs[i].cols;

        char **board = make_board(s, rows, cols);

        printf("\n Input:\n\n");
        print_board(board, rows, cols);

        solve(board, rows, &cols);

        printf("\n Output:\n");
        print_board(board, rows, cols);

        free_board(board, rows);
    }

    return EXIT_SUCCESS;
}
