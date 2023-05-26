#include "shell.h"

/**
 * _strcpy - function copies string pointed to by src,
 * including the terminating null byte to the buffer pointed to dest.
 * @src: string to be copied
 * @dest: new string
 * Return: pointer to the destination string.
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _strdup - function return pointer to newly allocated space in memory,
 * which contains a copy of the string passed as a parameter.
 * @str: string to be duplicated.
 * Return: NULL if str = NULL, On success, the _strdup function returns
 * a pointer to the duplicated string.
 * It returns NULL if insufficient memory was available
 */

char *_strdup(const char *str)
{
	int len = 0;
	char *new;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	for (len++; len--;)
		new[len] = *--str;
	return (new);
}

/**
 *  _puts -  function that prints string, followed by a new line.
 *  @s: String to be printed.
 */

void _puts(char *s)
{
	int i = 0;

	if (!s)
		return;
	while (s[i] != '\0')
	{
		_putchar(s[i]);
		i++;
	}
}

/**
 * _putchar - function prints single character
 * @ch: character to bassed as a parameter to be printed
 * Return: 1 on success, and -1 on error.
 */

int _putchar(char ch)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buf[i++] = ch;
	return (1);
}
