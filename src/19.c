/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
#define BAD_APPLE 0xdeadc0de

struct ListNode* removeNthFromEnd( struct ListNode* head, int n ) {
    struct ListNode super_head = {BAD_APPLE, head};
    struct ListNode* pred_del = NULL;
    for ( struct ListNode* cur = &super_head; cur; cur = cur->next ) {
        if ( pred_del ) pred_del = pred_del->next;
        if ( !n-- ) pred_del = &super_head;
    }
    struct ListNode* tmp = pred_del->next;
    if ( tmp ) pred_del->next = tmp->next;
    free( tmp );
    return super_head.next;
}
