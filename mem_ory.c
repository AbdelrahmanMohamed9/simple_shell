#include "shell.h"

/**
 * bfree - function frees a pointer.
 * @p: - pointer to be freed.
 * Return: 1 if freed, or 0 if not.
 */

int bfree(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
