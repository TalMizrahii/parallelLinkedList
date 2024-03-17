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
    head->listSize = 1;
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
    omp_set_lock(head->lock);
#pragma omp atomic
    ++head->listSize;
    omp_unset_lock(head->lock);
    omp_unset_lock(prev->lock);
}

void remove_val(node_t *head, int val) {
    // Find the right place to insert.
    node_t *ptr = head->next;
    node_t *prev = head;

    while (ptr != NULL && ptr->value != val) {
        prev = ptr;
        ptr = ptr->next;
    }
    // If the value is not in the list.
    if (ptr == NULL) {
        return;
    }
    // Lock the element that may be modified.
    omp_set_lock(prev->lock);
    // Modify the previous node to point to the next node.
    prev->next = ptr->next;
    // Free the memory of the removed node.
    omp_destroy_lock(ptr->lock);
    free(ptr->lock);
    ptr->lock = NULL;
    free(ptr);
    ptr = NULL;
    // Decrease the list size.
    omp_set_lock(head->lock);
#pragma omp atomic
    --head->listSize;
    omp_unset_lock(head->lock);
    // Unlock the previous node.
    omp_unset_lock(prev->lock);
}

/**
 * Find the given value in the linked list.
 * @param head The head node of the linked list.
 * @param val The value to find in the linked list.
 * @return 1 if the value is found, 0 otherwise.
 */
int find_val(node_t *head, int val) {
    node_t *current = head;
    // Iterate through the linked list.
    while (current != NULL) {
        // Check if the current node's value matches the target value.
        if (current->value == val) {
            return 1;
        }
        // Move to the next node.
        current = current->next;
    }
    // The value was not found in the linked list.
    return 0;
}

/**
 * Return the length of the linked list.
 * @param head The head node of the linked list.
 * @return The length of the linked list as int.
 */
int get_len(node_t *head) {
    return head->listSize;
}

/**
 * Free the memory of the linked list.
 * @param head The head node of the linked list.
 */
void free_list(node_t *head) {
    // Iterate through the linked list and free the memory of each node.
    node_t *current = head;
    node_t *next;
    // Free the memory of each node.
    while (current != NULL) {
        // Move to the next node.
        next = current->next;
        // Free the memory of the current node.
        omp_destroy_lock(current->lock);
        free(current->lock);
        current->lock = NULL;
        free(current);
        // Move to the next node.
        current = next;
    }
    // Set the head to NULL.
    head = NULL;
}