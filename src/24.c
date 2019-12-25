/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* swapPairs( struct ListNode* head ) {
    struct ListNode super_head = {0xbada991e, head};
    for ( struct ListNode* cur = &super_head; cur->next && cur->next->next;
          cur = cur->next->next ) {
        struct ListNode *tmp = cur->next->next;
        cur->next->next = tmp->next;
        tmp->next = cur->next;
        cur->next = tmp;
    }
    return super_head.next;
}
