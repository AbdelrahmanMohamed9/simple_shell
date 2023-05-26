#include "shell.h"

/**
 * _erratoi - Changes Str To Int.
 * @s: The Input Str To Be Transformed.
 *
 * Return: Return 0 With No Num In Str Return -1 If
 *	Otherwise.
 */
int _erratoi(char *s)
{
	int n = 0;
	unsigned long int rst = 0;

	if (*s == '+')
		s++;  /* TODO: why Does That Make Main Return 255? */
	for (n = 0;  s[n] != '\0'; n++)
	{
		if (s[n] >= '0' && s[n] <= '9')
		{
			rst *= 10;
			rst += (s[n] - '0');
			if (rst > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (rst);
}

/**
 * print_error - Shows A Error Message On The Screen.
 * @info: The Input And Output Information Structure.
 * @estr: A Str That Identifies A Particular Kind Of Error.
 *
 * Return: Return 0 With No Num In Str, Return -1 If
 *      Otherwise.
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - Generates a text representation
 *	of a base 10 integer.
 * @input: A User's Input.
 * @fd: The File Handle For Writing Data.
 *
 * Return: Return The Count of char outputted.
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int n, cnt = 0;
	unsigned int _cpc_, crnt;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_cpc_ = -input;
		__putchar('-');
		cnt++;
	}
	else
		_cpc_ = input;
	crnt = _cpc_;
	for (n = 1000000000; n > 1; n /= 10)
	{
		if (_cpc_ / n)
		{
			__putchar('0' + crnt / n);
			cnt++;
		}
		crnt %= n;
	}
	__putchar('0' + crnt);
	cnt++;

	return (cnt);
}

/**
 * convert_number - A copy of the itoa converter function.
 * @num: Numeric value.
 * @base: Number system base.
 * @flags: Input parameters indicators.
 *
 * Return: That Will Return Str.
 */
char *convert_number(long int num, int base, int flags)
{
	static char *arr;
	static char buf[50];
	char sg = 0;
	char *br;
	unsigned long i = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		i = -num;
		sg = '-';

	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	br = &buf[49];
	*br = '\0';

	do	{
		*--br = arr[i % base];
		i /= base;
	} while (i != 0);

	if (sg)
		*--br = sg;
	return (br);
}

/**
 * remove_comments - This function replaces first appearance
 *	of '#' in str with null char to terminate str.
 * @buf: Location of the string to be changed in memory.
 *
 * Return: That Will Return 0 always.
 */
void remove_comments(char *buf)
{
	int n;

	for (n = 0; buf[n] != '\0'; n++)
		if (buf[n] == '#' && (!n || buf[n - 1] == ' '))
		{
			buf[n] = '\0';
			break;
		}
}
