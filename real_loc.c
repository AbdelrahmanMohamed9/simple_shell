#include "shell.h"

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

	for (i = 0; i < n; i++)
		str[i] = c;
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

/**
 * _realloc - function reallocates a block of memory
 * @ptr: pointer to previous malloced block
 * @oldsize: size of previous block
 * @newsize: size of new block
 * Return: pointer to reallocated memory
 */
void *_realloc(void *ptr, unsigned int oldsize, unsigned int newsize)
{
	char *p;

	if (!ptr)
		return (malloc(newsize));
	if (!newsize)
		return (free(ptr), NULL);
	if (newsize == oldsize)
		return (ptr);

	p = malloc(newsize);
	if (!p)
		return (NULL);

	oldsize = oldsize < newsize ? oldsize : newsize;
	while (oldsize--)
		p[oldsize] = ((char *)ptr)[oldsize];
	free(ptr);
	return (p);
}
