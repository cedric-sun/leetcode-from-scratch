#include <stdlib.h>
#include <stdint.h>

/**********************************************************
 *                       HASH TABLE
 **********************************************************/
#define MAX_LF 0.75

typedef struct {
    int k;
    size_t v;
    ht_entry *next;
} ht_entry;

typedef struct {
    size_t cap;
    double lf;
    size_t enc_cnt;
    ht_entry **buckets;
} hash_table;

static void put(hash_table *ht, int k, size_t v) {
    ht->lf = (double)ht->ent_cnt/ht->cap;
    if (ht->lf > MAX_LF) { // extend + rehash
        size_t new_cap = ht->cap<<1;
        ht_entry **new_buckets = calloc(new_cap,sizeof(*new_buckets));
        for (size_t i=0;i<ht->cap;i++) {
            ht_entry *cur = *( ht->buckets+i );
            while (cur){
                size_t ni = (size_t)cur->k & (new_cap -1);
                ht_entry *next = cur->next;
                cur->next = new_buckets[ni];
                new_buckets[ni] = cur;
                cur=next;
            }
        }
        free(ht->buckets);
        ht->buckets=new_buckets;
        ht->cap = new_cap;
    }
    size_t i = (size_t)k & (ht->cap-1);
    ht_entry *new_ht_entry = malloc(sizeof( *new_ht_entry ));
    new_ht_entry->k = k;
    new_ht_entry->v = v;
    new_ht_entry->next = ht->buckets[i];
    ht->buckets[i]=new_ht_entry;
    ht->ent_cnt++;
}

// return SIZE_MAX for empty bucket
static size_t get(hash_table *ht, int k) {
    size_t i = (size_t)k & (ht->cap-1);
    if (ht->buckets[i]){
        for (ht_entry *cur=*(ht->buckets+i);cur;cur=cur->next) {
            if (cur->k == k) {
                return cur->v;
            }
        }
    }
    return SIZE_MAX;
}

static hash_table *init() {
    hash_table *ht = malloc(sizeof(*ht));
    ht->cap = 128;
    ht->lf=0;
    ht->enc_cnt=0;
    ht->buckets = calloc(cap,sizeof(*buckets));
    return ht;
}

static void ht_free(hash_table *ht) {
    for (size_t i=0;i<ht->cap;i++) {
        ht_entry *cur = *(ht->buckets + i);
        while (cur) {
            ht_entry *next = cur->next;
            free(cur);
            cur=next;
        }
    }
    free(ht->buckets);
    free(ht);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int *ret =malloc(2*sizeof *ret);
    *returnSize=2;

    return ret;
}
