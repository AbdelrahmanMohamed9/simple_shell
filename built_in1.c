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
	char *b, s;
	int rt;

	b = _strchr(str, '=');
	if (!b)
		return (1);
	s = *b;
	*b = 0;
	rt = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*b = s;
	return (rt);
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
	char *b = NULL, *m = NULL;

	if (node)
	{
		b = _strchr(node->str, '=');
		for (m = node->str; m <= b; m++)
			_putchar(*m);
		_putchar('\'');
		_puts(b + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - That Emulates An Alias Builtin.
 * @info: That Struct Contain The Possible Argument
 *
 *  Return: That Will Return 0 always.
 */
int _myalias(info_t *info)
{
	int n = 0;
	char *b = NULL;
	list_t *nd = NULL;

	if (info->argc == 1)
	{
		nd = info->alias;
		while (nd)
		{
			print_alias(nd);
			nd = nd->next;
		}
		return (0);
	}
	for (n = 1; info->argv[n]; n++)
	{
		b = _strchr(info->argv[n], '=');
		if (b)
			set_alias(info, info->argv[n]);
		else
			print_alias(node_starts_with(info->alias, info->argv[n], '='));
	}

	return (0);
}
