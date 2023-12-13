#include "main.h"

/**
 * print_str - print a string pointed to by @str
 * @str: ptr to string
 * @len: string length
 * Return: int, number of printed chars
 */
int print_str(char *str, int len)
{
	if (!str)
		return (print_str("(null)", 6));

	return (write(STDOUT_FILENO, str, len));
}

/**
 * ppstr - parse and print string from va_list
 * @ap: arg ptr to string
 * @spec: format specifier
 * Return: int, number of printed chars
 */
int ppstr(va_list ap, char *spec)
{
	int count;
	int len;
	char *tmp;

	if (spec == NULL)
		return (0);
	tmp = va_arg(ap, char *);
	len = _strlen(tmp);
	count = print_str(tmp, len);

	return (count);
}

/**
 * _perror - print error msg to stderr
 * @errormsg: error msg to print
 */
void _perror(char *errormsg)
{
	perror(errormsg);
}

/**
 * ppchar - extract char from @va_list
 * @ap: ptr to list of args
 * @spec: format specifier
 * Return: int, number of printed chars
 */
int ppchar(va_list ap, char *spec)
{
	int count;

	if (!spec)
		return (0);
	count = put_char(va_arg(ap, int));

	return (count);
}

/**
 * put_char - print a single char to stdout
 * @c: the char to be printed
 * Return: number of printed chars
 */
int put_char(char c)
{
	return (write(STDOUT_FILENO, &c, 1));
}
