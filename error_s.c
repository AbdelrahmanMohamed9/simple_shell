#include "shell.h"

/**
 *_eputs - Displays the provided str.
 * @str: The inputted string that will be outputted
 *
 *
 * Return: Empty
 */
void _eputs(char *str)
{
	int n;

	if (!str)
		return;
	for (n = 0; str[n] != '\0'; n++)
	{
		_eputchar(str[n]);
	}
}

/**
 * _eputchar - Prints The char C To The Error Output.
 * @c: That Is The char To Be Outputted.
 *
 *
 * Return: Return 1 When Success And -1 When Not Success.
 *
 */
int _eputchar(char c)
{
	static int n;
	static char buffer[WRITE_BUF_SIZE];

	while (1)
	{
		if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
		{
			write(2, buffer, n);
			n = 0;
			break;
		}
		if (c != BUF_FLUSH)
		{
			buffer[n++] = c;
			break;
		}
	}
	return (1);
}

/**
 * _putfd - Outputs the character c to the specified file descriptor.
 * @c: That Is The char To Be Outputted.
 * @fd: The handle for the file or device
 *	to which data is written.
 *
 *
 * Return: Return 1 When Success And -1 When Not Success.
 *
 */
int _putfd(char c, int fd)
{
	static int n;
	static char buffer[WRITE_BUF_SIZE];

	while (1)
	{
		if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
		{
			write(fd, buffer, n);
			n = 0;
			break;
		}
		if (c != BUF_FLUSH)
		{
			buffer[n++] = c;
			break;
		}
	}
	return (1);
}

/**
 *_putsfd - Outputs the provided str.
 * @str: The inputted string that will be outputted.
 * @fd: The handle for the file or device
 *	to which data is written.
 *
 * Return: The count of characters that were written.
 */
int _putsfd(char *str, int fd)
{
	int n;

	if (!str)
		return (0);
	for (n = 0; *str; str++)
	{
		n += _putfd(*str, fd);
	}
	return (n);
}
