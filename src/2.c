#include <stdlib.h>

// struct ListNode {
//    int val;
//    struct ListNode* next;
//};

struct ListNode* addTwoNumbers( struct ListNode* l1, struct ListNode* l2 ) {
    struct ListNode *res, *cur;
    res = cur = malloc( sizeof *res );
    for ( int c = 0;; ) {
        cur->next = NULL;
        int d1 = l1 ? l1->val : 0, d2 = l2 ? l2->val : 0;
        int d = ( d1 + d2 + c ) % 10;
        c = ( d1 + d2 + c ) / 10;
        cur->val = d;
        if ( l1 ) l1 = l1->next;
        if ( l2 ) l2 = l2->next;
        if ( !l1 && !l2 && !c ) break;
        cur = cur->next = malloc( sizeof *res );
    }
    return res;
}
