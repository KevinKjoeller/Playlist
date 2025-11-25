#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <stddef.h>

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

// Insert a node at a specific position
void insert_at(Node **list, size_t index, Node *new_node);

// Delete a node at a specific position and return its data
void *delete_at(Node **list, size_t index);

// Append a node to the end of the list
void append(Node **list, Node *new_node);

// Free the entire list
void free_list(Node **list);

#endif // SINGLY_LINKED_LIST_H
