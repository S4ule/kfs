
#include <stddef.h>		// size_t

const void *
memchr(const void *s, int c, size_t n)
{
	while (n > 0)
	{
		if (*(const unsigned char *)s == (const unsigned char)c)
		{
			return s;
		}
		s++;
		n--;
	}
	return NULL;
}

int
memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ss1 = (const unsigned char *)s1;
	const unsigned char	*ss2 = (const unsigned char *)s2;

	while (*ss1 == *ss2 && n > 0)
	{
		ss1++;
		ss2++;
		n--;
	}
	if (n != 0)
	{
		return (*ss1 - *ss2);
	}
	return 0;
}

void *
memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*ptr_dst = (unsigned char *)dest;;
	const unsigned char	*ptr_src = (const unsigned char *)src;

	while (n > 0)
	{
		*ptr_dst = *ptr_src;
		ptr_dst++;
		ptr_src++;
		n--;
	}
	return dest;
}

void *
memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*ptr_dst = (unsigned char *)dest;
	const unsigned char	*ptr_src = (const unsigned char *)src;;

	if (ptr_dst > ptr_src && ptr_dst - ptr_src < (long int)n)
	{
		n--;
		while ((long int)n >= 0)
		{
			ptr_dst[n] = ptr_src[n];
			n--;
		}
		return (dest);
	}
	while (n > 0)
	{
		*ptr_dst = *ptr_src;
		ptr_dst++;
		ptr_src++;
		n--;
	}
	return dest;
}

void *
memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n > 0)
	{
		*ptr = c;
		ptr++;
		n--;
	}
	return s;
}

size_t
strlen(const char* str) 
{
	size_t len = 0;

	while (str[len] != '\0')
	{
		++len;
	}
	return len;
}

const char *
strchr(const char *s, int c)
{
	while (*s || *s == (char)c)
	{
		if (*s == (char)c)
		{
			return (s);
		}
		s++;
	}
	return NULL;
}