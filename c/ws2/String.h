#ifndef __STRING_H__
#define __STRING_H__

#include <stddef.h> /*size_t*/

/*find string length:*/
extern size_t StrLen(const char *str);

/* */
extern int StrCmp(const char *str1, const char *str2);

/* */
extern char *StrCpy(char *destination, const char *source);

/* */
extern char *StrNcpy(char *destination, const char *source, size_t n);

/* */
extern int StrCaseCmp(const char *s1, const char *s2);

/* */
extern char *StrChr(const char *str, int c);

/* */
extern char *StrDup(const char *source);

/* */
extern char *StrCat(char *dest, const char *src);

/* */
extern char *StrNcat(char *dest, const char *src, size_t n);

/* */
extern char *StrStr (const char *s1, const char *s2);

/* length of identical consecutive characters in both strings: */
extern size_t StrSpn(const char *s, const char *accept);

char *StrTok(char *str, const char *delim);

#endif
