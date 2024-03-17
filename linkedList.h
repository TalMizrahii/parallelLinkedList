#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>
#include "omp.h"

typedef struct node_s {
    int value;
    int listSize;
    struct node_s *next;
    omp_lock_t *lock;
} node_t;

node_t *init_list(void);
void sorted_insert(node_t *head, int val);
void remove_val(node_t *head, int val);
int find_val(node_t *head, int val);
int get_len(node_t *head);
void free_list(node_t *head);

#endif
