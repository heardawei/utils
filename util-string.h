#ifndef __UTIL_STRING_H__
#define __UTIL_STRING_H__

#ifdef __cplusplus
extern "C" {
#endif

char *strip(char *string);
char *get_value_by_key(const char *haystack, const char *needle, char sep, int ignore_case);
void mSplitFree(char*** pbuf, int num_toks);
char** mSplit(const char* str, const char* sep_chars, const int max_toks,
    int* num_toks, const char meta_char);

#ifdef __cplusplus
}
#endif

#endif /*__UTIL_STRING_H__*/