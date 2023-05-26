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

	v = 0;
	while (src[v] != '\0' && v < n - 1)
	{
		dest[v] = src[v];
		v++;
	}
	if (v < n)
	{
		k = v;
		while (k < n)
		{
			dest[k] = '\0';
			k++;
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

	v = 0;
	k = 0;
	while (dest[v] != '\0')
		v++;
	while (src[k] != '\0' && k < n)
	{
		dest[v] = src[k];
		v++;
		k++;
	}
	if (k < n)
		dest[v] = '\0';
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
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
