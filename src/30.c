// aho corasick
#include <stdlib.h>
#include <string.h>

#define TRIE_MAX_NODE_N 100008
#define ALPHA_SZ 26

// .bss section is inited with zero
static int tr[TRIE_MAX_NODE_N][ALPHA_SZ];
static int suffix[TRIE_MAX_NODE_N];
static int pid[TRIE_MAX_NODE_N];

typedef struct {
    size_t begin, pid;
} match;

const match *aho_corasick( const char *const text, const char *const *const patterns, const int patterns_n,
                           const int tlen, const int comm_plen, int *const matches_n ) {
    int tot = 0;
    memset( tr, 0, sizeof tr );
    memset( pid, 0, sizeof pid );
    // root is 0

    for ( int i = 0; i < patterns_n; i++ ) {
        int cur = 0;
        for ( int j = 0; j < comm_plen; j++ ) {
            const int idx = patterns[i][j] - 'a';
            if ( !tr[cur][idx] ) tr[cur][idx] = ++tot;
            cur = tr[cur][idx];
        }
        pid[cur] = i + 1;
    }

    int *const Q = malloc( tot * sizeof *Q );
    int head = 0, tail = 0;
    for ( int i = 0; i < ALPHA_SZ; i++ )
        if ( tr[0][i] ) {
            // the suffix of root doesn't matter
            // but the suffix of the first level nodes
            // has to be root
            suffix[tr[0][i]] = 0;
            Q[tail++] = tr[0][i];
        }
    while ( head < tail ) {
        int cur = Q[head++];
        for ( int i = 0; i < ALPHA_SZ; i++ ) {
            if ( tr[cur][i] ) {
                suffix[tr[cur][i]] = tr[suffix[cur]][i];
                Q[tail++] = tr[cur][i];
            } else {
                tr[cur][i] = tr[suffix[cur]][i];
            }
        }
    }

    // the meaning of suffix array changes here

    int *visited = calloc( tot + 1, sizeof *visited );
    head = tail = 0;

    for ( int i = 0; i < ALPHA_SZ; i++ )
        if ( tr[0][i] ) {
            Q[tail++] = tr[0][i];
            visited[tr[0][i]] = 1;
        }
    while ( head < tail ) {
        int cur = Q[head++];
        if ( !pid[suffix[cur]] ) {
            suffix[cur] = suffix[suffix[cur]];
            // the property of bfs guarantees that suffix[suffix[x]] is always already dict_suffix[suffix[x]]
        }
        for ( int i = 0; i < ALPHA_SZ; i++ ) {
            if ( tr[cur][i] && !visited[tr[cur][i]] ) {
                Q[tail++] = tr[cur][i];
                visited[tr[cur][i]] = 1;
            }
        }
    }
    free( visited );

    // begin search
    int mcap = 128, msz = 0;
    match *matches = malloc( mcap * sizeof *matches );
    for ( int i = 0, cur = 0; i < tlen; i++ ) {
        cur = tr[cur][text[i] - 'a'];
        for ( int x = cur; x; x = suffix[x] ) {
            if ( pid[x] ) {
                if ( msz >= mcap ) matches = realloc( matches, ( mcap <<= 1 ) * sizeof *matches );
                matches[msz++] = ( match ){i - comm_plen + 1, pid[x] - 1};
            }
        }
    }

    free( Q );

    *matches_n = msz;
    return matches;
}

static const int pow_p31[] = {
    1,         31,        961,       29791,     923521,    28629151,  887503681, 512613868, 891029773, 621922720,
    279604149, 667728547, 699584777, 687127898, 300964649, 329904038, 227025088, 37777665,  171107606, 304335741,
    434407890, 466644473, 465978537, 445334521, 805370034, 966470838, 960595717, 778466966, 132475730, 106747594,
    309175387, 584436916, 117544234, 643871227, 960007866, 760243585, 567550928, 594078615, 416436903, 909543885,
    195860183, 71665619,  221634171, 870659247, 990436423, 703528843, 809393944, 91212039,  827573191, 654768696,
    297829396, 232711195, 214046982, 635456388, 699147857, 673583378, 881084538, 313620435, 722233404, 389235326,
    66294998,  55144920,  709492511, 994267652, 822296942, 491204977, 227354152, 47978649,  487338110, 107481275,
    331919498, 289504348, 974634716, 213675926, 623953652, 342563041, 619454181, 203079440, 295462586, 159340085,
    939542599, 125820308, 900429521, 913314908, 312761896, 695618695, 564179356, 489559883, 176356238, 467043333,
    478343197, 828638981, 687808186, 322053577, 983660806, 493484716, 298026061, 238807810, 403042047, 494303349};

static int polyroll_hash( const char *str, const int comm_len ) {
    const int m = 1e9 + 9;
    int hash = 1;
    for ( int i = 0; i < comm_len; i++ ) {
        hash = ( hash + ( str[i] - 'a' + 1 ) * (int_fast64_t)pow_p31[i] ) % m;
    }
    return hash;
}

typedef struct _strncnt {
    const char *str;
    int pr_hash;
    int cnt;
    struct _strncnt *next;
} strncnt_t;

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
// assume len of any word <=100
int *findSubstring( char *s, char **words, int wordsSize, int *returnSize ) {
    if ( !wordsSize || !*s ) {
        *returnSize = 0;
        return NULL;
    }
    const int slen = strlen( s );
    const int comm_wlen = strlen( words[0] );
    if ( slen < comm_wlen * wordsSize ) {
        *returnSize = 0;
        return NULL;
    }

    // unique and count
    const int hcap = ( wordsSize << 2 ) / 3;
    strncnt_t **hash_arr = calloc( hcap, sizeof *hash_arr );
    for ( int i = 0; i < wordsSize; i++ ) {
        const int pr = polyroll_hash( words[i], comm_wlen );
        const int idx = pr % hcap;
        for ( strncnt_t *cur = hash_arr[idx]; cur; cur = cur->next ) {
            if ( cur->pr_hash == pr && !strcmp( cur->str, words[i] ) ) {  // dup
                cur->cnt++;
                goto OUTER_CONTINUE;
            }
        }
        strncnt_t *t = malloc( sizeof *t );
        *t = ( strncnt_t ){.str = words[i], .pr_hash = pr, .cnt = 1, .next = hash_arr[idx]};
        hash_arr[idx] = t;
    OUTER_CONTINUE:;
    }

    const char **uniq_words = malloc( wordsSize * sizeof *uniq_words );
    int *const cnt = malloc( wordsSize * sizeof *cnt );
    int uniqws_sz = 0;

    for ( int i = 0; i < hcap; i++ ) {
        for ( strncnt_t *cur = hash_arr[i], *next; cur; next = cur->next, free( cur ), cur = next ) {
            uniq_words[uniqws_sz] = cur->str;
            cnt[uniqws_sz++] = cur->cnt;
        }
    }
    free( hash_arr );

    int msz;
    const match *matches = aho_corasick( s, uniq_words, uniqws_sz, slen, comm_wlen, &msz );

    int anssz = 0, anscap = 32;
    int *ans = malloc( anscap * sizeof *ans );

    // sliding window
    //
    // you can't really slide on the matches, because there is input like
    // "aaaaaa" {"aaa","aaa"}
    // and there will be 4 matches but you need to take the first and the last.

    int *const hit = malloc( slen * sizeof *hit );
    memset( hit, -1, slen * sizeof *hit );
    for ( int i = 0; i < msz; i++ ) hit[matches[i].begin] = matches[i].pid;

    int *const used = malloc( wordsSize * sizeof *used );
    for ( int i = 0; i < comm_wlen; i++ ) {
        int window_sz = 0;
        memset( used, 0, wordsSize * sizeof *used );
        for ( int j = i; j < slen; j += comm_wlen ) {
            const int pid = hit[j];
            if ( ~pid ) {
                used[pid]++;
                window_sz++;
                while ( used[pid] > cnt[pid] ) used[hit[j - comm_wlen * ( --window_sz )]]--;
                if ( window_sz == wordsSize ) ans[anssz++] = j - comm_wlen * ( window_sz - 1 );
            } else {
                window_sz = 0;
                memset( used, 0, wordsSize * sizeof *used );
            }
        }
    }

    free( used );
    free( hit );
    free( (void *)matches );
    free( uniq_words );
    free( cnt );

    *returnSize = anssz;
    return ans;
}

#include <stdio.h>
void test0() {
    const char *const text =
        "pjzkrkevzztxductzzxmxsvwjkxpvukmfjywwetvfnujhweiybwvvsrfequzkhossmootkmyxgjgfordrpapjuunmqnxxdrqrfgkrsjqbszgiq"
        "lcfnrpjlcwdrvbumtotzylshdvccdmsqoadfrpsvnwpizlwszrtyclhgilklydbmfhuywotjmktnwrfvizvnmfvvqfiokkdprznnnjycttprkx"
        "puykhmpchiksyucbmtabiqkisgbhxngmhezrrqvayfsxauampdpxtafniiwfvdufhtwajrbkxtjzqjnfocdhekumttuqwovfjrgulhekcpjszy"
        "ynadxhnttgmnxkduqmmyhzfnjhducesctufqbumxbamalqudeibljgbspeotkgvddcwgxidaiqcvgwykhbysjzlzfbupkqunuqtraxrlptivsh"
        "hbihtsigtpipguhbhctcvubnhqipncyxfjebdnjyetnlnvmuxhzsdahkrscewabejifmxombiamxvauuitoltyymsarqcuuoezcbqpdaprxmsr"
        "ickwpgwpsoplhugbikbkotzrtqkscekkgwjycfnvwfgdzogjzjvpcvixnsqsxacfwndzvrwrycwxrcismdhqapoojegggkocyrdtkzmiekhxop"
        "pctytvphjynrhtcvxcobxbcjjivtfjiwmduhzjokkbctweqtigwfhzorjlkpuuliaipbtfldinyetoybvugevwvhhhweejogrghllsouipabfa"
        "fcxnhukcbtmxzshoyyufjhzadhrelweszbfgwpkzlwxkogyogutscvuhcllphshivnoteztpxsaoaacgxyaztuixhunrowzljqfqrahosheukh"
        "ahhbiaxqzfmmwcjxountkevsvpbzjnilwpoermxrtlfroqoclexxisrdhvfsindffslyekrzwzqkpeocilatftymodgztjgybtyheqgcpwogdc"
        "jlnlesefgvimwbxcbzvaibspdjnrpqtyeilkcspknyylbwndvkffmzuriilxagyerjptbgeqgebiaqnvdubrtxibhvakcyotkfonmseszhczap"
        "xdlauexehhaireihxsplgdgmxfvaevrbadbwjbdrkfbbjjkgcztkcbwagtcnrtqryuqixtzhaakjlurnumzyovawrcjiwabuwretmdamfkxrgq"
        "gcdgbrdbnugzecbgyxxdqmisaqcyjkqrntxqmdrczxbebemcblftxplafnyoxqimkhcykwamvdsxjezkpgdpvopddptdfbprjustquhlazkjfl"
        "uxrzopqdstulybnqvyknrchbphcarknnhhovweaqawdyxsqsqahkepluypwrzjegqtdoxfgzdkydeoxvrfhxusrujnmjzqrrlxglcmkiykldbi"
        "asnhrjbjekystzilrwkzhontwmehrfsrzfaqrbbxncphbzuuxeteshyrveamjsfiaharkcqxefghgceeixkdgkuboupxnwhnfigpkwnqdvzlyd"
        "pidcljmflbccarbiegsmweklwngvygbqpescpeichmfidgsjmkvkofvkuehsmkkbocgejoiqcnafvuokelwuqsgkyoekaroptuvekfvmtxtqsh"
        "cwsztkrzwrpabqrrhnlerxjojemcxel";
    const char *const patterns[] = {"dhvf", "sind", "ffsl", "yekr", "zwzq", "kpeo", "cila", "tfty", "modg",
                                    "ztjg", "ybty", "heqg", "cpwo", "gdcj", "lnle", "sefg", "vimw", "bxcb"};
    int retsz;
    int *ans = findSubstring( (char *)text, (char **)patterns, sizeof patterns / sizeof *patterns, &retsz );
    for ( int i = 0; i < retsz; i++ ) printf( "%3d", ans[i] );
    putchar( '\n' );
    free( ans );
}

void test1() {
    const char *const text = "wordgoodgoodgoodbestword";
    const char *const patterns[] = {"word", "good", "best", "word"};
    int retsz;
    int *ans = findSubstring( (char *)text, (char **)patterns, sizeof patterns / sizeof *patterns, &retsz );
    for ( int i = 0; i < retsz; i++ ) printf( "%3d", ans[i] );
    putchar( '\n' );
    free( ans );
}

void test2() {
    const char *const text = "barfoothefoobarman";
    const char *const patterns[] = {"foo", "bar"};
    int retsz;
    int *ans = findSubstring( (char *)text, (char **)patterns, sizeof patterns / sizeof *patterns, &retsz );
    for ( int i = 0; i < retsz; i++ ) printf( "%3d", ans[i] );
    putchar( '\n' );
    free( ans );
}

void test3() {
    const char *const text = "foofoofoo";
    const char *const patterns[] = {"foo"};
    int retsz;
    int *ans = findSubstring( (char *)text, (char **)patterns, sizeof patterns / sizeof *patterns, &retsz );
    for ( int i = 0; i < retsz; i++ ) printf( "%3d", ans[i] );
    putchar( '\n' );
    free( ans );
}

void test4() {
    const char *const text = "foobarfoo";
    const char *const patterns[] = {"foo", "bar"};
    int retsz;
    int *ans = findSubstring( (char *)text, (char **)patterns, sizeof patterns / sizeof *patterns, &retsz );
    for ( int i = 0; i < retsz; i++ ) printf( "%3d", ans[i] );
    putchar( '\n' );
    free( ans );
}

void test5() {
    const char *const text = "aaaaaa";
    const char *const patterns[] = {"aaa", "aaa"};
    int retsz;
    int *ans = findSubstring( (char *)text, (char **)patterns, sizeof patterns / sizeof *patterns, &retsz );
    for ( int i = 0; i < retsz; i++ ) printf( "%3d", ans[i] );
    putchar( '\n' );
    free( ans );
}
int main() { 
    test0();
    test1();
    test2();
    test3();
    test4();
}
