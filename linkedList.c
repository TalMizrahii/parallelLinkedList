#include "linkedList.h"

/**
 *  Initialize a linked list with the head node having the minimum integer as value.
 * @return node_t* - The head node of the linked list.
 */
node_t *init_list(void) {
    node_t *head = malloc(sizeof(node_t));
    head->next = NULL;
    head->value = INT_MIN;
    head->lock = malloc(sizeof(omp_lock_t));
    omp_init_lock(head->lock);
    return head;
}

/**
 * *THE CODE WAS INSPIRED BY THE LECTURE'S CODE*
 * Insert a new node with the given value in the linked list.
 * @param head
 * @param val
 */
void sorted_insert(node_t *head, int val) {
    /* Find the right place to insert */
    node_t *ptr = head->next;
    node_t *prev = head;

    while (ptr != NULL && ptr->value < val) {
        prev = ptr;
        ptr = ptr->next;
    }

    /* Lock the element that may be modified */
    omp_set_lock(prev->lock);

    /* Confirm that the element is still in the right place */
    if (prev->next != ptr) {
        ptr = prev->next;
        while (ptr != NULL && ptr->value < val) {
            omp_set_lock(ptr->lock);
            omp_unset_lock(prev->lock);
            prev = ptr;
            ptr = ptr->next;
        }
    }
    printf("Inserting %d\n", val);
    /* Insert the new node */
    node_t *new_node = malloc(sizeof(node_t));
    new_node->value = val;
    new_node->next = ptr;
    new_node->lock = malloc(sizeof(omp_lock_t));
    omp_init_lock(new_node->lock);
    prev->next = new_node;
    omp_unset_lock(prev->lock);
}