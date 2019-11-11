#include <stdio.h>

/**********************************************************
 *                       HASH TABLE
 **********************************************************/
#include <stdint.h>
#include <stdlib.h>
#define MAX_LF 0.75

typedef struct _ht_entry{
    int k;
    int : 32; // padding
    size_t v;
    struct _ht_entry *next;
} ht_entry;

typedef struct {
    size_t cap;
    double lf;
    size_t ent_cnt;
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
    node *cur = *(ht->buckets+i);
    //TODO: check duplication

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
    ht->ent_cnt=0;
    ht->buckets = calloc(ht->cap,sizeof(*ht->buckets));
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


/**************************************
 *              UNIT TEST
 **************************************/

int main() {
    hash_table *ht0 = init();
    put(ht0, -13, 114514);
    size_t v = get(ht0,-13);
    printf("%lu\n",v);
    v = get(ht0,-11);
    printf("%lu\n",v);
    ht_free(ht0);
}
