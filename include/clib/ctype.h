#ifndef __CTYPE_H__
# define __CTYPE_H__ 1

#include <stdbool.h>

/*
	???
*/
int toupper(int c);
int tolower(int c);

/*
	Char Checker
*/
bool isalnum(int c);
bool isalpha(int c);
bool isascii(int c);
bool isdigit(int c);
bool isprint(int c);

#endif /* __CTYPE_H__ */