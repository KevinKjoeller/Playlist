#include "singly_linked_list.h"
#include <stdlib.h>

void insert_at(Node **list, size_t index, Node *new_node) {
    if (index == 0) {
        new_node->next = *list;
        *list = new_node;
        return;
    }
    
    Node *current = *list;
    for (size_t i = 0; i < index - 1 && current != NULL; i++) {
        current = current->next;
    }
    
    if (current == NULL) return; // Index out of bounds
    
    new_node->next = current->next;
    current->next = new_node;
}

void *delete_at(Node **list, size_t index) {
    if (*list == NULL) return NULL;
    
    Node *to_delete;
    
    if (index == 0) {
        to_delete = *list;
        *list = (*list)->next;
        void *data = to_delete->data;
        free(to_delete);
        return data;
    }
    
    Node *current = *list;
    for (size_t i = 0; i < index - 1 && current->next != NULL; i++) {
        current = current->next;
    }
    
    if (current->next == NULL) return NULL; // Index out of bounds
    
    to_delete = current->next;
    current->next = to_delete->next;
    void *data = to_delete->data;
    free(to_delete);
    return data;
}

void append(Node **list, Node *new_node) {
    if (*list == NULL) {
        *list = new_node;
        return;
    }
    
    Node *current = *list;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void free_list(Node **list) {
    Node *current = *list;
    while (current != NULL) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    *list = NULL;
}
