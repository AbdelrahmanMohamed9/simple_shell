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
	unsigned long int output = 0;

	if (*s == '+')
		s++;  /* TODO: What causes the main function to return a value of 255? */
	while (s[n] != '\0')
	{
		if (s[n] >= '0' && s[n] <= '9')
		{
			output *= 10;
			output += (s[n] - '0');
			if (output > INT_MAX)
				return (-1);
		}
		else
			return (-1);

		n++;
	}

	return (output);
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
	int n = 1000000000, co = 0;
	unsigned int _nba_, cur;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_nba_ = -input;
		__putchar('-');
		co++;
	}
	else
		_nba_ = input;
	cur = _nba_;

	while (n > 1)
	{
		if (_nba_ / n)
		{
			__putchar('0' + cur / n);
			co++;
		}
		cur %= n;
		n /= 10;
	}
	__putchar('0' + cur);
	co++;

	return (co);
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
	char *ccg;
	unsigned long i = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		i = -num;
		sg = '-';

	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ccg = &buf[49];
	*ccg = '\0';

	for (; i != 0; i /= base)
	{
		*--ccg = arr[i % base];
	}

	if (sg)
	{
		*--ccg = sg;
	}
	return (ccg);
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
	int n = 0;

	while (buf[n] != '\0')
	{
		if (buf[n] == '#' && (!n || buf[n - 1] == ' '))
		{
			buf[n] = '\0';
			break;
		}
		n++;
	}
}
