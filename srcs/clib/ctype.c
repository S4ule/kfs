
#include <stddef.h>		// size_t
#include <stdbool.h>	// true/false

/*
	???
*/
int
toupper(int c)
{
	if (c >= 97 && c <= 122)
	{
		c -= 32;
	}
	return c;
}

int
tolower(int c)
{
	if (c >= 65 && c <= 90)
	{
		c += 32;
	}
	return c;
}


/*
	Char Checker
*/
bool
isalnum(int c)
{
	if (c >= 65 && c <= 90)
	{
		return true;
	}
	if (c >= 97 && c <= 122)
	{
		return true;
	}
	if (c >= 48 && c <= 57)
	{
		return true;
	}
	return false;
}

bool
isalpha(int c)
{
	if (c >= 65 && c <= 90)
	{
		return true;
	}
	if (c >= 97 && c <= 122)
	{
		return true;
	}
	return false;
}

bool
isascii(int c)
{
	if (c >= 0 && c <= 127)
	{
		return true;
	}
	return false;
}

bool
isdigit(int c)
{
	if (c >= 48 && c <= 57)
	{
		return true;
	}
	return false;
}

bool
isprint(int c)
{
	if (c >= 32 && c <= 126)
	{
		return true;
	}
	return false;
}

