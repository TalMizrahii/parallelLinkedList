#include <stdio.h>
#include "linkedList.h"

#define MAX_NODES 10000
#define MAX_VAL 1000000

int main(){
    node_t *head = init_list();
    /* Insert random values */
    #pragma omp parallel for
    for (int i = 0; i < MAX_NODES; i++) {
        sorted_insert(head, rand() % MAX_VAL);
    }

    /* Check that the list is sorted */
    node_t *ptr = head->next;
    int last_val = head->value;
    int count = 0;

    while (ptr != NULL) {
        if (ptr->value < last_val) {
            printf("[-] List is not sorted\n");
            return 1;
        }
        last_val = ptr->value;
        ptr = ptr->next;
        count++;
    }

    if (count != MAX_NODES) {
        printf("[-] List size is not correct\n");
        return 1;
    }

    printf("[+] Correctness test passed\n");

    return 0;
}
