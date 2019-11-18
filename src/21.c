//struct ListNode {
//    int val;
//    struct ListNode* next;
//};

#include <stdint.h>
#include <stdlib.h>

static inline struct ListNode* new_node( int val ) {
    struct ListNode* ret = malloc( sizeof *ret );
    ret->val = val;
    ret->next = NULL;
    return ret;
}

struct ListNode* mergeTwoLists( struct ListNode* l1, struct ListNode* l2 ) {
    struct ListNode *head, *cur;
    head = cur = new_node( 0xdeadbeef );
    while ( l1 || l2 ) {
        intmax_t l1v=INTMAX_MAX, l2v=INTMAX_MAX,v;
        if ( l1 ) l1v = l1->val;
        if ( l2 ) l2v = l2->val;
        if ( l1v < l2v )    v = l1v, l1 = l1->next;
        else                v = l2v, l2 = l2->next;
        cur = cur->next = new_node( v );
    }
    cur = head->next;
    free( head );
    return cur;
}
