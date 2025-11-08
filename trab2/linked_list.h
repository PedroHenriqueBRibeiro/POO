#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "appointments.h"

struct Node { 
    Appointment* data; 
    Node* next; 
};

Node* list_push_back(Node* h, Appointment* d);
void list_free(Node* h);
size_t list_len(Node* h);
Appointment** list_to_array(Node* h, size_t* out_n);

#endif