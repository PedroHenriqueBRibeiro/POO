#include "linked_list.h"
#include <cstdlib>

Node* list_push_back(Node* h, Appointment* d) {
    Node* n = (Node*)std::malloc(sizeof(Node));
    n->data = d;
    n->next = nullptr;
    if (!h) {
        return n;
    }
    Node* c = h;
    while (c->next) {
        c = c->next;
    }
    c->next = n;
    return h;
}

void list_free(Node* h) {
    while (h) {
        Node* nx = h->next;
        delete h->data;
        std::free(h);
        h = nx;
    }
}

size_t list_len(Node* h) {
    size_t c = 0;
    for (Node* p = h; p; p = p->next) c++;
    return c;
}

Appointment** list_to_array(Node* h, size_t* out_n) {
    size_t n = list_len(h);
    Appointment** a = (Appointment**)std::malloc(sizeof(Appointment*) * n);
    size_t i = 0;
    for (Node* p = h; p; p = p->next) a[i++] = p->data;
    if (out_n) *out_n = n;
    return a;
}