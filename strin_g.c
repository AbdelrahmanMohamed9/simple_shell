#include "shell.h"

/**
 * starts_with - function finds the first occurrence
 * of substring needle in string haystack
 * @haystack:  This is the main C string to be scanned.
 * @needle: This is the small string to be searched with-in haystack string.
 * Return: a pointer to the first occurrence in haystack of any of the entire
 * sequence of characters specified in needle, or a null pointer if
 * the sequence is not present in haystack.
 */

char *starts_with(const char *haystack, const char *needle)
{
	int	i;
	int	j;

	i = 0;
	while (haystack[i] != '\0')
	{
		j = 0;
		while (needle[j] == haystack[i + j])
		{
			while (needle[j + 1] == '\0')
			{
				return ((char *)(haystack + i));
			}
			j++;
		}
		i++;
	}
	return (0);
}

/**
 *  _strlen - function that returns the length of a string.
 *  @s: string to be passed as a parametter
 *  Return: length of a string
 */

int _strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/**
 * _strcat -  function concatenates two strings.
 * @src: string to be apended to the destination.
 * @dest: string to be returned
 * Return:  pointer to  dest.
 */

char *_strcat(char *dest, char *src)
{
	int i, j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
		dest[i++] = src[j++];
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcmp - function compares two strings.
 * @s1: first string
 * @s2: second string
 * Return: 0 if strings are equal
 * >0 if the first non-matching character in str1 is than that of str2.
 * <0 if the first non-matching character in str1 is lower than that of str2.
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
