
#include <stddef.h>		// size_t
#include <stdbool.h>	// true/false

int
atoi(const char *nptr)
{
	int	neg;
	int	res;

	res = 0;
	neg = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
	{
		nptr++;
	}
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
		{
			neg *= -1;
		}
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + *nptr - '0';
		nptr++;
	}
	return (res * neg);
}
