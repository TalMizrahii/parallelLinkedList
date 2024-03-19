#include "linkedList.h"

/**
 *  Initialize a linked list with the head node having the minimum integer as value.
 * @return node_t* - The head node of the linked list.
 */
node_t *init_list(void) {
    // Allocate memory for the head node.
    node_t *head = malloc(sizeof(node_t));
    if (!head) {
        printf("Error allocating memory for head\n");
        exit(1);
    }
    // Initialize the head node.
    head->next = NULL;
    head->value = INT_MIN;
    head->lock = malloc(sizeof(omp_lock_t));
    if (!head->lock) {
        printf("Error allocating memory for lock\n");
        exit(1);
    }
    // Initialize the lock for the head node.
    omp_init_lock(head->lock);
    // Initialize the list size.
    return head;
}

/**
 * *THE CODE WAS INSPIRED BY THE LECTURE'S CODE*
 * Insert a new node with the given value in the linked list.
 * @param head
 * @param val
 */
void sorted_insert(node_t *head, int val) {
    // Check if the head node is NULL.
    if (!head)
        return;
    // Set the head node as the current node.
    node_t *ptr = head->next;
    node_t *prev = head;
    // Traverse the linked list to find the right place to insert the new node.
    while (ptr != NULL && ptr->value < val) {
        prev = ptr;
        ptr = ptr->next;
    }
    // Lock the previous node.
    omp_set_lock(prev->lock);

    // Confirm that the element is still in the right place.
    if (prev->next != ptr) {
        ptr = prev->next;
        while (ptr != NULL && ptr->value < val) {
            omp_set_lock(ptr->lock);
            omp_unset_lock(prev->lock);
            prev = ptr;
            ptr = ptr->next;
        }
    }
    // Insert the new node.
    node_t *new_node = malloc(sizeof(node_t));
    if (!new_node) {
        printf("Error allocating memory for new_node\n");
        exit(1);
    }
    // Initialize the new node.
    new_node->value = val;
    new_node->next = ptr;
    new_node->lock = malloc(sizeof(omp_lock_t));
    if (!new_node->lock) {
        printf("Error allocating memory for new_node->lock\n");
        exit(1);
    }
    // Initialize the lock for the new node.
    omp_init_lock(new_node->lock);
    prev->next = new_node;
    // Unlock the previous node.
    omp_unset_lock(prev->lock);
}

/**
 * Remove the node with the given value from the linked list.
 * @param head The head node of the linked list.
 * @param val The value to remove.
 */
void remove_val(node_t *head, int val) {
    // Check if the head node is NULL.
    if (!head)
        return;
    // Set the head node as the current node.
    node_t *prev = head;
    // Lock the previous node.
    omp_set_lock(prev->lock);
    node_t *ptr = head->next;
    // Traverse the linked list to find the node with the given value.
    while (ptr != NULL && ptr->value != val) {
        // Lock the current node.
        omp_set_lock(ptr->lock);
        // If the current node's value matches the target value, remove the node.
        if (ptr->value == val) {
            // Remove the node.
            prev->next = ptr->next;
            omp_unset_lock(ptr->lock);
            omp_destroy_lock(ptr->lock);
            free(ptr->lock);
            ptr->lock = NULL;
            free(ptr);
            ptr = NULL;
            // Get out of the loop.
            break;
        }
        // Move to the next node.
        omp_unset_lock(prev->lock);
        prev = ptr;
        ptr = ptr->next;
    }
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
    // Check if the head node is NULL.
    if (!head)
        return 0;
    // Set the head node as the current node.
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
    // Check if the head node is NULL.
    if (!head)
        return 0;
    // Iterate through the linked list and count the number of nodes.
    int length = 0;
    node_t *current = head->next;
    while (current != NULL) {
        // Increment the length.
        #pragma omp atomic
        length++;
        // Move to the next node.
        current = current->next;
    }
    // Return the length of the linked list.
    return length;
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
}


