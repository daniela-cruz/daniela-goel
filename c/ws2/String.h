#include <stdio.h>  /*size_t*/
#include <stdlib.h> /*linkage*/
/*String header reimplementation*/
size_t StrLen(const char *str);

int StrCmp(const char *str1, const char *str2);

char *StrCpy(char *destination, const char *source);

char *StrNcpy(char *destination, const char *source, size_t n);
