#include "shell.h"

/**
 * _realloc - function reallocates a block of memory
 * @p: pointer to previous malloced block
 * @size_old: size of previous block
 * @size_new: size of new block
 * Return: pointer to reallocated memory
 */
void *_realloc(void *p, unsigned int size_old, unsigned int size_new)
{
	char *ptr;

	if (!p)
		return (malloc(size_new));
	if (!size_new)
		return (free(p), NULL);
	if (size_old == size_new)
		return (p);

	ptr = malloc(size_new);
	if (!ptr)
		return (NULL);
	size_old = size_old < size_new ? size_old : size_new;
	while (size_old--)
		ptr[size_old] = ((char *)p)[size_old];
	free(p);
	return (ptr);
}

/**
 * _memset - copies character c to the first n characters of string str
 * @str: pointer to the block of memory to fill.
 * @c: character to fill the string with
 * @n: number of bytes to be set to the value.
 * Return: pointer to the memory area str.
 */

char *_memset(char *str, char c, unsigned int n)
{
	unsigned int i;

	i = 0;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (str);
}

/**
 * ffree - function frees a string of strings
 * @str: string of strings
 */
void ffree(char **str)
{
	char **s = str;

	if (!str)
		return;
	while (*str)
		free(*str++);
	free(s);
}
