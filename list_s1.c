#include "shell.h"

/**
 * list_to_strings - function returns array of strings
 * of list str
 * @h: pointer to the first node.
 * Return: array of strings.
 */

char **list_to_strings(list_t *h)
{
	list_t *new = h;
	size_t i = list_len(h), j;
	char **str_s;
	char *str;

	if (!h || !i)
		return (NULL);
	str_s = malloc(sizeof(char *) * (i + 1));
	if (!str_s)
		return (NULL);
	for (i = 0; new; new = new->next, i++)
	{
		str = malloc(_strlen(new->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(str_s[j]);
			free(str_s);
			return (NULL);
		}

		str = _strcpy(str, new->str);
		str_s[i] = str;
	}
	str_s[i] = NULL;
	return (str_s);
}

/**
 *  print_list - function prints the elements of a listint_t list.
 *  @head: linked list
 *  Return: number of nodes
 */

size_t print_list(const list_t *head)
{
	size_t i = 0;

	while (head)
	{
		_puts(convert_number(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * get_node_index - function that gets the index of the node.
 * @h: pointer to list head.
 * @node: pointer to node.
 * Return: index of the node or -1 if fails.
 */
ssize_t get_node_index(list_t *h, list_t *node)
{
	size_t i = 0;

	while (h)
	{
		if (h == node)
			return (i);
		h = h->next;
		i++;
	}
	return (-1);
}

/**
 * node_starts_with - function returns node which string starts with str.
 * @h: pointer to list head.
 * @prfx: string to match with.
 * @s: the next character afer str to match
 * Return: the matched node or NULL
 */
list_t *node_starts_with(list_t *h, char *prfx, char s)
{
	char *p = NULL;

	while (h)
	{
		p = starts_with(h->str, prfx);
		if (p && ((s == -1) || (*p == s)))
			return (h);
		h = h->next;
	}
	return (NULL);
}

/**
 * list_len -  function that returns the number of
 * elements in a linked listint_t list.
 * @h: linked list
 * Return: number of elements.
 */

size_t list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}
