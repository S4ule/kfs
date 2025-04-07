#ifndef __STRING_H__
# define __STRING_H__ 1

#include <stddef.h>	// size_t

/*
	STR
*/
size_t strlen(const char* str);
const char *strchr(const char *s, int c);

/*
	MEM	
*/
void *memset(void *s, int c, size_t n);
void *memmove(void *dest, const void *src, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
const void *memchr(const void *s, int c, size_t n);

#endif /* __STRING_H__ */