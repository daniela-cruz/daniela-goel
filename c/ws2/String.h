#include <stdio.h>  /*size_t*/
#include <stdlib.h> /*linkage*/
/*String header reimplementation*/
extern size_t StrLen(const char *str);

extern int StrCmp(const char *str1, const char *str2);

extern char *StrCpy(char *destination, const char *source);

extern char *StrNcpy(char *destination, const char *source, size_t n);

extern int StrCaseCmp(const char *s1, const char *s2);

extern char *StrChr(const char *str, int c);
