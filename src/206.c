// Definition for singly-linked list.
//struct ListNode {
//    int val;
//    struct ListNode *next;
//};

#include <stdlib.h>

static inline struct ListNode *new_node( int val, struct ListNode *next ) {
    struct ListNode *ret = malloc( sizeof *ret );
    ret->val = val;
    ret->next = next;
    return ret;
}

struct ListNode *reverseList( struct ListNode *head ) {
    if ( head == NULL ) return NULL;
    struct ListNode *rhead = new_node( (int)0xdeadbeef, NULL );
    while ( head ) {
        rhead->next = new_node( head->val, rhead->next );
        head = head->next;
    }
    return rhead->next;
}
