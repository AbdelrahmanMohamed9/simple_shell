#include "shell.h"

/**
 *  _puts -  function that prints string, followed by a new line.
 *  @str: String to be printed.
 */

void _puts(char *str)
{
	int i;

	i = 0;
	while (str[i])
		_putchar(str[i++]);
	_putchar('\n');
}

/**
 * _putchar - function prints single character
 * @c: character to bassed as a parameter to be printed
 * Return: 1 on success, and -1 on error.
 */
int _putchar(char c)
{
	int ret;

	ret = write(1, &c, 1);
	if (ret == -1)
		return (-1);

	return (0);
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
	char *new;
	int i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i])
		i++;
	new = malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

/**
 * _strcpy - function copies string pointed to by src,
 * including the terminating null byte to the buffer pointed to dest.
 * @src: string to be copied
 * @dest: new string
 * Return: pointer to the destination string.
 */

char *_strcpy(char *dest, char *src)
{
	int i;
	int len;

	len = 0;
	i = 0;
	while (src[len])
		len++;
	while (i <= len)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}
