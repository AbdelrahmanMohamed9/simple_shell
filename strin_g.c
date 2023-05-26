#include "shell.h"

/**
 *  _strlen - function that returns the length of a string.
 *  @str: string to be passed as a parametter
 *  Return: length of a string
 */

int _strlen(char *str)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str++)
		i++;
	return (i);
}

/**
 * _strcmp - function compares two strings.
 * @str1: first string
 * @str2: second string
 * Return: 0 if strings are equal
 * >0 if the first non-matching character in str1 is than that of str2.
 * <0 if the first non-matching character in str1 is lower than that of str2.
 */

int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}


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
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat -  function concatenates two strings.
 * @src: string to be apended to the destination.
 * @dest: string to be returned
 * Return:  pointer to  dest.
 */

char *_strcat(char *dest, char *src)
{
	char *new = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (new);
}
