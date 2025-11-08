#ifndef LIST_H
#define LIST_H

#include <stddef.h>

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

Node *list_push_back(Node *h, void *d);
void list_free(Node *h, void (*free_data)(void *));
size_t list_len(Node *h);
void **list_to_array(Node *h, size_t *out_n);

#endif