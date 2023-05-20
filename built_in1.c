#include "shell.h"

/**
 * _myhistory - That Shows A History List, One Command In line,
 *	Marked With Line num, Start In 0 .
 * @info:That Struct Contain The Possible Argument.
 *
 * Return: That Will Return 0 always.
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - That Put Alias To Str.
 * @info: That Is The Parameter Structure.
 * @str: That Is A Str Alis.
 *
 * Return: Return 0 always In Success, Return 1 In Error.
 */
int unset_alias(info_t *info, char *str)
{
	char *b, x;
	int mma;

	b = _strchr(str, '=');
	if (!b)
		return (1);
	x = *b;
	*b = 0;
	mma = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*b = x;
	return (mma);
}

/**
 * set_alias - That Put Alias To Str.
 * @info: That Is The Parameter Structure.
 * @str: That Is A Str Alis.
 *
 * Return: Return 0 always In Success, Return 1 In Error.
 */
int set_alias(info_t *info, char *str)
{
	char *b;

	b = _strchr(str, '=');
	if (!b)
		return (1);
	if (!*++b)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - That Shows The Alias Str.
 * @node: Tha Is An Alias Node.
 *
 * Return: Return 0 always In Success, Return 1 In Error.
 */
int print_alias(list_t *node)
{
	char *b = NULL, *e = NULL;
	int return_val = 0;

	if (node)
	{
		b = _strchr(node->str, '=');
		e = node->str;
		while (e <= b)
		{
		_putchar(*e);
		e++;
		}
		_putchar('\'');
		_puts(b + 1);
		_puts("'\n");
	}
	else
	{
		(return_val) = 1;
	}
	return (return_val);
}

/**
 * _myalias - That Emulates An Alias Builtin.
 * @info: That Struct Contain The Possible Argument
 *
 *  Return: That Will Return 0 always.
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		for (node = info->alias; node != NULL; node = node->next)
		{
		print_alias(node);
		}

		return (0);
	}

	i = 1;

	while (info->argv[i] != NULL)
	{
		p = _strchr(info->argv[i], '=');
		if (p != NULL)
		{
		set_alias(info, info->argv[i]);
		}
		else
		{
		print_alias(node_starts_with(info->alias, info->argv[i], '='));
		}
		i++;
	}

	return (0);
}
