#ifndef __UTIL_BS_H__
#define __UTIL_BS_H__
#include <stdint.h>
/**
 * \brief Basic search improved. Limits are better handled, so
 * it doesn't start searches that wont fit in the remaining buffer
 *
 * \param haystack pointer to the buffer to search in
 * \param haystack_len length limit of the buffer
 * \param neddle pointer to the pattern we ar searching for
 * \param needle_len length limit of the needle
 *
 * \retval ptr to start of the match; NULL if no match
 */

static uint8_t *BasicSearch(const uint8_t *haystack, uint32_t haystack_len, const uint8_t *needle, uint32_t needle_len) {

    const uint8_t *h, *n;
    const uint8_t *hmax = haystack + haystack_len;
    const uint8_t *nmax = needle + needle_len;

    if (needle_len == 0 || needle_len > haystack_len) {
       return NULL;
    }

    for (n = needle; nmax - n <= hmax - haystack; haystack++) {
        if (*haystack != *n) {
            continue;
        }

        /* one byte needles */
        if (needle_len == 1) {
            return (uint8_t *)haystack;
        }

        for (h = haystack+1, n++; nmax - n <= hmax - haystack; h++, n++) {
            if (*h != *n) {
                break;
            }

            /* if we run out of needle we fully matched */
            if (n == nmax - 1) {
                return (uint8_t *)haystack;
            }
        }
        n = needle;
    }

    return NULL;
}

#endif /*__UTIL_BS_H__*/
