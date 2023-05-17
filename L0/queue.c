/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

#include "harness.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new() {
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (!q) {
        return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q) {
    if (!q) {
        return;
    }
    /* How about freeing the list elements? */
    list_ele_t *ele_ptr = q->head;
    while (ele_ptr) {
        list_ele_t *ptr_to_be_freed = ele_ptr;
        ele_ptr = ele_ptr->next;
        free(ptr_to_be_freed);
        ptr_to_be_freed = NULL;
    }
    /* Free queue structure */
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_head(queue_t *q, int v) {
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    if (!q) {
        return false;
    }
    newh = malloc(sizeof(list_ele_t));
    /* What if malloc returned NULL? */
    if (!newh) {
        return false;
    }
    newh->value = v;
    newh->next = q->head;
    // if empty queue
    if (!q->head) {
        q->tail = newh;
    }
    q->head = newh;
    ++q->size;
    return true;
}

/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_tail(queue_t *q, int v) {
    /* You need to write the complete code for this function */
    if (!q) {
        return false;
    }
    if (!q->head) {
        return q_insert_head(q, v);
    }
    list_ele_t *newt = malloc(sizeof(list_ele_t));
    if (!newt) {
        return false;
    }
    newt->value = v;
    newt->next = NULL;
    q->tail->next = newt;
    q->tail = newt;
    ++q->size;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If vp non-NULL and element removed, store removed value at *vp.
  Any unused storage should be freed
*/
bool q_remove_head(queue_t *q, int *vp) {
    /* You need to fix up this code. */
    if (!q || !q->head) {
        return false;
    }
    list_ele_t *prev_head = q->head;
    q->head = q->head->next;
    if (!q->head) {
        q->tail = NULL;
    }
    q->size -= 1;
    if (vp) {
        *vp = prev_head->value;
    }
    free(prev_head);
    prev_head = NULL;

    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q) {
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (!q) {
        return 0;
    }
    return q->size;
}

/*
  Reverse elements in queue.

  Your implementation must not allocate or free any elements (e.g., by
  calling q_insert_head or q_remove_head).  Instead, it should modify
  the pointers in the existing data structure.
 */
void q_reverse(queue_t *q) {
    if (!q || !q->head || q->head == q->tail) {
        return;
    }
    list_ele_t *cur_ptr = q->head;
    q->tail = q->head;

    list_ele_t *prev = NULL;
    while (cur_ptr) {
        list_ele_t *itr_next_ptr = cur_ptr->next;
        cur_ptr->next = prev;

        prev = cur_ptr;
        cur_ptr = itr_next_ptr;
    }

    q->head = prev;
}
