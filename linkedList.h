#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct node_s node_t;

node_t *init_list(void);
void sorted_insert(node_t *head, int val);
void remove_val(node_t *head, int val);
int find_val(node_t *head, int val);
int get_len(node_t *head);
void free_list(node_t *head);

#endif