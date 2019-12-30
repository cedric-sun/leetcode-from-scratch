#include <stdbool.h>
#include <stdlib.h>

#define LOA 26

typedef struct _trie {
    bool exist;
    struct _trie* child[LOA];
} Trie;

/** Initialize your data structure here. */

Trie* trieCreate() {
    Trie* ret = calloc( 1, sizeof *ret );
    return ret;
}

/** Inserts a word into the trie. */
void trieInsert( Trie* obj, char* word ) {
    for ( char* p = word; *p; p++ ) {
        int idx = *p - 'a';
        if ( !obj->child[idx] ) obj->child[idx] = trieCreate();
        obj = obj->child[idx];
    }
    obj->exist = true;
}

/** Returns if the word is in the trie. */
bool trieSearch( Trie* obj, char* word ) {
    for ( char* p = word; *p; p++ ) {
        int idx = *p - 'a';
        if ( obj->child[idx] )
            obj = obj->child[idx];
        else
            return false;
    }
    return obj->exist;
}

/** Returns if there is any word in the trie that starts with the given prefix.
 */
bool trieStartsWith( Trie* obj, char* prefix ) {
    for ( char* p = prefix; *p; p++ ) {
        int idx = *p - 'a';
        if ( obj->child[idx] )
            obj = obj->child[idx];
        else
            return false;
    }
    return true;
}

void trieFree( Trie* obj ) {
    for ( size_t i = 0; i < LOA; i++ )
        if ( obj->child[i] ) trieFree( obj->child[i] );
    free( obj );
}

#include <stdio.h>
int main( void ) {
    // Your Trie struct will be instantiated and called as such:
    Trie* obj = trieCreate();
    trieInsert( obj, "apple" );

    bool param_2 = trieSearch( obj, "apple" );

    bool param_3 = trieStartsWith( obj, "apg" );

    printf( "%d %d\n", param_2, param_3 );

    trieFree( obj );
}
