#include <stddef.h>

// Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *proceed( struct ListNode *p, size_t k ) {
    while ( k-- && p ) {
        p = p->next;
    }
    if ( ~k ) return NULL;
    return p;
}

static struct ListNode *stop;

static void dfs( struct ListNode *p, struct ListNode *parent ) {
    if ( p == stop ) return;
    dfs( p->next, p );
    p->next = parent;
}

struct ListNode *reverseKGroup( struct ListNode *head, int k ) {
    if ( !k || k == 1 ) return head;
    struct ListNode super_head = {0xbada991e, head};
    for ( struct ListNode *cur = &super_head, *gp_end, *jump_dest;
          jump_dest = cur->next, gp_end = proceed( cur, k ); cur = jump_dest ) {
        stop = gp_end->next;
        dfs( cur->next, gp_end->next );
        cur->next = gp_end;
    }
    return super_head.next;
}

/*********** UNIT TEST ***************/
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

struct ListNode *make( int *arr, size_t sz ) {
    struct ListNode super_head = {0, NULL}, *cur = &super_head;
    while ( sz-- ) {
        cur = cur->next = malloc( sizeof *cur );
        *cur = ( struct ListNode ){*arr++, NULL};
    }
    return super_head.next;
}

struct ListNode *make_vargs( size_t cnt, ... ) {
    va_list ap;
    va_start( ap, cnt );
    int *arr = malloc( cnt * sizeof *arr );
    for ( size_t i = 0; i < cnt; i++ ) arr[i] = va_arg( ap, int );
    va_end( ap );
    struct ListNode *ret = make( arr, cnt );
    free( arr );
    return ret;
}

void ln_chain_free( struct ListNode *head ) {
    while ( head ) {
        struct ListNode *next = head->next;
        free( head );
        head = next;
    }
}

void test0() {
    struct ListNode *l0 = make_vargs( 6, 1, 2, 3, 4, 5, 6 );
    struct ListNode *ans = reverseKGroup( l0, 2 );
    for ( struct ListNode *cur = ans; cur; cur = cur->next )
        printf( "%5d", cur->val );
    putchar( '\n' );
    ln_chain_free( ans );
}

void test1() {
    struct ListNode *ans = reverseKGroup( NULL, 0 );
    for ( struct ListNode *cur = ans; cur; cur = cur->next )
        printf( "%5d", cur->val );
    putchar( '\n' );
}

int main() { test0(); }
