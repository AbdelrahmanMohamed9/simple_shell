#include "shell.h"

/**
 **_strncpy - Creates a copy of a str.
 *@dest: Output str to be generated.
 *@src: Str to be duplicated.
 *@n: The maximum number of characters to copy.
 *
 *Return: The string that has been merged.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int v, k;
	char *c = dest;

	for (v = 0; src[v] != '\0' && v < n - 1; v++)
	{
		dest[v] = src[v];
	}
	if (v < n)
	{
		for (k = v; k < n; k++)
		{
			dest[k] = '\0';
		}
	}
	return (c);
}

/**
 **_strncat - Appends one string to another.
 *@dest: First input str.
 *@src : Second input str.
 *@n: Maximum size of the byte stream.
 *
 *Return: The combined str.
 */
char *_strncat(char *dest, char *src, int n)
{
	int v, k;
	char *c = dest;

	for (v = 0; dest[v] != '\0'; v++)

	for (k = 0; src[k] != '\0' && k < n; k++)
	{
		dest[v + k] = src[k];
	}

	if (k < n)
	{
		dest[v + k] = '\0';
	}

	return (c);
}

/**
 **_strchr - Locates the occurrence of char in str.
 *@s: Target str for Parsing.
 *@c: Lookup char.
 *
 *Return: A memory address represented by the pointer s.
 */
char *_strchr(char *s, char c)
{
	for (; *s != '\0'; s++)
	{
		if (*s == c)
		{
			return (s);
		}
	}

	return (NULL);
}
