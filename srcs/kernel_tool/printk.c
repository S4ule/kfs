
#include <stdarg.h> // va_list va_start() va_arg() va_end()

#include "kernel_tool/terminal.h" // terminal_putstr() terminal_putchar()

static void
_printk_put_hex_upper(unsigned long n)
{
	char c;

	if (n > 15)
	{
		_printk_put_hex_upper(n / 16);
		n %= 16;
	}
	c = n + '0';
	if (c > '9')
	{
		c = c - '0' - 10 + 'A';
	}
	terminal_putchar(c);
}

static void
_printk_put_hex_lower(unsigned long n)
{
	char c;

	if (n > 15)
	{
		_printk_put_hex_lower(n / 16);
		n %= 16;
	}
	c = n + '0';
	if (c > '9')
	{
		c = c - '0' - 10 + 'a';
	}
	terminal_putchar(c);
}

static void
_printk_put_uint(unsigned int n)
{
	char c;

	if (n > 9)
	{
		_printk_put_uint(n / 10);
		n %= 10;
	}
	c = n + '0';
	terminal_putchar(c);
}

static void
_printk_put_int(int n)
{
	unsigned int	num;
	char			c;

	if (n < 0)
	{
		terminal_putchar('-');
		num = n * -1;
	}
	else
		num = n;
	if (num > 9)
	{
		_printk_put_uint(num / 10);
		num %= 10;
	}
	c = num + '0';
	terminal_putchar(c);
}

static int
_printk_pars_args(const char c_type, va_list *args)
{
	switch(c_type)
	{
		case 'd':
		{
			int i = va_arg(*args, int);

			_printk_put_int(i);
			break ;
		}
		case 'u':
		{
			unsigned int i = va_arg(*args, unsigned int);

			_printk_put_uint(i);
			break ;
		}
		case 's':
		{
			const char *s = va_arg(*args, const char *);
			
			terminal_putstr(s);
			break ;
		}
		case 'c':
		{
			int c = va_arg(*args, int);

			terminal_putchar(c);
			break ;
		}
		case 'x':
		{
			unsigned long a = va_arg(*args, unsigned long);

			_printk_put_hex_lower(a);
			break ;
		}
		case 'X':
		{
			unsigned long a = va_arg(*args, unsigned long);

			_printk_put_hex_upper(a);
			break ;
		}
		case '%':
		{
			terminal_putchar('%');
			return 1;
		}
		default:
		{
			terminal_putchar(c_type);
			break ;
		}
	}
	return 0;
}

void
printk(const char* format, ...)
{
	va_list args;
 
 	va_start(args, format);
 	while (*format != '\0')
 	{
 		if (*format == '%')
 		{
 			++format;
 			_printk_pars_args(*format, &args);
 		}
 		else
 		{
 			terminal_putchar(*format);
 		}
 		++format;
 	}
	va_end(args);
	return ;
}