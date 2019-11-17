/******************************
 *          MANACHER
 *   Don't forget to free
 *   the returned pointer.
 *****************************/
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define DELI '|'

static char *manacher(const char *const s) {
    size_t slen = strlen(s);
    size_t tlen = (slen << 1) + 1;
    char *t = malloc(tlen);
    for (size_t i = 0; i < slen; i++) {
        t[i << 1] = DELI;
        t[(i << 1) + 1] = s[i];
    }
    t[tlen - 1] = DELI;
    size_t *radius = malloc(tlen * sizeof *radius);
    radius[0] = 0;
    for (size_t i = 1, r = 0, c = 0; i < tlen; i++) {
        size_t ext_l, ext_r;
        if (i > r) {
            radius[i] = 0;
            ext_l = i - 1;
            ext_r = i + 1;
        } else {
            size_t j = (c << 1) - i;
            if (radius[j] + 1 < r - i) {
                radius[i] = radius[j];
                ext_l = SIZE_MAX;  // signal for no extension
            } else {
                radius[i] = r - i;
                ext_r = r + 1;
                ext_l = (i << 1) - ext_r;
            }
        }

        while (ext_l != SIZE_MAX && ext_r < tlen && t[ext_l] == t[ext_r]) {
            radius[i]++;
            ext_l--;
            ext_r++;
        }

        if (i + radius[i] > r) {
            c = i;
            r = i + radius[i];
        }
    }
    free(t);

    size_t max_radius = 0, max_center = 0;
    for (size_t i = 1; i < tlen; i++) {
        if (max_radius < radius[i]) {
            max_radius = radius[i];
            max_center = i;
        }
    }
    free(radius);
    size_t orig_start = (max_center >> 1) - (max_radius >> 1);
    char *ans = malloc(max_radius + 1);
    memcpy(ans, s + orig_start, max_radius);
    ans[max_radius] = '\0';
    return ans;
}

char* longestPalindrome( char* s ) {
    return manacher(s);
}
