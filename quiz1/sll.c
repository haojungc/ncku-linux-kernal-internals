#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

typedef struct __node {                   
    int value;
    struct __node *next;
} node_t;

static void list_display(node_t *list);

static inline node_t *list_make_node_t(node_t *list, int value) {
    node_t *node = malloc(sizeof(node_t));
    if (node == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(EXIT_FAILURE);
    }
    node->value = value;
    node->next = list;
    return node;
}

static inline void list_add_node_t(node_t **list, node_t *node_t) {
    node_t->next = *list;
    *list = node_t;
}

static inline void list_concat(node_t **left, node_t *right) {
    while (*left)
        left = &((*left)->next);
    *left = right;
}

static void quicksort(node_t **list)
{
    if (!*list)
        return;

    node_t *pivot = *list;
    int value = pivot->value;
    node_t *p = pivot->next;
    pivot->next = NULL;

    node_t *left = NULL, *right = NULL;
    while (p) {
        node_t *n = p;
        p = p->next;
        list_add_node_t(n->value > value ? &right : &left, n);
    }

    quicksort(&left);
    quicksort(&right);

    node_t *result = NULL;
    list_concat(&result, left);
    list_concat(&result, pivot);
    list_concat(&result, right);
    *list = result;
}

static void quicksort_non_recursive(node_t **list)
{
#define MAX_LEVELS 1000
    node_t *begin[MAX_LEVELS], *end[MAX_LEVELS];

    begin[0] = *list;
    end[0] = NULL;
    int i = 0;

    while (i >= 0 && i < MAX_LEVELS - 1) {
        /* Initializes pivot, left, and right */
        node_t *pivot = begin[i];
        int value = pivot->value;
        node_t *ptr = pivot->next;
        pivot->next = NULL;
        node_t *left = NULL, *right = end[i];

        /* Splits the current list into two sublists */
        while (ptr != end[i]) {
           node_t *n = ptr;
           ptr = ptr->next;
           list_add_node_t(n->value > value ? &right : &left, n);
        }

        node_t *result = NULL;
        list_concat(&result, left);
        list_concat(&result, pivot);
        list_concat(&result, right);

        /* Resets the beginning and ending nodes of the sublists.
         * left: i; right: i + 1 */
        begin[i] = result;
        begin[i + 1] = right; /* right == pivot->next */
        end[i + 1] = end[i];
        end[i] = pivot;

        /* `right` has only 0-1 nodes */
        if (begin[i + 1] != end[i + 1] && begin[i + 1]->next != end[i + 1]) {
            i++;
        } else {
            /* `left` has only 0-1 nodes */
            while (begin[i] == end[i] || begin[i]->next == end[i]) {
                if (i > 0)
                    /* Concatenates the list on the LHS and `left` */
                    end[i - 1]->next = begin[i];
                else {
                    *list = begin[i];
                    return;
                }
                i--;
            }
        }
    }
    fprintf(stderr, "sorting failed, max level reached\n");
    exit(EXIT_FAILURE);
#undef MAX_LEVELS
}

static bool list_is_ordered(node_t *list) {
    bool first = true;
    int value;
    while (list) {
        if (first) {
            value = list->value;
            first = false;
        } else {
            if (list->value < value)
                return false;
            value = list->value;
        }
        list = list->next;
    }
    return true;
}

static void list_display(node_t *list) {
    printf("%s IN ORDER : ", list_is_ordered(list) ? "   " : "NOT");
    while (list) {
        printf("%d ", list->value);
        list = list->next;
    }
    printf("\n");
}

static void list_free(node_t **list) {
    node_t *head = *list;
    node_t *next;
    while (head) {
        next = head->next;
        free(head);
        head = next;
    }
}

int main(int argc, char **argv) {
    srandom(time(NULL));
    size_t count = 20;

    node_t *list = NULL;
    while (count--)
        list = list_make_node_t(list, random() % 1024);

    list_display(list);
    quicksort_non_recursive(&list);
    list_display(list);

    if (!list_is_ordered(list))
        return EXIT_FAILURE;

    list_free(&list);
    return EXIT_SUCCESS;
}
