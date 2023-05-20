#include "shell.h"

/**
 * interactive - That Return true If shell Is Interactive.
 * @info: The Structure Address.
 *
 * Return: When Interactive Return 1, Otherwise Return 0 .
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - That For check The Character If It's Delimeter.
 * @c: the character That Will Check.
 * @delim: Delimeter Str.
 *
 * Return: When true Return 1, When false Return 0 .
 */
int is_delim(char c, char *delim)
{
	for (; *delim; delim++)
	{
		if (*delim == c)
		{
		return (1);
		}
	}
	return (0);
}

/**
 *_isalpha - That Check The Alphabetic Char.
 *@c: A Char To The Input.
 *
 *Return: When The C alphabetic Return 1,
 *	When The C Not Alphabetic Return 0 .
 */

int _isalpha(int c)
{
	int s = 0;

	while (('a' + s <= c && c <= 'z' + s) || ('A' + s <= c && c <= 'Z' + s))
	{
		s++;
	}
	return (s > 0);
}

/**
 *_atoi - That Transforms Str To int.
 *@s: str It Will Be Convert.
 *Return: When No num In str Return 0, Otherwise Convert num.
 */

int _atoi(char *s)
{
	int n = 0, sg = 1, fg = 0, op = 0;
	unsigned int res = 0;

	while (s[n] != '\0' && fg != 2)
	{
		if (s[n] == '-')
			sg *= -1;

		if (s[n] >= '0' && s[n] <= '9')
		{
			fg = 1;
			res *= 10;
			res += (s[n] - '0');
		}
		else if (fg == 1)
			fg = 2;

		n++;
	}

	if (sg == -1)
		op = -res;
	else
		op = res;

	return (op);
}
