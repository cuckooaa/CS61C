#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    /* your code here */
    if (head == NULL || head->next == NULL) {
        return 0;
    }

    node *tortoise = head;
    node *hare = head;

    // loop contition: hare can move.
    while (hare != NULL && hare->next != NULL) {
        tortoise = tortoise->next;       // tortoise gose two steps.
        hare = hare->next->next;         // hare goes two steps.

        if (tortoise == hare) {
            // if they meet, there will be a cycle.
            return 1;
        }
    }

    // no cycle
    return 0;
}
