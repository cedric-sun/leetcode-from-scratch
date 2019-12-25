#include <stdlib.h>

// Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};

static void sift_down( struct ListNode **heap, const size_t heap_sz,
                       size_t i ) {
    while ( 1 ) {
        size_t max_idx = i;
        const size_t lc_idx = ( i << 1 ) + 1, rc_idx = ( i << 1 ) + 2;
        if ( lc_idx < heap_sz && heap[lc_idx]->val < heap[max_idx]->val )
            max_idx = lc_idx;
        if ( rc_idx < heap_sz && heap[rc_idx]->val < heap[max_idx]->val )
            max_idx = rc_idx;
        if ( max_idx != i ) {
            struct ListNode *tmp = heap[max_idx];
            heap[max_idx] = heap[i];
            heap[i] = tmp;
            i = max_idx;
        } else {
            break;
        }
    }
}

struct ListNode *mergeKLists( struct ListNode **lists, int listsSize ) {
    {
        // remove empty list
        size_t non_null_lists_sz = 0;
        for ( size_t i = 0; i < listsSize; i++ )
            if ( lists[i] ) lists[non_null_lists_sz++] = lists[i];
        listsSize = non_null_lists_sz;
    }

    struct ListNode super_head = {0xbada991e, NULL};
    struct ListNode *cur = &super_head;
    for ( int i = ( listsSize >> 1 ) - 1; ~i; i-- )
        sift_down( lists, listsSize, i );
    while ( listsSize ) {
        cur = cur->next = malloc( sizeof *cur );
        *cur = ( struct ListNode ){lists[0]->val, NULL};
        if ( lists[0]->next )
            lists[0] = lists[0]->next;
        else
            lists[0] = lists[--listsSize];

        sift_down( lists, listsSize, 0 );
    }

    return super_head.next;
}

/* UNIT TEST */

#include <stdarg.h>
#include <stdio.h>

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

#include <string.h>
int main() {
    struct ListNode *lls[] = {
        make_vargs( 4, 1, 4, 7, 10 ),
        make_vargs( 4, 2, 5, 8, 11 ),
        make_vargs( 4, 3, 6, 9, 12 )
    };
#define lists_cnt ( sizeof lls / sizeof *lls )
    struct ListNode *lls_copy[lists_cnt];
    memcpy( lls_copy, lls, lists_cnt * sizeof *lls_copy );

    struct ListNode *ans = mergeKLists( lls_copy, lists_cnt );
    for ( struct ListNode *cur = ans; cur; cur = cur->next )
        printf( "%5d", cur->val );
    putchar( '\n' );
    ln_chain_free( ans );

    for ( size_t i = 0; i < lists_cnt; i++ ) {
        ln_chain_free( lls[i] );
    }
}
