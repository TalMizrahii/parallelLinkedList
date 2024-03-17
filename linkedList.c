#include "linkedList.h"

/**
 *  Initialize a linked list with the head node having the minimum integer as value.
 * @return node_t* - The head node of the linked list.
 */
node_t *init_list(void) {
    node_t *head = malloc(sizeof(node_t));
    if(!head){
        printf("Error allocating memory for head\n");
        exit(1);
    }
    head->next = NULL;
    head->value = INT_MIN;
    head->lock = malloc(sizeof(omp_lock_t));
    if(!head->lock){
        printf("Error allocating memory for lock\n");
        exit(1);
    }
    head->listSize = 0;
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
    if(!head)
        return;

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
    /* Insert the new node */
    node_t *new_node = malloc(sizeof(node_t));
    if(!new_node){
        printf("Error allocating memory for new_node\n");
        exit(1);
    }
    new_node->value = val;
    new_node->next = ptr;
    new_node->lock = malloc(sizeof(omp_lock_t));
    if(!new_node->lock){
        printf("Error allocating memory for new_node->lock\n");
        exit(1);
    }
    omp_init_lock(new_node->lock);
    prev->next = new_node;
    #pragma omp atomic
    head->listSize++;
    omp_unset_lock(prev->lock);
}

void remove_val(node_t *head, int val) {
    node_t *prev = head;
    omp_set_lock(prev->lock);
    node_t *ptr = head->next;

    while (ptr != NULL && ptr->value != val) {
        omp_set_lock(ptr->lock);
        if (ptr->value == val) {
            prev->next = ptr->next;
            #pragma omp atomic
            head->listSize--;
            omp_unset_lock(ptr->lock);
            omp_destroy_lock(ptr->lock);
            free(ptr->lock);
            ptr->lock = NULL;
            free(ptr);
            ptr = NULL;
            break;
        }
        omp_unset_lock(prev->lock);
        prev = ptr;
        ptr = ptr->next;
    }
    omp_unset_lock(prev->lock);
}

/**
 * Find the given value in the linked list.
 * @param head The head node of the linked list.
 * @param val The value to find in the linked list.
 * @return 1 if the value is found, 0 otherwise.
 */
int find_val(node_t *head, int val) {
    if(!head)
        return 0;
    //    printf("Finding %d\n", val);
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
    int length = 0;
    node_t *current = head->next;

    // Traverse the linked list and count the nodes
    while (current != NULL) {
        #pragma omp atomic
        length++; // increment length atomically to ensure thread safety

        current = current->next;
    }
    return length;
//    return head->listSize;
}

/**
 * Free the memory of the linked list.
 * @param head The head node of the linked list.
 */
void free_list(node_t *head) {
    //    printf("Freeing list\n");
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


